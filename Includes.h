#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <SDL.h>
#include <SDL_Image.h>

using namespace std;

const int WIN = 0;
const int LOSE = 1;
const int CONTINUE = 2;
const int WINDOW_WIDTH = 960;
const int WINDOW_HEIGHT = 540;
const double EPS = 1e-6;

bool inRectangle(int w, int h, double x, double y, double ptsX, double ptsY);
bool collision(double lhsX, double lhsY, double rhsX, double rhsY);
double calculateAngle(double mouseX, double mouseY, double textureX, double textureY);
