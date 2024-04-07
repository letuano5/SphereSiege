
#include "Level.h"

void Level::printLevel() {
    cerr << "Current level: " << numPhase << " " << numMonster << " " << limitMonster << " " << killedMonster << endl;
}

Level::Level() {
    numPhase = randInt(1, 5);
    numMonster = randInt(1, 15);
    limitMonster = numPhase * numMonster;
    killedMonster = 0;
    //    printLevel();
    levelup_sound = Mix_LoadWAV("res/audio/levelUp.wav");
    if (levelup_sound == NULL) {
        cerr << "Failed to load levelup sound.\n";
    }
}

Level::~Level() {
    Mix_FreeChunk(levelup_sound);
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
    numMonster = randInt(1, 15);
    limitMonster = numPhase * numMonster;
    killedMonster = 0;
    //    printLevel();
    //    cerr << "Upgraded to level " << level << " with " << numPhase << " phases and " << numMonster << " monsters" << endl;
}

void Level::update(int curScore) {
    if (this->curScore != curScore) {
        this->curScore = curScore;
        //        cerr << "Killed a new enemy!" << endl;
        ++killedMonster;
        if (killedMonster % numMonster == 0) {
            --numPhase;
            if (numPhase == 0) {
                upLevel();
            }
        }
        //        printLevel();
    }
}

double Level::getLevelProgress() {
    //    int last = 0;
    //    for (int i = 0; i < level; i++) last += levelData[i].second;
    //    cerr << "? " << curScore << " " << last << " " << level << endl;
    //    return (double)(curScore - last) / levelData[level].second;
    //    cerr << "Ratio: " << killedMonster << "/ " << limitMonster << endl;
    return double(killedMonster) / limitMonster;
}

bool Level::readLevel() {
    ifstream inp("res/save/level.txt");
    int level = -1, curScore = -1;
    int numPhase = -1, numMonster = -1, killedMonster = -1, limitMonster = -1;
    inp >> level >> curScore >> numPhase >> numMonster >> killedMonster >> limitMonster;
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
    this->level = level;
    this->curScore = curScore;
    this->numPhase = numPhase;
    this->numMonster = numMonster;
    this->killedMonster = killedMonster;
    this->limitMonster = limitMonster;
    inp.close();
    return true;
}

void Level::writeLevel() {
    ofstream out("res/save/level.txt");
    out << level << " " << curScore << " " << numPhase << " " << numMonster << " " << killedMonster << " " << limitMonster;
    out.close();
}
