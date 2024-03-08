#pragma once

#include "Includes.h"
#include "Window.h"
#include "Camera.h"

class Enemy {

public:
    Enemy(int w, int h, double x, double y, double speed, double rotateSpeed, const string &image_path);
    ~Enemy();
    void draw(const Camera& camera);
    void update(int heroX, int heroY);
    double getX() const { return x; }
    double getY() const { return y; }
    int getW() const { return w; }
    int getH() const { return h; }
    void takeDmg(double dmg);
    double health_point = 1;
    int max_health_point = 1;

   private:
    int w, h;
    double x, y;
    double speed;
    int hp_w = 30, hp_h = 4;
    double rotateSpeed = 2;
    double rotateAngle = 0;
    SDL_Texture *triangle_texture = nullptr;
};
