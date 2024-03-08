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

void Enemy::draw(const Camera& camera) {
    SDL_FRect enemy = {x - camera.getX(), y - camera.getY(), w, h};
    SDL_Rect inner = {x + (w - hp_w) / 2 - camera.getX(), y + h + 8 - camera.getY(), hp_w * (health_point / max_health_point), hp_h};

    if (triangle_texture) {
        SDL_Rect outer = {x + (w - hp_w) / 2 - camera.getX(), y + h + 8 - camera.getY(), hp_w, hp_h};
        SDL_SetRenderDrawColor(Window::renderer, 200, 0, 0, 255);
        if (!rectOutOfCamera(outer.w, outer.h, outer.x, outer.y)) {
            SDL_RenderDrawRect(Window::renderer, &outer);
        }
        if (!rectOutOfCamera(inner.w, inner.h, inner.x, inner.y)) {
            SDL_RenderFillRect(Window::renderer, &inner);
        }
        if (!rectOutOfCamera(enemy.w, enemy.h, enemy.x, enemy.y)) {
            SDL_RenderCopyExF(Window::renderer, triangle_texture, nullptr, &enemy, rotateAngle, nullptr, SDL_FLIP_NONE);
            rotateAngle += rotateSpeed;
        }
    } else {
        cout << "No texture.\n";
    }
}

void Enemy::update(int heroX, int heroY) {
    double angle = calculateAngle(heroX, heroY, x, y);
    x += speed * cos(angle * M_PI / 180);
    y += speed * sin(angle * M_PI / 180);
    rotateAngle += rotateSpeed;
}

void Enemy::takeDmg(double dmg) {
    health_point -= dmg;
}
