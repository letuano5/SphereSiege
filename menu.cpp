#include "Menu.h"

#include "Button.h"
#include "Text.h"
#include "Window.h"

Menu::Menu(string menuType) : menuType(menuType) {}
Menu::~Menu() {}

void Menu::draw(int mouseX, int mouseY) const {
    SDL_Rect overlay = {x, y, w, h};
    SDL_SetRenderDrawColor(Window::renderer, 30, 30, 30, 255);
    SDL_RenderFillRect(Window::renderer, &overlay);
    int mX, mY;
    SDL_GetMouseState(&mX, &mY);
    if (menuType == "start") {
        Text title(Window::renderer, "res/font/PressStart2P.ttf", 42, "SPHERE SIEGE", {200, 200, 200, 255});
        Text credit(Window::renderer, "res/font/PressStart2P.ttf", 12, "Made with love by lto5", {35, 35, 35, 255});

        title.display(WINDOW_WIDTH / 2 - title.getW() / 2, WINDOW_HEIGHT * 0.2, Window::renderer);
        credit.display(WINDOW_WIDTH / 2 - credit.getW() / 2, WINDOW_HEIGHT * 0.8, Window::renderer);

        Button startBtn(200, 40, WINDOW_WIDTH / 2 - 100, title.getY() + title.getH() + 70, "PLAY");
        Button continueBtn(200, 40, WINDOW_WIDTH / 2 - 100, startBtn.getY() + startBtn.getH() + 10, "CONTINUE");
        Button statsBtn(200, 40, WINDOW_WIDTH / 2 - 100, continueBtn.getY() + continueBtn.getH() + 10, "STATS");
        startBtn.updateHover(mX, mY);
        if (canContinue) continueBtn.updateHover(mX, mY);
        statsBtn.updateHover(mX, mY);
        if (!canContinue) {
            continueBtn.setColor({45, 45, 45, 30}, {55, 55, 55, 30});
            continueBtn.setLabelColor({120, 120, 120, 30});
        }
        startBtn.draw();
        continueBtn.draw();
        statsBtn.draw();
        if (startBtn.isClicked(mouseX, mouseY)) {
            isStarted = 2;
            isContinued = 0;
        }
        if (continueBtn.isClicked(mouseX, mouseY) && canContinue) {
            isContinued = 1;
        }
    } else if (menuType == "pause") {
        Text title(Window::renderer, "res/font/PressStart2P.ttf", 42, "PAUSE", {200, 200, 200, 255});

        title.display(WINDOW_WIDTH / 2 - title.getW() / 2, WINDOW_HEIGHT * 0.2, Window::renderer);

        Button resumeBtn(200, 40, WINDOW_WIDTH / 2 - 100, title.getY() + title.getH() + 70, "RESUME");
        Button exitBtn(200, 40, WINDOW_WIDTH / 2 - 100, resumeBtn.getY() + resumeBtn.getH() + 10, "EXIT");
        resumeBtn.updateHover(mX, mY);
        exitBtn.updateHover(mX, mY);
        resumeBtn.draw();
        exitBtn.draw();
        if (resumeBtn.isClicked(mouseX, mouseY)) {
            isPaused = !isPaused;
        }
        if (exitBtn.isClicked(mouseX, mouseY)) {
            exit(0);
        }
    } else if (menuType == "lost") {
        Text title(Window::renderer, "res/font/PressStart2P.ttf", 42, "YOU LOST", {200, 200, 200, 255});

        title.display(WINDOW_WIDTH / 2 - title.getW() / 2, WINDOW_HEIGHT * 0.2, Window::renderer);

        Button restartBtn(200, 40, WINDOW_WIDTH / 2 - 100, title.getY() + title.getH() + 70, "RESTART");
        Button exitBtn(200, 40, WINDOW_WIDTH / 2 - 100, restartBtn.getY() + restartBtn.getH() + 10, "EXIT");
        restartBtn.updateHover(mX, mY);
        exitBtn.updateHover(mX, mY);
        restartBtn.draw();
        exitBtn.draw();
        if (restartBtn.isClicked(mouseX, mouseY)) {
            isPaused = false;
            isStarted = true;
            isLost = false;
        }
        if (exitBtn.isClicked(mouseX, mouseY)) {
            exit(0);
        }
    } else {
    }
}
