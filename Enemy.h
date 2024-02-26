#pragma once

#include "Includes.h"
#include "Window.h"
#include "Hero.h"

class Enemy {
public:
    Enemy(int w, int h, double x, double y, double speed, const string &image_path);
    ~Enemy();
    void draw();
    void update(int heroX, int heroY);
    double getX() const { return x; }
    double getY() const { return y; }

private:
    int w, h;
    double x, y;
    double speed;
    SDL_Texture *triangle_texture = nullptr;
};
