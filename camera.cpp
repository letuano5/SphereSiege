#include "Camera.h"

Camera::Camera() {}

Camera::Camera(int leftX, int leftY) : leftX(leftX), leftY(leftY) {}

void Camera::adjust(int heroX, int heroY, int heroW, int heroH) {
    float speed = 0.05f;

    // Calculate the target position of the camera
    int targetX = heroX + heroW / 2 - WINDOW_WIDTH / 2;
    int targetY = heroY + heroH / 2 - WINDOW_HEIGHT / 2;

    // Use linear interpolation to gradually move the camera towards the target position
    leftX = (1 - speed) * leftX + speed * targetX;
    leftY = (1 - speed) * leftY + speed * targetY;

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

void Camera::saveCamera() {
    ofstream out("res/save/camera.txt");
    out << getX() << " " << getY() << "\n";
    out.close();
}

bool Camera::setCamera() {
    ifstream inp("res/save/camera.txt");
    int x = -1, y = -1;
    inp >> x >> y;
    if (x < 0 || x + WINDOW_WIDTH > MAP_WIDTH || y < 0 || y + WINDOW_HEIGHT > MAP_HEIGHT) {
        return false;
    }
    leftX = x;
    leftY = y;
    inp.close();
    return true;
}
