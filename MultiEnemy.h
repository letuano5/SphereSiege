#pragma once

#include "Enemy.h"
#include "Explosion.h"
#include "Hero.h"
#include "Includes.h"
#include "Level.h"
#include "Menu.h"
#include "ParticleEmitter.h"
#include "PopupText.h"
#include "Score.h"

const double SLOW_RATE = 3;
const double itemActiveTime = 5;

class MultiEnemy {
   public:
    MultiEnemy();
    ~MultiEnemy();
    void generateEnemy(Hero& hero, Score& score, Camera& camera, Level& level, Menu& stats);
    Uint32 lastSlow = 0;
    bool isSlow = false;
    void setSlow(bool isSlow);
    void saveEnemies();
    bool setEnemies();
    vector<Enemy*>& getEnemies() { return enemies; }

   private:
    vector<PopupText> pTexts;
    vector<ParticleEmitter> emitters;
    vector<Enemy*> enemies;
    vector<Explosion*> explosions;
    void generateSingleEnemy(Hero& hero, Score& score, Camera& camera, Level& level);
    void killEnemy(int& index);
    void clearE();
    Mix_Chunk* explosion_sound = nullptr;
};
