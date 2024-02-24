#include <iostream>
#include <SDL.h>


#include "Window.h"
#include "Hero.h"

using namespace std;

const int WINDOW_WIDTH = 960;
const int WINDOW_HEIGHT = 540;


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

    while(!window.isClosed()) {
        hero.update();
        pollEvents(window, hero);
        hero.draw();
        window.clear();
    }

    return 0;
}
