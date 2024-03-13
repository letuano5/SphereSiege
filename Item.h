#pragma once
#include "Includes.h"
#include "Text.h"
#include "Camera.h"
#include "Window.h"

class Item {
public:
    Item(double x, double y, string type);
    ~Item();
    void draw(const Camera &camera);
    void update();
private:
    double x, y;
    const double direction = randDouble(0, 2 * PI);
    const double speed = randDouble(0.5, 2);
    const string type;
};
