#pragma once
#include "Camera.h"
#include "Includes.h"
class PopupText {
   private:
    double x, y;
    string text;
    int size;
    double speed;
    SDL_Color color;
    double friction = 0.85;

   public:
    PopupText(double x, double y, string text, int size, double speed, SDL_Color color);
    ~PopupText();
    void update();
    void draw(Camera& camera);
    bool isDead() const { return speed <= 1.5; }
};