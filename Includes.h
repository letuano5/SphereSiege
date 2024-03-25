#pragma once

#include <SDL.h>
#include <SDL_Image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include <cassert>
#include <chrono>
#include <cmath>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <vector>

using namespace std;
using namespace chrono;

const int WIN = 0;
const int LOSE = 1;
const int CONTINUE = 2;
const int WINDOW_WIDTH = 960;
const int WINDOW_HEIGHT = 540;
const int LEFT_BOUND = -50;
const int MAP_WIDTH = 1280;
const int MAP_HEIGHT = 720;
const double EPS = 1e-6;
const double PI = acos(-1);

bool inRectangle(int w, int h, double x, double y, double ptsX, double ptsY);
bool intersectRectangle(int w, int h, double x, double y, int thatW, int thatH, double thatX, double thatY);
double calculateAngle(double mouseX, double mouseY, double textureX, double textureY);
int randInt(int low, int high);
double randDouble(double low, double high);
bool rectOutOfBound(int w, int h, double x, double y);
bool rectOutOfCamera(int w, int h, double x, double y);
bool pointInBound(double x, double y);
bool equalF(double x, double y);
pair<int, int> getMousePosition();
extern bool isStarted;
extern bool isPaused;
extern bool isLost;
extern bool isContinued;
extern bool heroAutoShoot;
extern double dt;
extern Uint32 curTick;
Uint32 getTick();
