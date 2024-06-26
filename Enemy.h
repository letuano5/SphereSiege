#pragma once

#include "Camera.h"
#include "Includes.h"
#include "Window.h"

class Enemy {
   public:
    Enemy(int w, int h, double x, double y, double speed, double angle, bool canSpilt, double hp, double dmg, int score, const string &image_path);
    ~Enemy();
    void draw(const Camera &camera);
    void update(int heroX, int heroY, double slowRate);
    double getX() const { return x; }
    double getY() const { return y; }
    int getW() const { return w; }
    int getH() const { return h; }
    int getScore() const { return score; }
    double getAngle() const { return angle; }
    double getHP() const { return health_point; }
    double getDamage() const { return dmg; }
    double getSpeed() const { return speed; }
    string getPath() const { return imagePath; }
    void takeDmg(double dmg);
    bool enemyOutOfMap() const;
    bool enemyOutOfBound(int leftBound) const;
    SDL_Color getAccentColor() const { return accentColor; }

    bool canSpilt;
    double dmg = 0.1;
    int score = 1;
    int isOut = 1;

   private:
    int w, h;
    double x, y;
    double angle = randDouble(0, 2 * PI);
    double speed;
    int hp_w = 30, hp_h = 4;
    double health_point = 1;
    double max_health_point = 1;
    double rotateSpeed = randInt(1, 2);
    double rotateAngle = 0;
    int canShiftAngle = randInt(0, 25);
    string imagePath;
    SDL_Texture *triangle_texture = nullptr;
    SDL_Color accentColor = {67, 155, 213, 255};
    double randomAngle();
};
