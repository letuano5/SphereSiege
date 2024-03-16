#pragma once
#include "Camera.h"
#include "Includes.h"
#include "Text.h"
#include "Window.h"
#include "Hero.h"
const int activeTime = 5;
class Item {
   public:
    Item(string type);
    ~Item();
    void draw(const Camera &camera);
    void update();
    bool intersect(double x, double y, double w, double h);
    bool isOutOfBounds() const;
    void applyEffect(Hero &hero);

   private:
    double x, y;
    int w = 100, h = 24;
    double direction = randDouble(0, 2 * PI);
    double speed = randDouble(0.5, 2);
    const string type;
};
