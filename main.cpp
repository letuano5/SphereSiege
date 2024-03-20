#include "Enemy.h"
#include "Hero.h"
#include "Includes.h"
#include "Items.h"
#include "Menu.h"
#include "MultiEnemy.h"
#include "ProgressBar.h"
#include "Score.h"
#include "Text.h"
#include "Window.h"

using namespace std;

Window window("Sphere Siege", WINDOW_WIDTH, WINDOW_HEIGHT);
Hero* hero = NULL;
ProgressBar* Health = NULL;
ProgressBar* Progress = NULL;
Score* score = NULL;
Score* best = NULL;
MultiEnemy* enemies = NULL;
Camera* camera = NULL;
Items* items = NULL;

Menu start("start");
Menu pause("pause");
Menu lost("lost");

Uint64 prevTime = SDL_GetPerformanceCounter();
Uint64 currTime, deltaTime;

void reset() {
    delete hero;
    hero = NULL;
    delete Health;
    Health = NULL;
    delete Progress;
    Progress = NULL;
    delete score;
    score = NULL;
    delete best;
    best = NULL;
    delete enemies;
    enemies = NULL;
    delete camera;
    camera = NULL;
    delete items;
    items = NULL;
}

void init() {
    reset();
    hero = new Hero(20, 20, WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2 - 100, "res/triangle.png");
    Health = new ProgressBar(120, 12, 20, 20, "HP", true, {0, 255, 0, 255});
    Progress = new ProgressBar(120, 12, 220, 20, "progress", true, {150, 150, 150, 255});
    score = new Score(0, "score: ", 520, 20, false);
    best = new Score(0, "best: ", 750, 20, true);
    enemies = new MultiEnemy();
    camera = new Camera();
    items = new Items();
}

void play() {
    pair<int, int> mousePos = {-1, -1};
    window.clear();
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
        mousePos = window.pollEvents(event);
    }
    if (isStarted) {
        currTime = SDL_GetPerformanceCounter();
        deltaTime = currTime - prevTime;
        dt = (double)deltaTime / SDL_GetPerformanceFrequency();
        prevTime = currTime;

        if (isPaused) {
            pause.draw(mousePos.first, mousePos.second);
            return;
        }
        if (isLost) {
            lost.draw(mousePos.first, mousePos.second);
            if (!isLost) {
                init();
            }
            return;
        }

        enemies->generateEnemy(*hero, *score, *camera);
        items->spawnItem(*hero, *camera, *enemies);
        Progress->draw();
        Health->draw();
        score->draw();
        best->draw();
        if (score->getScore() >= best->getScore()) {
            best->update(score->getScore());
        }
        Health->update(hero->health_point);
        Progress->update(0);
        hero->draw(*camera);
        hero->pollEvents(*camera);
        hero->update();

    } else {
        start.draw(mousePos.first, mousePos.second);
    }
}

int main(int argv, char** args) {
    srand(time(NULL));

    init();
    while (!window.isClosed()) {
        play();
    }

    reset();

    return 0;
}
