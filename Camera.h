#pragma once

#include "Includes.h"

class Camera {
public:
    Camera();
    Camera(int leftX, int leftY);
    int getX() const { return leftX; }
    int getY() const { return leftY; }
    void adjust(int heroX, int heroY, int heroW, int heroH);
    void saveCamera();
    bool setCamera();
private:
    int leftX = 0, leftY = 0;
};
