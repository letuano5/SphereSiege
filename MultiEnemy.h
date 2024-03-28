#pragma once

#include "Enemy.h"
#include "Explosion.h"
#include "Hero.h"
#include "Includes.h"
#include "Score.h"
// seconds
const double MAX_DIFF_TIME = 1;
const double MIN_BIG = 1;
const double MIN_SMALL = 1;
const double MIN_SPILLTER = 1;

const double SLOW_RATE = 3;
const double itemActiveTime = 5;

class MultiEnemy {
   public:
    MultiEnemy();
    ~MultiEnemy();
    void generateEnemy(Hero& hero, Score& score, Camera& camera, int curLevel);
    Uint32 lastSlow = 0;
    bool isSlow = false;
    void setSlow(bool isSlow);
    void saveEnemies();
    bool setEnemies();
    vector<Enemy*>& getEnemies() { return enemies; }

   private:
    vector<Enemy*> enemies;
    vector<Explosion*> explosions;
    void killEnemy(int& index);
    void clearE();
    double passedSecond();
    bool checkTime();
    clock_t lastTimeSpawned = clock();
    Mix_Chunk* explosion_sound = nullptr;
};
