
#include "Enemy.h"
#include "Includes.h"
#include "Window.h"
#include "MultiEnemy.h"
#include "Hero.h"
#include "Includes.h"
#include "ProgressBar.h"
#include "Text.h"
#include "Window.h"
#include "Score.h"

using namespace std;

int main(int argv, char **args) {
    srand(time(NULL));
    Uint64 prevTime = SDL_GetPerformanceCounter();
    Uint64 currTime, deltaTime;

    Window window("Sphere Siege", WINDOW_WIDTH, WINDOW_HEIGHT);
    Hero hero(20, 20, WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2 - 100, "res/triangle.png");
    Enemy enemy(20, 20, 60, 60, 2, "res/triangle.png");
    ProgressBar Health(120, 12, 20, 20, "HP", true, {0, 255, 0, 255});
    ProgressBar Progress(120, 12, 220, 20, "progress", true, {150, 150, 150, 255});
    Score score(0, "score: ", 520, 20, false);
    Score best(0, "best: ", 750, 20, true);
    MultiEnemy enemies;

    while (!window.isClosed()) {
        SDL_Event event;
        currTime = SDL_GetPerformanceCounter();
        deltaTime = currTime - prevTime;
        double dt = (double)deltaTime / SDL_GetPerformanceFrequency();

        if (SDL_PollEvent(&event)) {
            window.pollEvents(event);
        }

////// In progress
        enemy.update(hero.getX(), hero.getY());
        hero.intersect(enemy, score);
        enemy.draw();
        Progress.draw();
        Health.draw();
        score.draw();
        best.draw();
        if (score.getScore() >= best.getScore()) {
            best.update(score.getScore());
        }
        Health.update(0.8);
        Progress.update(0);
        hero.draw();
        hero.pollEvents(dt);
        hero.update(dt);
        enemies.generateEnemy(hero);
        window.clear();
        prevTime = currTime;
    }

    return 0;
}
