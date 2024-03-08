#pragma once

#include "Camera.h"
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

    void draw(Camera& camera);
    void shoot(int mouseX, int mouseY);
    void update(double dt);
    void pollEvents(double dt);
    int intersect(int enemyW, int enemyH, double enemyX, double enemyY, Score& score);
    int getX(const Camera& camera) const { return x - camera.getX(); }
    int getY(const Camera& camera) const { return y - camera.getY(); }
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
