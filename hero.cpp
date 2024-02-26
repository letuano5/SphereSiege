#include "Hero.h"
#include "Bullet.h"
#include "Includes.h"

#include <SDL_image.h>
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

pair<int, int> getMousePosition() {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    return make_pair(mouseX, mouseY);
}

Hero::Hero(int w, int h, int x, int y, const string &image_path) : w(w), h(h), x(x), y(y) {
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

Hero::~Hero() {
    SDL_DestroyTexture(triangle_texture);
}

void Hero::draw() const {
    SDL_Rect hero = {x, y, w, h};
//    cerr << "Draw hero at " << x << " " << y << endl;
    if (triangle_texture) {
        pair<int, int> mousePos = getMousePosition();
        int mouseX = mousePos.first;
        int mouseY = mousePos.second;
        double angle = calculateAngle(mouseX, mouseY, x, y);
        SDL_RenderCopyEx(Window::renderer, triangle_texture, nullptr, &hero, angle, nullptr, SDL_FLIP_NONE);

        for (const auto& bullet : bullets) {
            SDL_Rect bulletRect = {bullet.getX(), bullet.getY(), 5, 5};
            SDL_SetRenderDrawColor(Window::renderer, 255, 0, 0, 255);
            SDL_RenderFillRect(Window::renderer, &bulletRect);
        }

    } else {
        cout << "No texture.\n";
    }
}
void Hero::pollEvents(SDL_Event &event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_LEFT:
            case SDLK_a:
                x -= 10;
                break;
            case SDLK_RIGHT:
            case SDLK_d:
                x += 10;
                break;
            case SDLK_UP:
            case SDLK_w:
                y -= 10;
                break;
            case SDLK_DOWN:
            case SDLK_s:
                y += 10;
                break;
        }
    } else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
        shoot();
    }
}

void Hero::shoot() {
    pair<int, int> mousePos = getMousePosition();
    int mouseX = mousePos.first;
    int mouseY = mousePos.second;
    double angle = calculateAngle(mouseX, mouseY, x, y);
    bullets.emplace_back(x + w / 2, y + h / 2, angle);
}

void Hero::update() {
    for (int i = 0; i < int(bullets.size()); i++) {
        bullets[i].update();
        if (bullets[i].outOfBound()) {
            bullets.erase(bullets.begin() + i);
            i--;
        }
    }
}

int Hero::intersect(double enemyX, double enemyY) {
    if (inRectangle(w, h, x, y, enemyX, enemyY)) {
        cerr << "YOU LOSE!" << endl;
//        exit(0);
        return LOSE;
    }
    for (int i = 0; i < int(bullets.size()); i++) {
        if (collision(bullets[i].getX(), bullets[i].getY(), enemyX, enemyY)) {
            cerr << "This enemy has been killed" << endl;
            exit(0);
            return WIN;
        } else {
            cerr << "Try bullets " << i << " but failed" << endl;
            cerr << bullets[i].getX() << " " << bullets[i].getY() << " " << enemyX << " " << enemyY << endl;
        }
    }
    cerr << "..." << endl;
    return CONTINUE;
}
