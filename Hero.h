#pragma once

#include "Includes.h"
#include "Window.h"
#include "Bullet.h"


class Hero {
   public:
    Hero(int w, int h, int x, int y, const string &image_path);
    ~Hero();

    void draw() const;
    void shoot();
    void update();
    void pollEvents(SDL_Event &event);
    int intersect(double enemyX, double enemyY);
    int getX() const { return x; }
    int getY() const { return y; }

   private:
    int w, h;
    int x, y;
    int r, g, b, a;

    SDL_Texture *triangle_texture = nullptr;
    vector<Bullet> bullets;
};
