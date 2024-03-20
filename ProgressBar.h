#pragma once

#include "Includes.h"

using namespace std;

class ProgressBar {
   public:
    ProgressBar(int w, int h, int x, int y, string label, bool hasOutline, SDL_Color color);
    ProgressBar();
    ~ProgressBar();

    void draw() const;
    void update(double progress);

    double progress = 0;
    int _w = 0;
    int x, y, w, h;
    SDL_Color color;
    string label;

   private:
    bool hasOutline = false;
};
