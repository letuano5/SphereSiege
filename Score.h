#pragma once

#include "Includes.h"

class Score {
   public:
    Score(int scoreNum, string label, int x, int y, bool isBestScoreTxt, string dir);
    ~Score();
    Score(){}

    void draw() const;
    void update(const int score);
    int getScore() { return scoreNum; }
    bool readScore();
    void writeScore();

   private:
    int scoreNum;
    bool isBestScoreTxt;
    int x, y;
    string label;
    string dir;
};
