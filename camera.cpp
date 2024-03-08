#include "Camera.h"

Camera::Camera(){}

Camera::Camera(int leftX, int leftY) : leftX(leftX), leftY(leftY)
{}

void Camera::adjust(int heroX, int heroY, int heroW, int heroH) {
    if (heroX < leftX) {
        leftX = heroX;
    }
    if (heroY < leftY) {
        leftY = heroY;
    }
    if (heroX + heroW > leftX + WINDOW_WIDTH) {
        leftX = heroX + heroW - WINDOW_WIDTH;
    }
    if (heroY + heroH > leftY + WINDOW_HEIGHT) {
        leftY = heroY + heroH - WINDOW_HEIGHT;
    }
    if (leftX < 0) {
        leftX = 0;
    }
    if (leftY < 0) {
        leftY = 0;
    }
    if (leftX + WINDOW_WIDTH > MAP_WIDTH) {
        leftX = MAP_WIDTH - WINDOW_WIDTH;
    }
    if (leftY + WINDOW_HEIGHT > MAP_HEIGHT) {
        leftY = MAP_HEIGHT - WINDOW_HEIGHT;
    }
}
