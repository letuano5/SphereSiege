#include "MultiEnemy.h"
MultiEnemy::MultiEnemy() {
    ;
}

MultiEnemy::~MultiEnemy() {
    for (int i = 0; i < int(enemies.size()); i++) {
        delete enemies[i];
        enemies[i] = NULL;
    }
    enemies.clear();
}

bool MultiEnemy::checkTime() {
    clock_t currentTime = clock();
    int diffTime = (currentTime - lastTimeSpawned) / double(CLOCKS_PER_SEC);
    return diffTime > MAX_DIFF_TIME;
}

// https://stackoverflow.com/questions/42634068/sdl-using-a-stdvector-with-sdl-texture-does-not-work-array-works-fine
void MultiEnemy::generateEnemy(Hero& hero, Score& score) {
    if (enemies.empty() || checkTime()) {
        pair<int, int> currentPosition;
        do {
            currentPosition.first = randInt(0, WINDOW_WIDTH);
            currentPosition.second = randInt(0, WINDOW_HEIGHT);
        } while (!pointInBound(currentPosition.first, currentPosition.second));
        lastTimeSpawned = clock();
        enemies.push_back(new Enemy (32, 32, currentPosition.first, currentPosition.second, randDouble(1, 1.5), randInt(1, 2), "res/enemy.png"));
    }
    for (int i = 0; i < int(enemies.size()); i++) {
        enemies[i]->update(hero.getX(), hero.getY());
        if (rectOutOfBound(enemies[i]->getW(), enemies[i]->getH(), enemies[i]->getX(), enemies[i]->getY())) {
            delete enemies[i];
            enemies[i] = NULL;
            enemies.erase(enemies.begin() + i);
            i--;
            continue;
        }
        if (hero.intersect(enemies[i]->getW(), enemies[i]->getH(), enemies[i]->getX(), enemies[i]->getY(), score, enemies[i]->dmg) == WIN) {
            enemies[i]->takeDmg(hero.dmg);
        }
        if (enemies[i]->health_point <= EPS) {
            delete enemies[i];
            enemies[i] = NULL;
            score.update(1);
            enemies.erase(enemies.begin() + i);
            i--;
            continue;
        }
        enemies[i]->draw();
    }
}
