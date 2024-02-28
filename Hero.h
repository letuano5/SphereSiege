#pragma once

#include "Includes.h"
#include "Window.h"
#include "Bullet.h"

using namespace std;

class Hero {
   public:
    Hero(int w, int h, int x, int y, const string &image_path);

    ~Hero();

    double fireRate = 0.1;
    double lastShot = 0.0;
    double moveSpeed = 300.0;

    void draw() const;
    void shoot(int mouseX, int mouseY);
    void update(double dt);
    void pollEvents(double dt);
    int intersect(int enemyW, int enemyH, int enemyX, int enemyY) const;
    int getX() const { return x; }
    int getY() const { return y; }

   private:
    int w, h;
    int x, y;
    int r, g, b, a;

    SDL_Texture *triangle_texture = nullptr;
//    Bullet bullets[50005];
    vector<Bullet> bullets;
};
