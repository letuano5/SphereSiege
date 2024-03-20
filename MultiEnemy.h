#pragma once

#include "Enemy.h"
#include "Hero.h"
#include "Includes.h"
#include "Score.h"

// seconds
const double MAX_DIFF_TIME = 1;
const double MIN_BIG = 5;
const double MIN_SMALL = 7;
const double MIN_SPILLTER = 10;

const double SLOW_RATE = 3;
const double itemActiveTime = 5;

class MultiEnemy {
   public:
    MultiEnemy();
    ~MultiEnemy();
    void generateEnemy(Hero& hero, Score& score, const Camera& camera);
    Uint32 lastSlow = 0;
    bool isSlow = false;
    void setSlow(bool isSlow);

   private:
    vector<Enemy*> enemies;
    void killEnemy(int& index);
    double passedSecond();
    bool checkTime();
    clock_t lastTimeSpawned = clock();
};
