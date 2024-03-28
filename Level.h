#pragma once
#include "Includes.h"

class Level {
   public:
    Level();
    ~Level();
    void update(int curScore);
    int getLevel() const { return level; }
    double getLevelProgress();
    pair<int, int> levelData[5] = {{1, 50}, {2, 80}, {3, 150}, {4, 200}, {5, 250}};

    bool readLevel();
    void writeLevel();

   private:
    int level = 0;
    int curScore = 0;
    Mix_Chunk* levelup_sound = nullptr;
};
