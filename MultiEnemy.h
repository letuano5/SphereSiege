#pragma once

#include "Includes.h"
#include "Hero.h"
#include "Enemy.h"
#include "Score.h"

// seconds
const int MAX_DIFF_TIME = 1;

class MultiEnemy {
public:
    MultiEnemy();
    ~MultiEnemy();
    void generateEnemy(Hero& hero, Score& score);
    clock_t lastTimeSpawned = clock();
    bool checkTime();
private:
    vector<Enemy*> enemies;
};
