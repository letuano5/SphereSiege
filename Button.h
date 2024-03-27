#pragma once
#include "Includes.h"
class Button {
   public:
    Button(int w, int h, int x, int y, string label);
    ~Button();
    bool isClicked(int mouseX, int mouseY) const;
    void updateHover(int mouseX, int mouseY);
    void draw();
    int getW() { return w; };
    int getH() { return h; };
    int getX() { return x; };
    int getY() { return y; };
    void setColor(SDL_Color innerColor, SDL_Color outerColor) {
        this->innerColor = innerColor;
        this->outerColor = outerColor;
    }
    void setLabelColor(SDL_Color labelColor) { this->labelColor = labelColor; }
    SDL_Color innerColor = {45, 45, 45, 255};
    SDL_Color outerColor = {100, 100, 100, 255};
    SDL_Color labelColor = {200, 200, 200, 255};
    bool isMouseOver = false;

   private:
    int w, h;
    int x, y;
    string label;
};
