#pragma once
#include "Hero.h"
#include "Includes.h"
#include "Item.h"

// seconds
const int DIF_SPAWN_TIME = 1;
const string itemTypes[] = {"FAST_SHOT", "HP_PACK", "SLOWDOWN_ENEMIES", "TRIPPLE_SHOT", "PIERCE_SHOT"};

class Items {
   public:
    Items();
    ~Items();
    void spawnItem(Hero& hero, const Camera& camera);
    clock_t lastTimeSpawned = clock();
    bool checkTime();

   private:
    vector<Item*> items;
};
