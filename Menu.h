#pragma once

#include <string>

#include "Includes.h"
#include "Stats.h"

class Menu {
   public:
    Menu(string menuType);
    ~Menu();

    void draw(int mouseX, int mouseY);
    string menuType;
    string statPlaceholders[7] = {
        "BEST SCORE",
        "BEST LEVEL",
        "ROUNDS PLAYED",
        "ENEMIES KILLED",
        "ITEMS COLLECTED",
        "BULLETS FIRED",
        "TIME ELAPSED",
    };
    enum StatsType {
        BEST_SCORE = 0,
        BEST_LEVEL = 1,
        ROUNDS_PLAYED = 2,
        ENEMIES_KILLED = 3,
        ITEMS_COLLECTED = 4,
        BULLETS_FIRED = 5,
        TIME_ELAPSED = 6
    };
    vector<int> dat;
    bool readStats();
    void writeStats();

   private:
    int x = 0,
        y = 0;
    int w = WINDOW_WIDTH, h = WINDOW_HEIGHT;
};
