#pragma once
#include "Includes.h"

class Level {
   public:
    Level();
    ~Level();
    void update(int curScore);
    void drawLevelInfo() const;
    int getLevel() const { return level; }
    double getLevelProgress();

    bool readLevel();
    void writeLevel();
    bool donePhase() {
        --numPhase;
        numMonster = 0;
        return numPhase == 0;
    }
    int getNumMonster() const { return numMonster; }
    int getKilledMonster() const { return killedMonster; }
    void setRemainMonster(int remainMonsters) { this->remainMonsters = remainMonsters; }
    void upLevel();
    int maxLevel = 0;

   private:
    void printLevel();
    int remainMonsters = 0;
    int level = 0;
    int curScore = 0;
    int numPhase = 0;
    int initNumPhase = 0;
    int numMonster = 0;
    int killedMonster = 0;
    int limitMonster = 0;
    Mix_Chunk* levelup_sound = nullptr;
};
