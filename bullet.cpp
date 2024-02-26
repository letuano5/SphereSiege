#include <cmath>

#include "Includes.h"
#include "Bullet.h"

Bullet::Bullet(int x, int y, double angle)
    : x(x), y(y), angle(angle) {}

bool Bullet::outOfBound() {
    return getX() < 0 || getX() > WINDOW_WIDTH || getY() < 0 || getY() > WINDOW_HEIGHT;
}

void Bullet::update() {
    x += speed * cos(angle * M_PI / 180);
    y += speed * sin(angle * M_PI / 180);
}

Bullet::~Bullet() {
}
