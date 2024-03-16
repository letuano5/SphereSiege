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

int main(int argv, char **args) {
    srand(time(NULL));
    Uint64 prevTime = SDL_GetPerformanceCounter();
    Uint64 currTime, deltaTime;

    Window window("Sphere Siege", WINDOW_WIDTH, WINDOW_HEIGHT);
    Hero hero(20, 20, WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2 - 100, "res/triangle.png");
    ProgressBar Health(120, 12, 20, 20, "HP", true, {0, 255, 0, 255});
    ProgressBar Progress(120, 12, 220, 20, "progress", true, {150, 150, 150, 255});
    Score score(0, "score: ", 520, 20, false);
    Score best(0, "best: ", 750, 20, true);
    MultiEnemy enemies;
    Camera camera;
    Items items;

    Menu start("start");
    Menu pause("pause");
    Menu lost("lost");
    while (!window.isClosed()) {
        pair<int, int> mousePos = {-1, -1};
        window.clear();
        SDL_Event event;
        if (SDL_PollEvent(&event)) {
            mousePos = window.pollEvents(event);
        }
        if (isStarted) {
            if (isPaused) {
                pause.draw(mousePos.first, mousePos.second);
                continue;
            }
            if (isLost) {
                lost.draw(mousePos.first, mousePos.second);
                continue;
            }
            currTime = SDL_GetPerformanceCounter();
            deltaTime = currTime - prevTime;
            double dt = (double)deltaTime / SDL_GetPerformanceFrequency();

            enemies.generateEnemy(hero, score, camera);
            items.spawnItem(hero, camera);
            Progress.draw();
            Health.draw();
            score.draw();
            best.draw();
            if (score.getScore() >= best.getScore()) {
                best.update(score.getScore());
            }
            Health.update(hero.health_point);
            Progress.update(0);
            hero.draw(camera);
            hero.pollEvents(dt, camera);
            hero.update(dt);
            prevTime = currTime;
        } else {
            start.draw(mousePos.first, mousePos.second);
        }
    }

    return 0;
}
