#pragma once
#include "Camera.h"
#include "Hero.h"
#include "Includes.h"
#include "MultiEnemy.h"
#include "Text.h"
#include "Window.h"

class Item {
   public:
    Item(double x, double y, double dir, double speed, string type, string path);
    Item(string type, string path);
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
    string getPath() const { return path; }
    double getSpeed() const { return speed; }
    SDL_Color getAccentColor() const { return accentColor; }

   private:
    double x, y;
    int w = 100, h = 25;
    double direction = randDouble(0, 2 * PI);
    double speed = randDouble(20, 100);
    const string type;
    string path;
    SDL_Color accentColor;
    SDL_Texture *item_texture = nullptr;
};
