#pragma once
#include "Includes.h"
class Button {
   public:
    Button(int w, int h, int x, int y, string label);
    ~Button();
    bool isClicked(int mouseX, int mouseY) const;
    void draw() const;
    int getW() { return w; };
    int getH() { return h; };
    int getX() { return x; };
    int getY() { return y; };
    bool isClicked();

   private:
    int w, h;
    int x, y;
    string label;
};
