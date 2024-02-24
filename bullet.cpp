#include <cmath>

#include "Bullet.h"

Bullet::Bullet(int x, int y, double angle)
    : x(x), y(y), angle(angle) {}

void Bullet::update() {
    x += speed * cos(angle * M_PI / 180);
    y += speed * sin(angle * M_PI / 180);
}

Bullet::~Bullet() {
}
