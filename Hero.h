#pragma once

#include <map>

#include "Bullet.h"
#include "Camera.h"
#include "Enemy.h"
#include "Includes.h"
#include "Score.h"
#include "Window.h"

using namespace std;

class Hero {
   public:
    Hero() {}
    Hero(int w, int h, int x, int y, const string& image_path);

    ~Hero();

    double fireRate = 0.1;
    double lastShot = 0.0;
    double moveSpeed = 300.0;
    double dmg = 0.1;
    double health_point = 1;
    double maxHealth = 1;
    int shakeDuration = 0;
    int shakeIntensity = 0;

    double enemyDmgRate = 0.1;
    double enemyLastHit = 0.0;

    void draw(Camera& camera);
    void shoot(int mouseX, int mouseY);
    void update();
    void pollEvents(const Camera& camera);
    int intersect(int enemyW, int enemyH, double enemyX, double enemyY, Score& score, double enemyDmg);
    int getX(const Camera& camera) const { return x - camera.getX(); }
    int getY(const Camera& camera) const { return y - camera.getY(); }
    int getX() const { return x; }
    int getY() const { return y; }
    int getW() const { return w; }
    int getH() const { return h; }
    double getHealth() const { return health_point; }
    double getDamage() const { return dmg; }
    void setFastShot(bool fastShoot);
    void setHealth(double health);
    void setTrippleShot(bool trippleShot);
    void setPierceShot(bool setPierceShot);
    void saveHero();
    bool setHero();
    vector<Bullet>& getBullets() { return bullets; }

   private:
    int w,
        h;
    int x, y;
    int r, g, b, a;
    bool fastShoot = false;
    bool trippleShot = false;
    bool pierceShot = false;

    SDL_Texture* triangle_texture = nullptr;
    SDL_Texture* vignette_texture = nullptr;
    Mix_Chunk* shoot_sound = nullptr;
    vector<Bullet> bullets;
};
