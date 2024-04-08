#include "Menu.h"

#include "Button.h"
#include "Text.h"
#include "Window.h"

Menu::Menu(string menuType) : menuType(menuType), dat(7, 0) {}
Menu::~Menu() {}

string formatNumber(int num) {
    string str = to_string(num);
    reverse(str.begin(), str.end());
    for (int i = 3; i < str.length(); i += 4) {
        str.insert(i, " ");
    }
    reverse(str.begin(), str.end());
    return str;
}

void Menu::draw(int mouseX, int mouseY) {
    SDL_Rect overlay = {x, y, w, h};
    SDL_SetRenderDrawColor(Window::renderer, 30, 30, 30, 255);
    SDL_RenderFillRect(Window::renderer, &overlay);
    int mX, mY;
    SDL_GetMouseState(&mX, &mY);
    if (menuType == "start") {
        Text title("res/font/PressStart2P.ttf", 42, "SPHERE SIEGE", {200, 200, 200, 255});

        title.display(WINDOW_WIDTH / 2 - title.getW() / 2, WINDOW_HEIGHT * 0.2);

        Button startBtn(200, 40, WINDOW_WIDTH / 2 - 100, title.getY() + title.getH() + 70, "PLAY");
        Button continueBtn(200, 40, WINDOW_WIDTH / 2 - 100, startBtn.getY() + startBtn.getH() + 10, "CONTINUE");
        Button statsBtn(200, 40, WINDOW_WIDTH / 2 - 100, continueBtn.getY() + continueBtn.getH() + 10, "STATS");
        Button exitBtn(200, 40, WINDOW_WIDTH / 2 - 100, statsBtn.getY() + statsBtn.getH() + 10, "EXIT");
        startBtn.updateHover(mX, mY);
        if (canContinue) continueBtn.updateHover(mX, mY);
        statsBtn.updateHover(mX, mY);
        exitBtn.updateHover(mX, mY);
        if (!canContinue) {
            continueBtn.setColor({45, 45, 45, 30}, {55, 55, 55, 30});
            continueBtn.setLabelColor({120, 120, 120, 30});
        }
        startBtn.draw();
        continueBtn.draw();
        statsBtn.draw();
        exitBtn.draw();
        if (startBtn.isClicked(mouseX, mouseY)) {
            isStarted = 2;
            isContinued = 0;
        }
        if (continueBtn.isClicked(mouseX, mouseY) && canContinue) {
            isContinued = 1;
        }
        if (statsBtn.isClicked(mouseX, mouseY)) {
            isStatsShow = true;
        }
        if (exitBtn.isClicked(mouseX, mouseY)) {
            exit(0);
        }

    } else if (menuType == "pause") {
        Text title("res/font/PressStart2P.ttf", 42, "PAUSE", {200, 200, 200, 255});

        title.display(WINDOW_WIDTH / 2 - title.getW() / 2, WINDOW_HEIGHT * 0.2);

        Button resumeBtn(200, 40, WINDOW_WIDTH / 2 - 100, title.getY() + title.getH() + 70, "RESUME");
        Button menuBtn(200, 40, WINDOW_WIDTH / 2 - 100, resumeBtn.getY() + resumeBtn.getH() + 10, "MENU");
        resumeBtn.updateHover(mX, mY);
        menuBtn.updateHover(mX, mY);
        resumeBtn.draw();
        menuBtn.draw();
        if (resumeBtn.isClicked(mouseX, mouseY)) {
            isPaused = !isPaused;
        }
        if (menuBtn.isClicked(mouseX, mouseY)) {
            isPaused = false;
            isStarted = false;
        }
    } else if (menuType == "lost") {
        Text title("res/font/PressStart2P.ttf", 42, "YOU LOST", {200, 200, 200, 255});

        title.display(WINDOW_WIDTH / 2 - title.getW() / 2, WINDOW_HEIGHT * 0.2);

        Button restartBtn(200, 40, WINDOW_WIDTH / 2 - 100, title.getY() + title.getH() + 70, "RESTART");
        Button menuBtn(200, 40, WINDOW_WIDTH / 2 - 100, restartBtn.getY() + restartBtn.getH() + 10, "MENU");
        restartBtn.updateHover(mX, mY);
        menuBtn.updateHover(mX, mY);
        restartBtn.draw();
        menuBtn.draw();
        if (restartBtn.isClicked(mouseX, mouseY)) {
            isPaused = false;
            isStarted = true;
            isLost = false;
        }
        if (menuBtn.isClicked(mouseX, mouseY)) {
            isPaused = false;
            isStarted = false;
            isLost = false;
        }
    } else if (menuType == "stats") {
        Text title("res/font/PressStart2P.ttf", 42, "STATS", {200, 200, 200, 255});

        title.display(WINDOW_WIDTH / 2 - title.getW() / 2, WINDOW_HEIGHT * 0.2);

        int lastPlaceholderY;
        for (int i = 0; i < 7; i++) {
            Text stat("res/font/PressStart2P.ttf", 12, statPlaceholders[i], {130, 130, 130, 255});
            stat.display(WINDOW_WIDTH / 2 - stat.getW() - 10, title.getY() + title.getH() + 30 + i * 20);

            string valueStr;
            if (i == 6) {
                int s = dat[i] / 1000;
                string hour = to_string(s / 3600);
                s %= 3600;
                string minutes = to_string(s / 60);
                s %= 60;
                string seconds = to_string(s);
                while (hour.size() < 2) hour = '0' + hour;
                while (minutes.size() < 2) minutes = '0' + minutes;
                while (seconds.size() < 2) seconds = '0' + seconds;
                valueStr = hour + ":" + minutes + ":" + seconds;
            } else {
                valueStr = to_string(dat[i]);
            }

            Text value("res/font/PressStart2P.ttf", 12, valueStr, {180, 180, 180, 255});
            value.display(WINDOW_WIDTH / 2 + 10, title.getY() + title.getH() + 30 + i * 20);
            lastPlaceholderY = stat.getY();
        }
        Button clearDataBtn(200, 40, WINDOW_WIDTH / 2 - 100, lastPlaceholderY + 50, "CLEAR DATA");
        Button menuBtn(200, 40, WINDOW_WIDTH / 2 - 100, clearDataBtn.getY() + clearDataBtn.getH() + 10, "MENU");
        menuBtn.updateHover(mX, mY);
        clearDataBtn.updateHover(mX, mY);
        menuBtn.draw();
        clearDataBtn.draw();

        if (clearDataBtn.isClicked(mouseX, mouseY)) {
            dat.assign(7, 0);
            writeStats();
        }
        if (menuBtn.isClicked(mouseX, mouseY)) {
            isStatsShow = false;
        }
    }
}

void Menu::writeStats() {
    if (menuType != "stats") {
        return;
    }
    ofstream out("res/save/stats.txt");
    for (int x : dat) out << x << " ";
    out.close();
}

bool Menu::readStats() {
    if (menuType != "stats") {
        return false;
    }
    ifstream inp("res/save/stats.txt");
    vector<int> cur_data(7, -1);
    for (int& x : cur_data) {
        inp >> x;
    }
    inp.close();
    for (int x : cur_data) {
        if (x < 0 || x >= 1e9) {
            return false;
        }
    }
    dat.swap(cur_data);
    return true;
}
