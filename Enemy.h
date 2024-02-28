#pragma once

#include "Includes.h"
#include "Window.h"

class Enemy {
public:
    Enemy(int w, int h, double x, double y, double speed, double rotateSpeed, const string &image_path);
    ~Enemy();
    void draw();
    void updateEnemy(int heroX, int heroY);
    double getX() const { return x; }
    double getY() const { return y; }
    int getW() const { return w; }
    int getH() const { return h; }
    void decreaseHealthPoint(int delta) { healthPoint -= delta; }
    int getHealthPoint() const { return healthPoint; }

private:
    int w, h;
    double x, y;
    double speed;
    double rotateSpeed = 2;
    double rotateAngle = 0;
    int healthPoint = 1;
    SDL_Texture *triangle_texture = nullptr;
};
