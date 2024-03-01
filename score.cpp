#include "Score.h"

#include <string>

#include "Text.h"
#include "Window.h"

using namespace std;

Score::Score(int scoreNum, string label, int x, int y, bool isBestScoreTxt) : scoreNum(scoreNum), label(label), x(x), y(y), isBestScoreTxt(isBestScoreTxt) {}
Score::~Score() {}

void Score::draw() const {
    Text text(Window::renderer, "res/PressStart2P.ttf", 13, label + to_string(scoreNum), {200, 200, 200, 255});
    text.display(x, y, Window::renderer);
}
void Score::update(const int score) {
    if (isBestScoreTxt) {
        scoreNum = score;
    } else {
        scoreNum += score;
    }
}
