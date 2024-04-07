#pragma once

#include <string>

#include "Includes.h"

class Menu {
   public:
    Menu(string menuType);
    ~Menu();

    void draw(int mouseX, int mouseY) const;
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

   private:
    int x = 0,
        y = 0;
    int w = WINDOW_WIDTH, h = WINDOW_HEIGHT;
};
