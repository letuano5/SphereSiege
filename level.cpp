
#include "Level.h"

Level::Level() {
    levelup_sound = Mix_LoadWAV("res/audio/levelUp.wav");
    if (levelup_sound == NULL) {
        cerr << "Failed to load levelup sound.\n";
    }
}

Level::~Level() {
    Mix_FreeChunk(levelup_sound);
}

void Level::update(int curScore) {
    int curScoreNeeded = 0;

    for (int i = 0; i <= level; i++) {
        curScoreNeeded += levelData[i].second;
    }
    if (this->curScore != curScore) {
        this->curScore = curScore;
        if (curScore >= curScoreNeeded && level + 1 < 5) {
            int play = Mix_PlayChannel(-1, levelup_sound, 0);
            cerr << "Level up! " << play << endl;
            if (play == -1) {
                cerr << "Failed to play levelup sound. Error: " << Mix_GetError() << "\n";
            }
            level++;
        }
    }
}

double Level::getLevelProgress() {
    int last = 0;
    for (int i = 0; i < level; i++) last += levelData[i].second;
//    cerr << "? " << curScore << " " << last << " " << level << endl;
    return (double)(curScore - last) / levelData[level].second;
}

bool Level::readLevel() {
    ifstream inp("res/save/level.txt");
    int level = -1;
    inp >> level >> curScore;
    if (level < 0 || level >= 5) {
        return false;
    }
    this->level = level;
    this->curScore = curScore;
    inp.close();
    return true;
}

void Level::writeLevel() {
    ofstream out("res/save/level.txt");
    out << level << " " << curScore;
    out.close();
}
