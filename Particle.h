#pragma once

#include "Camera.h"
#include "Includes.h"
#include "Window.h"
class Particle {
   public:
    Particle(double x, double y, double speed, double friction, double direction, double lineWidth, SDL_Color color);
    ~Particle();
    void draw(Camera& camera);
    void update();
    double getSpeed() const { return speed; }

   private:
    double x, y;
    int w, h;
    double speed;
    double friction;
    double direction;
    double lineWidth;
    SDL_Color color;
};
