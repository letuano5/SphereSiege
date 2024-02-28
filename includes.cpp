#include "Includes.h"

mt19937_64 rng(time(NULL));

bool inRectangle(int w, int h, double x, double y, double ptsX, double ptsY) {
    return x <= ptsX && ptsX <= x + w && y <= ptsY && ptsY <= y + h;
}

bool intersectRectangle(int w, int h, double x, double y, int thatW, int thatH, double thatX, double thatY) {
    pair<double, double> topLeft = {max(x, thatX), max(y, thatY)};
    pair<double, double> botRight = {min(x + w, thatX + w), min(y + h, thatY + h)};
    return topLeft.first <= botRight.first && topLeft.second <= botRight.second;
}

bool collision(double lhsX, double lhsY, double rhsX, double rhsY) {
    return fabsl(lhsX - rhsX) <= EPS && fabsl(lhsY - rhsY) <= EPS;
}

double calculateAngle(double mouseX, double mouseY, double textureX, double textureY) {
    return atan2(mouseY - textureY, mouseX - textureX) * 180 / M_PI;
}

int randInt(int low, int high) {
    return uniform_int_distribution<int>(low, high)(rng);
}

bool rectOutOfBound(int w, int h, double x, double y) {
    return x + w < 0 || y + h < 0 || x > WINDOW_WIDTH || y > WINDOW_HEIGHT;
}
