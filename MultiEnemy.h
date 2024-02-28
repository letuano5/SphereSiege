#pragma once

#include "Includes.h"
#include "Hero.h"
#include "Enemy.h"

// microseconds
const int MAX_DIFF_TIME = 3000;

class MultiEnemy {
public:
    MultiEnemy();
    void generateEnemy(const Hero& hero);
private:
    vector<Enemy> enemies;
};
