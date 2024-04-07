#pragma once

#include "Includes.h"

class Stats {
public:
    int bestScore = 0;
    int bestLevel = 0;
    int playedRound = 0;
    int killedEnemies = 0;
    int firedBullets = 0;
    int collectedItems = 0;
    int timeElapsed = 0;
    Stats();
    ~Stats();
    void writeStats();
    bool readStats();
    void printStats();
    void reset();
};
