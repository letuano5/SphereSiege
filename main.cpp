#include "Includes.h"

#include "Window.h"
#include "Hero.h"
#include "Enemy.h"

using namespace std;

void pollEvents (Window &window, Hero &hero) {
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
        hero.pollEvents(event);
        window.pollEvents(event);
    }
}

int main(int argv, char** args) {
    Window window("Sphere Siege", WINDOW_WIDTH, WINDOW_HEIGHT);
    Hero hero(50, 50, WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2 - 100, "res/triangle.png");
    Enemy enemy(50, 50, 5, 5, 0.1, "res/enemy.png");

    while(!window.isClosed()) {
        hero.update();
        enemy.update(hero.getX(), hero.getY());
        hero.intersect(enemy.getX(), enemy.getY());
        pollEvents(window, hero);
        hero.draw();
        enemy.draw();
        window.clear();
    }

    return 0;
}
