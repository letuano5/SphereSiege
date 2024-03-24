#pragma once

#include "Includes.h"

using namespace std;

class ProgressBar {
   public:
    ProgressBar(int w, int h, int x, int y, string label, bool hasOutline, SDL_Color color, SDL_Color textColor);
    ProgressBar();
    ~ProgressBar();

    void draw();
    void update(double progress);
    void setTextColor(SDL_Color textColor) { this->textColor = textColor; }

    double progress = 0;
    int _w = 0;
    int x, y, w, h;
    SDL_Color color;
    SDL_Color textColor;
    string label;

   private:
    bool hasOutline = false;
};
