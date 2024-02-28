#pragma once

#include "Includes.h"
#include "Hero.h"
#include "Enemy.h"

// seconds
const int MAX_DIFF_TIME = 5;

class MultiEnemy {
public:
    MultiEnemy();
    ~MultiEnemy();
    void generateEnemy(const Hero& hero);
    clock_t lastTimeSpawned = clock();
    bool checkTime();
private:
    vector<Enemy*> enemies;
};
