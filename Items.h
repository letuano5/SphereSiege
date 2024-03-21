#pragma once
#include "Hero.h"
#include "Includes.h"
#include "Item.h"
#include "ProgressBar.h"
// seconds
const double DIF_SPAWN_TIME = 1;
const string itemTypes[] = {"FAST_SHOT", "HP_PACK", "SLOWDOWN_ENEMIES", "TRIPPLE_SHOT", "PIERCE_SHOT"};

class Items {
   public:
    Items();
    ~Items();
    void spawnItem(Hero& hero, const Camera& camera, MultiEnemy& enemies);
    clock_t lastTimeSpawned = clock();
    bool checkTime();
    pair<string, SDL_Color> itemProgressTypes[4] = {{"FAST SHOT", {138, 201, 38, 255}}, {"TRIPPLE SHOT", {0, 180, 216, 255}}, {"PIERCE SHOT", {243, 144, 44, 255}}, {"SLOWDOWN ENEMIES", {128, 128, 128, 255}}};
    ProgressBar* itemsProgress[4] = {NULL, NULL, NULL, NULL};

   private:
    vector<Item*> items;
    map<string, Uint32> activeItems;
};
