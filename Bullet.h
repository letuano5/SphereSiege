#pragma once

#include "Camera.h"
#include "Includes.h"
#include "Window.h"

using namespace std;

class Bullet {
   public:
    Bullet(int x, int y, double angle);
    ~Bullet();
    void draw(const Camera& camera) const;
    void update(double dt);
    bool outOfBound();
    bool bulletOutOfMap() const;
    bool outOfCamera(const Camera& camera) const;

    int getX(const Camera& camera) const { return x - camera.getX(); }
    int getY(const Camera& camera) const { return y - camera.getY(); }
    int getX() const { return x; }
    int getY() const { return y; }
    int getH() const { return h; }
    int getW() const { return w; }
    double getAngle() const { return angle; }
    void setX(int x) { this->x = x; }
    void setY(int y) { this->y = y; }

    SDL_Color color = {230, 230, 230, 255};

   private:
    int x, y;
    static constexpr int w = 4, h = 4;
    static constexpr double speed = 700.0;
    double angle;
};
