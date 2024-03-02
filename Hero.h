#pragma once

#include "Bullet.h"
#include "Enemy.h"
#include "Includes.h"
#include "Window.h"
#include "Score.h"

using namespace std;

class Hero {
   public:
    Hero(int w, int h, int x, int y, const string &image_path);

    ~Hero();

    double fireRate = 0.1;
    double lastShot = 0.0;
    double moveSpeed = 300.0;
    double dmg = 0.1;

    void draw() const;
    void shoot(int mouseX, int mouseY);
    void update(double dt);
    void pollEvents(double dt);
    int intersect(int enemyW, int enemyH, int enemyX, int enemyY, Score& score) const;
    int getX() const { return x; }
    int getY() const { return y; }
    int getW() const { return w; }
    int getH() const { return h; }

   private:
    int w, h;
    int x, y;
    int r, g, b, a;

    SDL_Texture *triangle_texture = nullptr;
    vector<Bullet> bullets;
};
