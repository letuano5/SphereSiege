#pragma once
#include "Hero.h"
#include "Includes.h"
#include "Item.h"
#include "Menu.h"
#include "ProgressBar.h"

// seconds
const double DIF_SPAWN_TIME = 15;
const int activeTime = 5;
const string itemTypes[] = {"FAST_SHOT", "HP_PACK", "SLOWDOWN_ENEMIES", "TRIPPLE_SHOT", "PIERCE_SHOT", "SHIELD"};
const string itemDirPath[] = {"res/image/item_fastshot.png", "res/image/item_hppack.png", "res/image/item_slowdownenemies.png", "res/image/item_tripleshot.png", "res/image/item_pierceshot.png", "res/image/item_shield.png"};

class Items {
   public:
    Items();
    ~Items();
    void spawnItem(Hero& hero, const Camera& camera, MultiEnemy& enemies, Menu& stats);
    // clock_t lastTimeS/pawned = clock();
    Uint32 lastTimeSpawned = 0;
    bool checkTime();
    pair<string, SDL_Color> itemProgressTypes[5] = {{"FAST_SHOT", {158, 0, 89, 255}}, {"TRIPPLE_SHOT", {255, 243, 0, 255}}, {"PIERCE_SHOT", {255, 183, 3, 255}}, {"SLOWDOWN_ENEMIES", {30, 150, 252, 255}}, {"SHIELD", {199, 198, 197, 255}}};
    vector<pair<string, ProgressBar*>> itemsProgress;
    void saveItem();
    bool setItem();
    vector<Item*>& getItems() { return items; }

   private:
    vector<Item*> items;
    map<string, Uint32> activeItems;
    SDL_Color textColor = {100, 100, 100, 255};
    SDL_Color textActiveColor = {188, 188, 188, 255};
    Mix_Chunk* powerUp_sound = nullptr;
};
