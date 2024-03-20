#pragma once

#include "Includes.h"

class Score {
   public:
    Score(int scoreNum, string label, int x, int y, bool isBestScoreTxt);
    ~Score();
    Score(){}

    void draw() const;
    void update(const int score);
    int getScore() { return scoreNum; }

   private:
    int scoreNum;
    bool isBestScoreTxt;
    int x, y;
    string label;
};
