#include "Enemy.h"

#include "Includes.h"

Enemy::Enemy(int w, int h, double x, double y, double speed, double angle, bool canSpilt, double hp, double dmg, int score, const string& image_path)
    : w(w), h(h), x(x), y(y), speed(speed), angle(angle), health_point(hp), max_health_point(hp), dmg(dmg), score(score), canSpilt(canSpilt), imagePath(image_path) {
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
    //    cerr << "render enemy at " << x << " " << y << " " << angle << endl;
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

bool Enemy::enemyOutOfMap() const {
    return x < 0 || y < 0 || x + w > MAP_WIDTH || y + h > MAP_HEIGHT;
}

bool Enemy::enemyOutOfBound(int leftBound) const {
    return x + w < leftBound || y + h < leftBound || x > MAP_WIDTH || y > MAP_HEIGHT;
}

void Enemy::update(int heroX, int heroY, double slowRate) {
    if (canShiftAngle == 0) {
        angle = calculateAngle(heroX, heroY, x, y);
    }
    //    x += speed * cos(angle) * slowRate;
    //    y += speed * sin(angle) * slowRate;
    x += speed * cos(angle) * dt * 50 * slowRate;
    y += speed * sin(angle) * dt * 50 * slowRate;
    rotateAngle += rotateSpeed;
}

void Enemy::takeDmg(double dmg) {
    health_point -= dmg;
}
