#pragma once

#include "Camera.h"
#include "Includes.h"
#include "Window.h"

class Explosion {
    vector<SDL_Texture*> frames;
    double x, y;
    int currentFrame = 0;
    const int numFrames = 31;
    const string framePath = "res/explosion/";

   public:
    Explosion(double x, double y);
    ~Explosion();

    void update();

    void draw(Camera& camera) const;

    bool isDone() const;
};
