#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <random>
#include <cmath>
#include <ctime>
#include <SDL.h>
#include <SDL_Image.h>

using namespace std;
using namespace chrono;

const int WIN = 0;
const int LOSE = 1;
const int CONTINUE = 2;
const int WINDOW_WIDTH = 960;
const int WINDOW_HEIGHT = 540;
const double EPS = 1e-6;

bool inRectangle(int w, int h, double x, double y, double ptsX, double ptsY);
bool intersectRectangle(int w, int h, double x, double y, int thatW, int thatH, double thatX, double thatY);
double calculateAngle(double mouseX, double mouseY, double textureX, double textureY);
int randInt(int low, int high);
double randDouble(double low, double high);
bool rectOutOfBound(int w, int h, double x, double y);
bool pointInBound(double x, double y);
bool equalF(double x, double y);
