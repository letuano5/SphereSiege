#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <ctime>
#include <SDL.h>
#include <SDL_Image.h>
#include <SDL_ttf.h>

using namespace std;

const int WIN = 0;
const int LOSE = 1;
const int CONTINUE = 2;
const int WINDOW_WIDTH = 960;
const int WINDOW_HEIGHT = 540;
const int MAP_WIDTH = WINDOW_WIDTH * 2;
const int MAP_HEIGHT = WINDOW_HEIGHT * 2;
const double EPS = 1e-6;
struct screen {
    int x = WINDOW_WIDTH / -2;
    int y = WINDOW_HEIGHT / -2;
};
bool inRectangle(int w, int h, double x, double y, double ptsX, double ptsY);
bool intersectRectangle(int w, int h, double x, double y, int thatW, int thatH, double thatX, double thatY);
bool collision(double lhsX, double lhsY, double rhsX, double rhsY);
double calculateAngle(double mouseX, double mouseY, double textureX, double textureY);
