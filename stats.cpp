#include "Stats.h"

Stats::Stats() { reset(); }
Stats::~Stats() {}

void Stats::reset() {
    bestScore = 0;
    bestLevel = 0;
    playedRound = 0;
    killedEnemies = 0;
    firedBullets = 0;
    collectedItems = 0;
    timeElapsed = 0;
}

void Stats::printStats() {
    cerr << string(10, '=') << endl;
    cerr << "Best score: " << bestScore;
    cerr << "Best level: " << bestLevel << endl;
    cerr << "Played times: " << playedRound << endl;
    cerr << "Killed enemies: " << killedEnemies << endl;
    cerr << "Fired bullets: " << firedBullets << endl;
    cerr << "Collected items: " << collectedItems << endl;
    int s = timeElapsed / 1000;
    cerr << "Time elapsed: " << s / 3600 << ":" << (s % 3600) / 60 << ":" << ((s % 3600) % 60) << endl;
    cerr << string(10, '=') << endl;
}

void Stats::writeStats() {
    ofstream out("res/save/stats.txt");
    out << bestScore << " ";
    out << bestLevel << " ";
    out << playedRound << " ";
    out << killedEnemies << " ";
    out << firedBullets << " ";
    out << collectedItems << " ";
    out << timeElapsed << " ";
    out.close();
}

bool Stats::readStats() {
    ifstream inp("res/save/stats.txt");
    int bestScore = -1;
    int bestLevel = -1;
    int playedRound = -1;
    int killedEnemies = -1;
    int firedBullets = -1;
    int collectedItems = -1;
    int timeElapsed = -1;
    inp >> bestScore >> bestLevel >> playedRound >> killedEnemies >> firedBullets >> collectedItems >> timeElapsed;
    inp.close();
    if (bestScore < 0 || bestScore >= 1e9) {
        return false;
    }
    if (bestLevel < 0 || bestLevel >= 1e9) {
        return false;
    }
    if (playedRound < 0 || playedRound >= 1e9) {
        return false;
    }
    if (killedEnemies < 0 || killedEnemies >= 1e9) {
        return false;
    }
    if (firedBullets < 0 || firedBullets >= 1e9) {
        return false;
    }
    if (collectedItems < 0 || collectedItems >= 1e9) {
        return false;
    }
    if (timeElapsed < 0 || timeElapsed >= 1e9) {
        return false;
    }
    this->bestScore = bestScore;
    this->bestLevel = bestLevel;
    this->playedRound = playedRound;
    this->killedEnemies = killedEnemies;
    this->firedBullets = firedBullets;
    this->collectedItems = collectedItems;
    this->timeElapsed = timeElapsed;
    return true;
}
