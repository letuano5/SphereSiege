#pragma once
#include <string>

#include "Bullet.h"
#include "Window.h"

using namespace std;

class Hero {
   public:
    Hero(int w, int h, int x, int y, const string &image_path);

    ~Hero();

    double fireRate = 0.1;
    double lastShot = 0.0;
    double moveSpeed = 300.0;

    void draw() const;
    void shoot(int mouseX, int mouseY);
    void update(double dt);
    void pollEvents(double dt);

   private:
    int w, h;
    int x, y;
    int r, g, b, a;

    SDL_Texture *triangle_texture = nullptr;
    vector<Bullet> bullets;
};
