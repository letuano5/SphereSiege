
#include "Includes.h"
#include "Window.h"
#include "MultiEnemy.h"
#include "Hero.h"
using namespace std;


int main(int argv, char** args) {
    srand(time(NULL));
    Uint64 prevTime = SDL_GetPerformanceCounter();
    Uint64 currTime, deltaTime;

    Window window("Sphere Siege", WINDOW_WIDTH, WINDOW_HEIGHT);
    Hero hero(20, 20, WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2 - 100, "res/triangle.png");
    MultiEnemy enemies;

    while (!window.isClosed()) {
        SDL_Event event;
        currTime = SDL_GetPerformanceCounter();
        deltaTime = currTime - prevTime;
        double dt = (double)deltaTime / SDL_GetPerformanceFrequency();

        hero.draw();
        hero.pollEvents(dt);
        hero.update(dt);

        if (SDL_PollEvent(&event)) {
            window.pollEvents(event);
        }

        enemies.generateEnemy(hero);
        window.clear();
        prevTime = currTime;

    }

    return 0;
}
