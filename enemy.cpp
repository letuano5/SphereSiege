#include "Enemy.h"

#include "Includes.h"

Enemy::Enemy(int w, int h, double x, double y, double speed, double angle, bool canSpilt, double hp, double dmg, int score, const string& image_path)
    : w(w), h(h), x(x), y(y), speed(speed), angle(angle), health_point(hp), max_health_point(hp), dmg(dmg), score(score), canSpilt(canSpilt), imagePath(image_path) {
    if (image_path.find("big") != string::npos) {
        accentColor = {224, 119, 63, 255};
    } else if (image_path.find("small") != string::npos) {
        accentColor = {231, 202, 34, 255};
    } else if (image_path.find("splitter") != string::npos) {
        accentColor = {76, 213, 51, 255};
    }
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
    //    cerr << "enemy at " << x << " " << y << " draw at " << x-camera.getX() << " " << y-camera.getY() << " " << angle << endl;
    //    cerr << "possibility: " << x + 1e9 * cos(angle) << " " << x - 1e9 * cos(angle) << " " << y + 1e9 * sin(angle) << " " << y-1e9 * sin(angle)<<endl;
    //    cerr << "render enemy at " << x << " " << y << " " << angle << endl;
    //    if (!enemyCanReachMap(x, y, angle)) {
    //        cerr << "fail " << x << " " << y << " " << angle << endl;
    //        assert(enemyCanReachMap(x, y, angle));
    //    }
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
    if (angle < 0) {
        angle += 2 * PI;
    }
    if (angle >= 2 * PI) {
        angle -= 2 * PI;
    }
    if (canShiftAngle == 0) {
        angle = calculateAngle(heroX, heroY, x, y);
    }
    x += speed * cos(angle) * dt * 50 * slowRate;
    y += speed * sin(angle) * dt * 50 * slowRate;
    if (x > 0 && y > 0 && x + w < MAP_WIDTH && y + h < MAP_HEIGHT) {
        isOut = 0;
    } else {
        if (isOut) {
            // ...
        } else {
            if ((x <= 0 || x + w >= MAP_WIDTH) && enemyCanReachMap(x, y, speed, PI - angle)) {
                // cerr << "shifted 1" << x << " " << y << " " << angle << endl;
                angle = PI - angle;
            } else if ((y <= 0 || y + h >= MAP_HEIGHT) && enemyCanReachMap(x, y, speed, -angle)) {
                // cerr << "shifted 2" << x << " " << y << " " << angle << endl;
                angle = -angle;
            } else {
                bool shifted = false;
                for (auto nextAngle : {PI - angle, -angle, PI + angle}) {
                    if (enemyCanReachMap(x, y, speed, nextAngle)) {
                        shifted = true;
                        angle = nextAngle;
                        break;
                    }
                }
                if (!shifted) {
                    while (!enemyCanReachMap(x, y, speed, angle)) {
                        angle = randDouble(0, 2 * PI);
                    }
                }
            }
            if (angle < 0) {
                angle += 2 * PI;
            }
            if (angle >= 2 * PI) {
                angle -= 2 * PI;
            }
        }
    }

    while (!enemyCanReachMap(x, y, speed, angle)) {
        angle = randDouble(0, 2 * PI);
    }

    rotateAngle += rotateSpeed;
}

void Enemy::takeDmg(double dmg) {
    health_point -= dmg;
}
