#pragma once

#include <vector>

#include "Enemy.h"

using namespace std;

class Bullet {
   public:
    Bullet(int x, int y, double angle);
    ~Bullet();
    void draw() const;
    void update(double dt);
//    void checkCollision(vector<Enemy>& enemies);
//    SDL_Rect getRect() const;
//    bool isOffScreen() const;

    int getX() const { return x; }
    int getY() const { return y; }
    int getH() const { return h; }
    int getW() const { return w; }

    struct {
        int r = 230;
        int g = 230;
        int b = 230;
        int a = 255;
    } Color;

   private:
    int x, y;
    static constexpr int w = 5, h = 5;
    static constexpr double speed = 700.0;
    double angle;
//    bool isColliding(const SDL_Rect& a, const SDL_Rect& b) const;
};
