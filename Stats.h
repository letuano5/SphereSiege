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
    // string getStatsData(int index) const {
    //     switch (index) {
    //         case 0:
    //             return to_string(bestScore);
    //         case 1:
    //             return to_string(bestLevel);
    //         case 2:
    //             return to_string(playedRound);
    //         case 3:
    //             return to_string(killedEnemies);
    //         case 4:
    //             return to_string(firedBullets);
    //         case 5:
    //             return to_string(collectedItems);
    //         case 6: {
    //             cout << timeElapsed << endl;
    //             int s = timeElapsed / 1000;
    //             return to_string(s / 3600) + ":" + to_string((s % 3600) / 60) + ":" + to_string(((s % 3600) % 60));
    //         }
    //         default:
    //             return "";
    //     }
    // }
};
