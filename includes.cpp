#include "Includes.h"

bool inRectangle(int w, int h, double x, double y, double ptsX, double ptsY) {
    return x <= ptsX && ptsX <= x + w && y <= ptsY && ptsY <= y + h;
}

bool intersectRectangle(int w, int h, double x, double y, int thatW, int thatH, double thatX, double thatY) {
    // [x, y]
    // [x + w, y + h]
    // [thatX, thatY]
    // [thatX + w, thatY + h]
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
