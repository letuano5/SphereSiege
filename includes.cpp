#include "Includes.h"

mt19937_64 rng(time(NULL));

int isStarted = false;
int isPaused = false;
int isLost = false;
int isContinued = false;
int isStatsShow = false;
int heroAutoShoot = false;
int canContinue = false;
int isMuted = false;
int isDataCleared = false;
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
    //    cerr << x << " " << LEFT_BOUND << " " << MAP_WIDTH + LEFT_BOUND << endl;
    //    cerr << y << " " << LEFT_BOUND << " " << MAP_WIDTH + LEFT_BOUND;
    return (equalF(x, LEFT_BOUND) || equalF(x, MAP_WIDTH - LEFT_BOUND) || equalF(y, LEFT_BOUND) || equalF(y, MAP_HEIGHT - LEFT_BOUND));
}

bool enemyCanReachMap(double posX, double posY, double angle) {
    if (posX < 0 && cos(angle) <= EPS) {
        return false;
    }
    if (posX > MAP_WIDTH && cos(angle) >= -EPS) {
        return false;
    }
    if (posY < 0 && sin(angle) <= EPS) {
        return false;
    }
    if (posY > MAP_HEIGHT && sin(angle) >= -EPS) {
        return false;
    }
    if (equalF(cos(angle), 0) || equalF(sin(angle), 0)) {
        return true;
    }
    double leftKx = -posX / cos(angle), rightKx = (MAP_WIDTH - posX) / cos(angle);
    double leftKy = -posY / sin(angle), rightKy = (MAP_HEIGHT - posY) / sin(angle);
    if (leftKx > rightKx) swap(leftKx, rightKx);
    if (leftKy > rightKy) swap(leftKy, rightKy);
    double leftK = max(leftKx, leftKy);
    double rightK = min(rightKx, rightKy);
    //    cerr << posX + leftK * cos(angle) << " " << posY + leftK * sin(angle) << endl;
//    cerr << leftK << " " << rightK << endl;
    return leftK <= rightK && rightK >= 0;
}

pair<int, int> getMousePosition() {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    return make_pair(mouseX, mouseY);
}

Uint32 getTick() {
    return SDL_GetTicks() - startTick + lastTick;
}

// bool parseInt(ifstream& inp, int& x) {
//     x = -1;
//     inp >> x;
//     return x >= 0 && x < 1e9;
// }
