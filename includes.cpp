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

double calculateAngle(double mouseX, double mouseY, double textureX, double textureY) {
    return atan2(mouseY - textureY, mouseX - textureX) * 180 / M_PI;
}

int randInt(int low, int high) {
    return uniform_int_distribution<int>(low, high)(rng);
}

double randDouble(double low, double high) {
    return uniform_real_distribution<double>(low, high)(rng);
}

bool rectOutOfBound(int w, int h, double x, double y) {
    return x + w < 0 || y + h < 0 || x > MAP_WIDTH || y > MAP_HEIGHT;
}

bool rectOutOfCamera(int w, int h, double x, double y) {
    return x + w < 0 || y + h < 0 || x > WINDOW_WIDTH || y > WINDOW_HEIGHT;
}

bool equalF(double x, double y) {
    return fabsl(x - y) <= EPS;
}

bool pointInBound(double x, double y) {
    return (equalF(x, 0) || equalF(x, MAP_WIDTH) || equalF(y, 0) || equalF(y, MAP_HEIGHT));
}
