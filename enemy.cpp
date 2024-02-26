#include "Includes.h"
#include "Hero.h"
#include "Enemy.h"

Enemy::Enemy(int w, int h, double x, double y, double speed, const string& image_path)
: w(w), h(h), x(x), y(y), speed(speed) {
    auto surface = IMG_Load(image_path.c_str());
    if (!surface) {
        cerr << "Failed to create surface.\n";
    }
    triangle_texture = SDL_CreateTextureFromSurface(Window::renderer, surface);
    if (!triangle_texture) {
        cerr << "Failed to create texture.\n";
    }
    SDL_FreeSurface(surface);
}
Enemy::~Enemy() {
    SDL_DestroyTexture(triangle_texture);
}

void Enemy::draw() {
    SDL_FRect enemy = {x, y, w, h};
    cerr << "draw enemy at " << x  << " " << y << endl;
    if (triangle_texture) {
        SDL_RenderCopyF(Window::renderer, triangle_texture, nullptr, &enemy);
    } else {
        cout << "No texture.\n";
    }
}

void Enemy::update(int heroX, int heroY) {
    double angle = calculateAngle(heroX, heroY, x, y);
//    cerr << x << " " << y << endl;
//    cerr << getX() << " " << getY() << " " << x << " " << y << " " << angle << endl;
    x += speed * cos(angle * M_PI / 180);
    y += speed * sin(angle * M_PI / 180);
}
