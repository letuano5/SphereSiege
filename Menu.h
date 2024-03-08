#pragma once

#include "Includes.h"
#include <string>

class Menu {
public:
    Menu (string menuType);
    ~Menu();

    void draw(int mouseX, int mouseY) const;
    string menuType;

private:
    int x = 0, y = 0;
    int w = WINDOW_WIDTH, h = WINDOW_HEIGHT;
};
