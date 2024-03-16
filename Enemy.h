#pragma once

#include "Includes.h"
#include "Window.h"
#include "Camera.h"

class Enemy {

public:
    Enemy(int w, int h, double x, double y, double speed, double angle, double canSpilt, double hp, double dmg, const string &image_path);
    ~Enemy();
    void draw(const Camera& camera);
    void update(int heroX, int heroY);
    double getX() const { return x; }
    double getY() const { return y; }
    int getW() const { return w; }
    int getH() const { return h; }
    double getAngle() const { return angle; }
    double getHP() const { return health_point; }
    void takeDmg(double dmg);
    bool enemyOutOfBound(int leftBound) const;
    bool canSpilt;
    double dmg = 0.1;

   private:
    int w, h;
    double x, y;
    double angle = randDouble(0, 2 * PI);
    double speed;
    int hp_w = 30, hp_h = 4;
    double health_point = 1;
    double max_health_point = 1;
    double rotateSpeed = randInt(1, 2);
    double rotateAngle = 0;
    bool canShiftAngle = randInt(0, 1);
    SDL_Texture *triangle_texture = nullptr;
    double randomAngle();
};
