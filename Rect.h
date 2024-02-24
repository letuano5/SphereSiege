#pragma once
#include <string>

#include "Window.h"

class Rect {
   public:
    Rect(int w, int h, int x, int y, int r, int g, int b, int a);
    Rect(int w, int h, int x, int y, const string &image_path);
    ~Rect();

    void draw() const;
    void pollEvents(SDL_Event &event);

   private:
    int w, h;
    int x, y;
    int r, g, b, a;

    SDL_Texture *triangle_texture = nullptr;
};
