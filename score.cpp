#include "Score.h"

#include <string>

#include "Text.h"
#include "Window.h"

using namespace std;

Score::Score(int scoreNum, string label, int x, int y, bool isBestScoreTxt, string dir)
    : scoreNum(scoreNum), label(label), x(x), y(y), isBestScoreTxt(isBestScoreTxt), dir(dir) {}

Score::~Score() {}

void Score::draw() const {
    Text text("res/font/PressStart2P.ttf", 13, label + to_string(scoreNum), {200, 200, 200, 255});
    text.display(x, y);
}

void Score::update(const int score) {
    if (isBestScoreTxt) {
        scoreNum = score;
    } else {
        scoreNum += score;
    }
}

void Score::writeScore() {
    ofstream out(dir.c_str());
    out << scoreNum;
    out.close();
}

bool Score::readScore() {
    ifstream inp(dir.c_str());
    int score = -1;
    inp >> score;
    if (score < 0 || score > 1e6) {
        return false;
    }
    scoreNum = score;
    return true;
}
