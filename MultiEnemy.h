#pragma once

#include "Enemy.h"
#include "Explosion.h"
#include "Hero.h"
#include "Includes.h"
#include "Level.h"
#include "ParticleEmitter.h"
#include "Score.h"
#include "Menu.h"

// seconds
const double MAX_DIFF_TIME = 1;
const double MIN_BIG = 1;
const double MIN_SMALL = 1;
const double MIN_SPILLTER = 1;

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
    vector<ParticleEmitter> emitters;
    vector<Enemy*> enemies;
    vector<Explosion*> explosions;
    void generateSingleEnemy(Hero& hero, Score& score, Camera& camera, Level& level);
    void killEnemy(int& index);
    void clearE();
    double passedSecond();
    bool checkTime();
    bool canReachMap(double posX, double posY, double angle) const;
    clock_t lastTimeSpawned = clock();
    Mix_Chunk* explosion_sound = nullptr;
};
