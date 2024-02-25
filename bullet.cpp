#include "Bullet.h"

#include <cmath>

Bullet::Bullet(int x, int y, double angle)
    : x(x), y(y), angle(angle) {}

void Bullet::draw() const {
    SDL_Rect bulletRect = {x, y, w, h};
    SDL_SetRenderDrawColor(Window::renderer, Color.r, Color.g, Color.b, Color.a);
    SDL_RenderFillRect(Window::renderer, &bulletRect);
}
void Bullet::update(double dt) {
    double dx = cos(angle) * speed * dt;
    double dy = sin(angle) * speed * dt;
    x += static_cast<double>(dx);
    y += static_cast<double>(dy);
}

Bullet::~Bullet() {
}
//void Bullet::checkCollision(std::vector<Enemy>& enemies) {
//}

//SDL_Rect Bullet::getRect() const {
//    return {x, y, 5, 5};
//}

//bool Bullet::isColliding(const SDL_Rect& a, const SDL_Rect& b) const {
//    return a.x < b.x + b.w &&
//           a.x + a.w > b.x &&
//           a.y < b.y + b.h &&
//           a.y + a.h > b.y;
//}
