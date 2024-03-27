#include "Bullet.h"

#include "Includes.h"

Bullet::Bullet(int x, int y, double angle)
    : x(x), y(y), angle(angle) {
}

void Bullet::draw(const Camera& camera) const {
    int length = 12;
    int thickness = 2;
    if (outOfCamera(camera)) {
        return;
    }
    SDL_SetRenderDrawColor(Window::renderer, color.r, color.g, color.b, color.a);
    for (int j = 0; j < thickness; ++j) {
        int x1 = x - j * sin(angle);
        int y1 = y + j * cos(angle);
        int x2 = x + length * cos(angle) - j * sin(angle);
        int y2 = y + length * sin(angle) + j * cos(angle);
        SDL_RenderDrawLine(Window::renderer, x1 - camera.getX(), y1 - camera.getY(), x2 - camera.getX(), y2 - camera.getY());
    }
}
void Bullet::update(double dt) {
    double dx = cos(angle) * speed * dt;
    double dy = sin(angle) * speed * dt;
    x += static_cast<double>(dx);
    y += static_cast<double>(dy);
}
bool Bullet::outOfBound() {
    return rectOutOfBound(getW(), getH(), getX(), getY());
}
bool Bullet::bulletOutOfMap() const {
    return x < 0 || y < 0 || x + w > MAP_WIDTH || y + h > MAP_HEIGHT;
}
bool Bullet::outOfCamera(const Camera& camera) const {
    return rectOutOfCamera(getW(), getH(), getX(camera), getY(camera));
}

Bullet::~Bullet() {}
