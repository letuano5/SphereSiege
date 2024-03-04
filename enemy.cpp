#include "Enemy.h"
#include "Includes.h"


Enemy::Enemy(int w, int h, double x, double y, double speed, double rotateSpeed, const string& image_path)
: w(w), h(h), x(x), y(y), speed(speed), rotateSpeed(rotateSpeed) {
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
    SDL_Rect inner = {x + (w - hp_w) / 2, y + h + 8, hp_w * (health_point / max_health_point), hp_h};

//    cerr << "draw enemy at " << x << " " << y << " " << w << " " << h << endl;
    if (triangle_texture) {
        SDL_Rect outer = {x + (w - hp_w) / 2, y + h + 8, hp_w, hp_h};
        SDL_SetRenderDrawColor(Window::renderer, 200, 0, 0, 255);
        SDL_RenderDrawRect(Window::renderer, &outer);
        SDL_RenderFillRect(Window::renderer, &inner);
        SDL_RenderCopyExF(Window::renderer, triangle_texture, nullptr, &enemy, rotateAngle, nullptr, SDL_FLIP_NONE);
        rotateAngle += rotateSpeed;
    } else {
        cout << "No texture.\n";
    }
}

void Enemy::update(int heroX, int heroY) {
    double angle = calculateAngle(heroX, heroY, x, y);
    x += speed * cos(angle * M_PI / 180);
    y += speed * sin(angle * M_PI / 180);
}

void Enemy::takeDmg(double dmg) {
    if (health_point > dmg) {
        health_point -= dmg;
    } else {
        health_point = 0;
    }
}
