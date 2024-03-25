#pragma once

#include "Includes.h"

class Camera {
   public:
    Camera();
    Camera(int leftX, int leftY);
    int getX() const { return leftX; }
    int getY() const { return leftY; }
    void adjust(int heroX, int heroY, int heroW, int heroH);
    void saveCamera();
    bool setCamera();

    double shakeDuration = 0;
    double shakeIntensity = 0;

    void shake(double duration, double intensity) {
        shakeDuration = initialShakeDuration = duration;
        shakeIntensity = intensity;
    }
    double initialShakeDuration = 0;
    void update(double dt) {
        if (shakeDuration > 0) {
            double shakeProgress = shakeDuration / initialShakeDuration;
            leftX += (rand() % 2000 - 1000) / 1000.0 * shakeIntensity * shakeProgress;
            leftY += (rand() % 2000 - 1000) / 1000.0 * shakeIntensity * shakeProgress;
            shakeDuration -= dt;
            if (shakeDuration < 0) {
                shakeDuration = 0;
            }
        }
    }

   private:
    int leftX = 0, leftY = 0;
};
