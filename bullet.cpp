#include <cmath>

#include "Includes.h"
#include "Bullet.h"


Bullet::Bullet(int x, int y, double angle)
    : x(x), y(y), angle(angle)
{
//    auto surface = IMG_Load("res/bullet.png");
//    if (!surface) {
//        cerr << "Failed to create surface.\n";
//    }
//    bullet_texture = SDL_CreateTextureFromSurface(Window::renderer, surface);
//    if (!bullet_texture) {
//        cerr << "Failed to create texture.\n";
//    }
//    SDL_FreeSurface(surface);
}

void Bullet::draw() const {
    SDL_Rect bulletRect = {x, y, w, h};
    SDL_SetRenderDrawColor(Window::renderer, Color.r, Color.g, Color.b, Color.a);
    SDL_RenderFillRect(Window::renderer, &bulletRect);
//    SDL_RenderCopyEx(Window::renderer, bullet_texture, nullptr, &bulletRect, angle, nullptr, SDL_FLIP_NONE);
}
void Bullet::update(double dt) {
    double dx = cos(angle) * speed * dt;
    double dy = sin(angle) * speed * dt;
    x += static_cast<double>(dx);
    y += static_cast<double>(dy);
}
bool Bullet::outOfBound() {
    return getX() < 0 || getX() > WINDOW_WIDTH || getY() < 0 || getY() > WINDOW_HEIGHT;
}

Bullet::~Bullet() {
//    SDL_DestroyTexture(bullet_texture);
}
