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

const int TOP = 0;
const int BOT = 1;
const int LEFT = 2;
const int RIGHT = 3;

const vector<string> OPTION_ANGLE = {"CHASE", "HORIZONTAL", "DIAGONAL", "RANDOM"};
const vector<string> DIRS = {"res/enemy.png", "res/enemybig.png", "res/enemysmall.png", "res/enemyspiltter.png"};
const vector<string> TYPE_ENEMY = {"NORMAL", "BIG", "SMALL", "SPILTTER"};

double randomAngle(int typeDir, const Hero& hero, pair<int, int> currentPosition) {
    int option = randInt(0, int(OPTION_ANGLE.size()) - 1);
    if (OPTION_ANGLE[option] == "CHASE") {
        return calculateAngle(hero.getX(), hero.getY(), currentPosition.first, currentPosition.second);
    }
    if (OPTION_ANGLE[option] == "HORIZONTAL") {
        if (typeDir == TOP) {
            return PI / 2;
        }
        if (typeDir == RIGHT) {
            return -PI;
        }
        if (typeDir == BOT) {
            return -PI / 2;
        }
        if (typeDir == LEFT) {
            return 0;
        }
        assert(false);
    }
    /// ?????
    if (OPTION_ANGLE[option] == "DIAGONAL") {
        int sign = randInt(0, 1) ? 1 : -1;
        double rot = sign * PI / 4;
        if (typeDir == TOP) {
            return PI / 2 + rot;
        }
        if (typeDir == RIGHT) {
            return -PI + rot;
        }
        if (typeDir == BOT) {
            return -PI / 2 + rot;
        }
        if (typeDir == LEFT) {
            return rot;
        }
        assert(false);
    }
    return randDouble(0, 2 * PI);
}

void MultiEnemy::killEnemy(int& index) {
    delete enemies[index];
    enemies[index] = nullptr;
    enemies.erase(enemies.begin() + index);
    --index;
}

// https://stackoverflow.com/questions/42634068/sdl-using-a-stdvector-with-sdl-texture-does-not-work-array-works-fine
void MultiEnemy::generateEnemy(Hero& hero, Score& score, const Camera& camera) {
    if (enemies.empty() || checkTime()) {
        pair<int, int> currentPosition;
        do {
            currentPosition.first = randInt(LEFT_BOUND, MAP_WIDTH);
            currentPosition.second = randInt(LEFT_BOUND, MAP_HEIGHT);
        } while (!pointInBound(currentPosition.first, currentPosition.second));
//        cerr << "spawning at " << currentPosition.first << " " << currentPosition.second << endl;
        int typeDir = 0;
        if (currentPosition.first == LEFT_BOUND) {
            typeDir = TOP;
        } else if (currentPosition.second == LEFT_BOUND) {
            typeDir = LEFT;
        } else if (currentPosition.second == MAP_HEIGHT) {
            typeDir = RIGHT;
        } else if (currentPosition.first == MAP_WIDTH) {
            typeDir = BOT;
        }
        lastTimeSpawned = clock();
        double curAngle = randomAngle(typeDir, hero, currentPosition);
        double curDamage = 0.01;
        int curW = 32;
        int curH = 32;
        double curSpeed = randDouble(1.5, 2);
        double curHP = 1;
        int indexEnemy = randInt(0, int(TYPE_ENEMY.size()) - 1);
        string typeEnemy = TYPE_ENEMY[indexEnemy];
        bool canSpilt = false;
        if (typeEnemy == "BIG") {
            curW = 40;
            curH = 40;
            curHP = 3;
            curDamage = 0.02;
            curSpeed = randDouble(0.5, 1.2);
        }
        if (typeEnemy == "SMALL") {
            curW = 24;
            curH = 24;
            curHP = 0.5;
            curDamage = 0.005;
            curSpeed = randDouble(2, 2.5);
        }
        if (typeEnemy == "SPILTTER") {
            curW = 60;
            curH = 60;
            curHP = 2;
            curDamage = 0.03;
            canSpilt = true;
            curSpeed = randDouble(1, 1.3);
        }
        enemies.push_back(new Enemy(curW, curH, currentPosition.first, currentPosition.second, curSpeed, curAngle, canSpilt, curHP, curDamage, DIRS[indexEnemy]));
    }
    for (int i = 0; i < int(enemies.size()); i++) {
        enemies[i]->update(hero.getX(), hero.getY());
        if (enemies[i]->enemyOutOfBound(LEFT_BOUND)) {
            killEnemy(i);
            continue;
        }
        if (!enemies[i]->enemyOutOfBound(0)) {
            if (hero.intersect(enemies[i]->getW(), enemies[i]->getH(), enemies[i]->getX(), enemies[i]->getY(), score, enemies[i]->dmg) == WIN) {
                enemies[i]->takeDmg(hero.dmg);
            }
        }
        if (enemies[i]->getHP() <= EPS) {
            if (enemies[i]->canSpilt) {
                for (int j = 0; j < 4; j++) {
                    int nextX = enemies[i]->getX();
                    int nextY = enemies[i]->getY();
                    if (j == 0) nextX -= 45;
                    if (j == 1) nextX += 45;
                    if (j == 2) nextY -= 45;
                    if (j == 3) nextY += 45;
                    enemies.push_back(new Enemy(32, 32, nextX, nextY, randDouble(1.5, 2), enemies[i]->getAngle(), false, 1, 0.1, DIRS[0]));
                }
            }
            killEnemy(i);
            score.update(1);
            continue;
        }
        enemies[i]->draw(camera);
    }
}
