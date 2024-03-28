#include "MultiEnemy.h"

MultiEnemy::MultiEnemy() {
    explosion_sound = Mix_LoadWAV("res/audio/explosion.wav");
    if (!explosion_sound) {
        cerr << "Failed to load explosion sound.\n";
    }
}

MultiEnemy::~MultiEnemy() {
    for (int i = 0; i < int(enemies.size()); i++) {
        delete enemies[i];
        enemies[i] = NULL;
    }
    enemies.clear();
    for (int i = 0; i < explosions.size(); i++) {
        delete explosions[i];
        explosions[i] = nullptr;
    }
    explosions.clear();
    Mix_FreeChunk(explosion_sound);
}

void MultiEnemy::clearE() {
    for (int i = 0; i < int(enemies.size()); i++) {
        delete enemies[i];
        enemies[i] = NULL;
    }
    enemies.clear();
}

double MultiEnemy::passedSecond() {
    clock_t currentTime = clock();
    return (currentTime - lastTimeSpawned) / double(CLOCKS_PER_SEC);
}

bool MultiEnemy::checkTime() {
    return passedSecond() > MAX_DIFF_TIME;
}

bool canSpawn(string typeEnemy, int curLevel) {
//    cerr << "Checking if we can spawn... " << curLevel << endl;
    if (typeEnemy == "BIG") {
        // return curSec > MIN_BIG;
        return curLevel >= 2;
    }
    if (typeEnemy == "SMALL") {
        // return curSec > MIN_SMALL;
        return curLevel >= 1;
    }
    if (typeEnemy == "SPILLTER") {
        // return curSec > MIN_SPILLTER;
        return curLevel >= 3;
    }
    return typeEnemy == "NORMAL";
}

const int TOP = 0;
const int BOT = 1;
const int LEFT = 2;
const int RIGHT = 3;

const vector<string> OPTION_ANGLE = {"CHASE", "HORIZONTAL", "DIAGONAL", "RANDOM"};
const vector<string> DIRS = {"res/image/enemy.png", "res/image/enemybig.png", "res/image/enemysmall.png", "res/image/enemyspiltter.png"};
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

void MultiEnemy::generateEnemy(Hero& hero, Score& score, Camera& camera, int curLevel) {
    if (enemies.empty() || checkTime()) {
        pair<int, int> currentPosition;
        do {
            currentPosition.first = randInt(LEFT_BOUND, MAP_WIDTH);
            currentPosition.second = randInt(LEFT_BOUND, MAP_HEIGHT);
        } while (!pointInBound(currentPosition.first, currentPosition.second));
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
        double curAngle = randomAngle(typeDir, hero, currentPosition);
        double curDamage = 0.01;
        int curW = 32;
        int curH = 32;
        double curSpeed = randDouble(1.5, 2);
        double curHP = 1;
        int curScore = 5;
        int indexEnemy;
        string typeEnemy;
        do {
            indexEnemy = randInt(0, int(TYPE_ENEMY.size()) - 1);
            typeEnemy = TYPE_ENEMY[indexEnemy];
        } while (!canSpawn(typeEnemy, curLevel));
        bool canSpilt = false;
        if (typeEnemy == "BIG") {
            curW = 40;
            curH = 40;
            curHP = 3;
            curDamage = 0.02;
            curSpeed = randDouble(0.5, 1.2);
            curScore = 30;
        }
        if (typeEnemy == "SMALL") {
            curW = 24;
            curH = 24;
            curHP = 0.5;
            curDamage = 0.01;
            curSpeed = randDouble(2, 2.5);
            curScore = 5;
        }
        if (typeEnemy == "SPILTTER") {
            curW = 60;
            curH = 60;
            curHP = 2;
            curDamage = 0.03;
            canSpilt = true;
            curSpeed = randDouble(1, 1.3);
            curScore = 5;
        }
        lastTimeSpawned = clock();
        enemies.push_back(new Enemy(curW, curH, currentPosition.first, currentPosition.second, curSpeed, curAngle, canSpilt, curHP, curDamage, curScore, DIRS[indexEnemy]));
    }
    for (int i = 0; i < int(enemies.size()); i++) {
        enemies[i]->update(hero.getX(), hero.getY(), isSlow ? 1.0 / SLOW_RATE : 1);
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
            score.update(enemies[i]->getScore());
            if (enemies[i]->canSpilt) {
                for (int j = 0; j < 4; j++) {
                    int nextX = enemies[i]->getX();
                    int nextY = enemies[i]->getY();
                    if (j == 0) nextX -= 45;
                    if (j == 1) nextX += 45;
                    if (j == 2) nextY -= 45;
                    if (j == 3) nextY += 45;
                    enemies.push_back(new Enemy(32, 32, nextX, nextY, randDouble(1.5, 2), enemies[i]->getAngle(), false, 1, 0.1, 5, DIRS[0]));
                }
            }
            double centerEnemyX = enemies[i]->getX() + enemies[i]->getW() / 2;
            double centerEnemyY = enemies[i]->getY() + enemies[i]->getH() / 2;
            explosions.push_back(new Explosion(centerEnemyX, centerEnemyY));
            if (!isMuted && Mix_PlayChannel(-1, explosion_sound, 0) == -1) {
                cerr << "Failed to play explosion sound: " << Mix_GetError() << "\n";
            }
            killEnemy(i);
            camera.shake(0.2, 12);
            continue;
        }
        enemies[i]->draw(camera);
    }
    for (int i = 0; i < explosions.size(); i++) {
        explosions[i]->update();
        if (explosions[i]->isDone()) {
            delete explosions[i];
            explosions[i] = nullptr;
            explosions.erase(explosions.begin() + i);
            i--;
        }
    }
    for (const auto& explosion : explosions) {
        explosion->draw(camera);
    }
}

void MultiEnemy::setSlow(bool isSlow) {
    this->isSlow = isSlow;
}

void MultiEnemy::saveEnemies() {
    ofstream out("res/save/enemies.txt");
    out << enemies.size() << "\n";
    for (const auto& enemy : enemies) {
        out << enemy->getW() << " " << enemy->getH() << "\n";
        out << setprecision(9) << fixed << enemy->getX() << " " << enemy->getY() << "\n";
        out << setprecision(9) << fixed << enemy->getSpeed() << "\n";
        out << setprecision(9) << fixed << enemy->getAngle() << "\n";
        out << enemy->canSpilt << "\n";
        out << setprecision(9) << fixed << enemy->getHP() << "\n";
        out << setprecision(9) << fixed << enemy->getDamage() << "\n";
        out << enemy->getPath() << "\n";
        out << enemy->getScore() << "\n";
    }
    out.close();
}

bool MultiEnemy::setEnemies() {
    ifstream inp("res/save/enemies.txt");
    if (!inp.is_open()) {
        return false;
    }
    int numEnemies = -1;
    inp >> numEnemies;
    if (numEnemies < 0 || numEnemies > 1e6) {
        inp.close();
        return false;
    }
    vector<Enemy*> enemies;
    for (int i = 0; i < numEnemies; i++) {
        int w = -1, h = -1;
        inp >> w >> h;
        if (w < 0 || w > MAP_WIDTH || h < 0 || h > MAP_HEIGHT) {
            cerr << "fail at reading height or width" << endl;
            inp.close();
            return false;
        }
        double x = -1e9, y = -1e9;
        inp >> x >> y;
        double speed = -1;
        inp >> speed;
        if (speed < 0 || speed >= 1e9) {
            cerr << "fail at reading speed" << endl;
            inp.close();
            return false;
        }
        double angle = -1e9;
        inp >> angle;
        if (equalF(angle, -1e9)) {
            cerr << "fail at reading angle" << endl;
            inp.close();
            return false;
        }
        int canSpilt = -1;
        inp >> canSpilt;
        if (canSpilt < 0 || canSpilt > 1) {
            cerr << "fail at reading spilting ability" << endl;
            inp.close();
            return false;
        }
        double hp = -1;
        inp >> hp;
        if (hp < 0 || hp > 3) {
            cerr << "fail at reading healthpoint" << endl;
            cerr << hp << endl;
            inp.close();
            return false;
        }
        double dmg = -1;
        inp >> dmg;
        if (dmg < 0) {
            inp.close();
            return false;
        }
        string pathImg;
        inp >> pathImg;
        bool truePath = false;
        for (const auto& path : DIRS) {
            if (path == pathImg) {
                truePath = true;
                break;
            }
        }
        if (!truePath) {
            cerr << "fail at reading image's path" << endl;
            inp.close();
            return false;
        }
        int score;
        inp >> score;
        if (score < 0) {
            cerr << "fail at reading score" << endl;
            inp.close();
            return false;
        }
        enemies.push_back(new Enemy(w, h, x, y, speed, angle, canSpilt, hp, dmg, score, pathImg));
        if (enemies[i]->enemyOutOfBound(LEFT_BOUND)) {
            cerr << "fail" << endl;
            return false;
            inp.close();
        }
    }
    inp.close();
    if (int(enemies.size()) != numEnemies) {
        return false;
    }
    clearE();
    this->enemies.swap(enemies);
    return true;
}
