#pragma once
#include "Camera.h"
#include "Hero.h"
#include "Includes.h"
#include "MultiEnemy.h"
#include "Text.h"
#include "Window.h"

class Item {
   public:
    Item(double x, double y, double dir, double speed, string type);
    Item(string type);
    ~Item();
    void draw(const Camera &camera);
    void update();
    bool intersect(double x, double y, double w, double h);
    bool isOutOfBounds() const;
    bool isOutOfMap() const;
    void applyEffect(Hero &hero, MultiEnemy &enemies);
    string getType() const { return type; }
    double getX() const { return x; }
    double getY() const { return y; }
    int getW() const { return w; }
    int getH() const { return h; }
    double getDir() const { return direction; }
    double getSpeed() const { return speed; }
    SDL_Color getInnerColor() const { return innerColor; }
    SDL_Color getOuterColor() const { return outerColor; }

   private:
    double x, y;
    int w = 200, h = 24;
    double direction = randDouble(0, 2 * PI);
    double speed = randDouble(20, 100);
    const string type;
    SDL_Color innerColor, outerColor;
};
