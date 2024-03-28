#include "Includes.h"

mt19937_64 rng(time(NULL));

int isStarted = false;
int isPaused = false;
int isLost = false;
int isContinued = false;
int heroAutoShoot = false;
int canContinue = false;
int isMuted = false;
double dt = 0;
Uint32 lastTick = 0;
Uint32 startTick = 0;

bool inRectangle(int w, int h, double x, double y, double ptsX, double ptsY) {
    return x <= ptsX && ptsX <= x + w && y <= ptsY && ptsY <= y + h;
}

bool intersectRectangle(int w, int h, double x, double y, int thatW, int thatH, double thatX, double thatY) {
    pair<double, double> topLeft = {max(x, thatX), max(y, thatY)};
    pair<double, double> botRight = {min(x + w, thatX + thatW), min(y + h, thatY + thatH)};
    //    cerr << "intersect = " << topLeft.first << " " << topLeft.second << ", " << botRight.first << " " << botRight.second << endl;
    return topLeft.first <= botRight.first && topLeft.second <= botRight.second;
}

// radian
double calculateAngle(double mouseX, double mouseY, double textureX, double textureY) {
    return atan2(mouseY - textureY, mouseX - textureX);
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
    return (equalF(x, LEFT_BOUND) || equalF(x, MAP_WIDTH) || equalF(y, LEFT_BOUND) || equalF(y, MAP_HEIGHT));
}

pair<int, int> getMousePosition() {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    return make_pair(mouseX, mouseY);
}

Uint32 getTick() {
    return SDL_GetTicks() - startTick + lastTick;
}
