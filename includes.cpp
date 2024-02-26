#include "Includes.h"

bool inRectangle(int w, int h, double x, double y, double ptsX, double ptsY) {
    return x <= ptsX && ptsX <= x + w && y <= ptsY && ptsY <= y + h;
}

bool collision(double lhsX, double lhsY, double rhsX, double rhsY) {
    return fabsl(lhsX - rhsX) <= EPS && fabsl(lhsY - rhsY) <= EPS;
}

double calculateAngle(double mouseX, double mouseY, double textureX, double textureY) {
    return atan2(mouseY - textureY, mouseX - textureX) * 180 / M_PI;
}
