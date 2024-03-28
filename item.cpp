#include "Item.h"

Item::Item(double x, double y, double dir, double speed, string type, string path) : x(x), y(y), direction(dir), speed(speed), type(type), path(path) {
    SDL_Surface *surface = IMG_Load(path.c_str());
    if (surface == nullptr) {
        cerr << "Error loading item texture: " << IMG_GetError() << " " << type << endl;
        exit(1);
    }
    item_texture = SDL_CreateTextureFromSurface(Window::renderer, surface);
    if (item_texture == nullptr) {
        cerr << "Error creating item texture: " << SDL_GetError() << endl;
        exit(1);
    }
    SDL_FreeSurface(surface);
}

Item::~Item() {
    SDL_DestroyTexture(item_texture);
}

Item::Item(string type, string path) : type(type), path(path) {
    SDL_Surface *surface = IMG_Load(path.c_str());
    if (surface == nullptr) {
        cerr << "Error loading item texture: " << IMG_GetError() << " " << type << endl;
        exit(1);
    }
    item_texture = SDL_CreateTextureFromSurface(Window::renderer, surface);
    if (item_texture == nullptr) {
        cerr << "Error creating item texture: " << SDL_GetError() << endl;
        exit(1);
    }
    SDL_FreeSurface(surface);
    int edge = randInt(0, 3);

    switch (edge) {
        case 0:  // Top edge
            x = randDouble(0, MAP_WIDTH);
            y = -h - 5;
            break;
        case 1:  // Bottom edge
            x = randDouble(0, MAP_WIDTH);
            y = MAP_HEIGHT;
            break;
        case 2:  // Left edge
            x = -w - 5;
            y = randDouble(0, MAP_HEIGHT);
            break;
        case 3:  // Right edge
            x = MAP_WIDTH;
            y = randDouble(0, MAP_HEIGHT);
            break;
    }
}

void Item::draw(const Camera &camera) {
    //    cout << direction << " " << speed << "\n";
    if (type == "FAST_SHOT") {
        accentColor = {158, 0, 89, 255};
    } else if (type == "HP_PACK") {
        accentColor = {214, 40, 40, 255};
    } else if (type == "SLOWDOWN_ENEMIES") {
        accentColor = {30, 150, 252, 255};
    } else if (type == "TRIPPLE_SHOT") {
        accentColor = {255, 243, 0, 255};
    } else if (type == "PIERCE_SHOT") {
        accentColor = {255, 183, 3, 255};
    } else if (type == "SHIELD") {
        accentColor = {199, 198, 197, 255};
    }
    SDL_FRect dst = {x - camera.getX(), y - camera.getY(), w, h};
    SDL_RenderCopyF(Window::renderer, item_texture, nullptr, &dst);
}
void Item::update() {
    x += speed * cos(direction) * dt;
    y += speed * sin(direction) * dt;
}

bool Item::intersect(double x, double y, double w, double h) {
    return this->x<x + w &&this->x + this->w> x && this->y<y + h &&this->y + this->h> y;
}
bool Item::isOutOfBounds() const {
    return x < -w - 5 || x > MAP_WIDTH || y < -h - 5 || y > MAP_HEIGHT;
}
bool Item::isOutOfMap() const {
    return x < 0 || x + w > MAP_WIDTH || y < 0 || y + h > MAP_HEIGHT;
}
void Item::applyEffect(Hero &hero, MultiEnemy &enemies) {
    if (type == "FAST_SHOT") {
        hero.setFastShot(true);
    } else if (type == "HP_PACK") {
        hero.setHealth(hero.getHealth() < 0.9 ? hero.getHealth() + 0.1 : 1.0);
    } else if (type == "SLOWDOWN_ENEMIES") {
        enemies.setSlow(true);
    } else if (type == "TRIPPLE_SHOT") {
        hero.setTrippleShot(true);
    } else if (type == "PIERCE_SHOT") {
        hero.setPierceShot(true);
    } else if (type == "SHIELD") {
        hero.setShield(true);
    }
}
