
#include "Level.h"

#include "Text.h"

void Level::printLevel() {
    cerr << "Current level: " << numPhase << " " << numMonster << " " << limitMonster << " " << killedMonster << endl;
}

Level::Level() {
    numPhase = randInt(1, 3);
    initNumPhase = numPhase;
    numMonster = randInt(1, 5);
    limitMonster = numPhase * numMonster;
    killedMonster = 0;
    levelup_sound = Mix_LoadWAV("res/audio/levelUp.wav");
    if (levelup_sound == NULL) {
        cerr << "Failed to load levelup sound.\n";
    }
}

Level::~Level() {
    Mix_FreeChunk(levelup_sound);
}
void Level::drawLevelInfo() const {
    Text curLv("res/font/PressStart2P.ttf", 7, "Current level: " + to_string(level + 1), {100, 100, 100, 255});
    curLv.display(WINDOW_WIDTH - curLv.getW() - 20, 402);
    Text curPhase("res/font/PressStart2P.ttf", 7, "Phase: " + to_string(initNumPhase - numPhase + 1) + "/" + to_string(initNumPhase), {100, 100, 100, 255});
    curPhase.display(WINDOW_WIDTH - curPhase.getW() - 20, 412);
    Text remainMonster("res/font/PressStart2P.ttf", 7, "Remaining monster(s): " + to_string(remainMonsters), {100, 100, 100, 255});
    remainMonster.display(WINDOW_WIDTH - remainMonster.getW() - 20, 422);
}
void Level::upLevel() {
    if (!isMuted) {
        int play = Mix_PlayChannel(-1, levelup_sound, 0);
        if (play == -1) {
            cerr << "Failed to play levelup sound. Error: " << Mix_GetError() << "\n";
        }
    }
    level++;
    numPhase = numPhase + randInt(1, 5);
    initNumPhase = numPhase;
    numMonster = randInt(1, 15);
    limitMonster = numPhase * numMonster;
    killedMonster = 0;
}

void Level::update(int curScore) {
    if (this->curScore != curScore) {
        this->curScore = curScore;
        ++killedMonster;
        if (killedMonster % numMonster == 0) {
            --numPhase;
            if (numPhase == 0) {
                upLevel();
            }
        }
    }
    if (maxLevel < level) {
        maxLevel = level;
    }
}

double Level::getLevelProgress() {
    return double(killedMonster) / limitMonster;
}

bool Level::readLevel() {
    ifstream inp("res/save/level.txt");
    int level = -1, curScore = -1;
    int numPhase = -1, numMonster = -1, killedMonster = -1, limitMonster = -1;
    int maxLevel = -1;
    inp >> level >> curScore >> numPhase >> numMonster >> killedMonster >> limitMonster >> maxLevel;
    if (level < 0 || level >= 1e9) {
        return false;
    }
    if (curScore < 0 || curScore >= 1e9) {
        return false;
    }
    if (numPhase < 0 || numPhase >= 1e9) {
        return false;
    }
    if (numMonster < 0 || numMonster >= 1e9) {
        return false;
    }
    if (killedMonster < 0 || killedMonster >= 1e9) {
        return false;
    }
    if (limitMonster < 0 || limitMonster >= 1e9) {
        return false;
    }
    if (maxLevel < 0 || limitMonster >= 1e9) {
        return false;
    }
    this->level = level;
    this->curScore = curScore;
    this->numPhase = numPhase;
    this->numMonster = numMonster;
    this->killedMonster = killedMonster;
    this->limitMonster = limitMonster;
    this->maxLevel = maxLevel;
    inp.close();
    return true;
}

void Level::writeLevel() {
    ofstream out("res/save/level.txt");
    out << level << " " << curScore << " " << numPhase << " " << numMonster << " " << killedMonster << " " << limitMonster;
    out << endl
        << maxLevel;
    out.close();
}
