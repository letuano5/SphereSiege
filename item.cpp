#include "Item.h"
Item::Item(string type) : type(type) {
    int edge = rand() % 4;

    switch (edge) {
        case 0:  // Top edge
            x = randDouble(0, MAP_WIDTH);
            y = 0;
            break;
        case 1:  // Bottom edge
            x = randDouble(0, MAP_WIDTH);
            y = MAP_HEIGHT;
            break;
        case 2:  // Left edge
            x = 0;
            y = randDouble(0, MAP_HEIGHT);
            break;
        case 3:  // Right edge
            x = MAP_WIDTH;
            y = randDouble(0, MAP_HEIGHT);
            break;
    }
}
Item::~Item() {}

void Item::draw(const Camera &camera) {
    //    cout << direction << " " << speed << "\n";
    string label;
    SDL_Color innerColor, outerColor;
    if (type == "FAST_SHOT") {
        label = "FAST SHOT";
        innerColor = {138, 201, 38, 255};
        outerColor = {161, 212, 81, 255};
    } else if (type == "HP_PACK") {
        label = "HP PACK";
        innerColor = {214, 40, 40, 255};
        outerColor = {222, 83, 83, 255};
    } else if (type == "SLOWDOWN_ENEMIES") {
        label = "SLOWDOWN ENEMIES";
        innerColor = {128, 128, 128, 255};
        outerColor = {100, 100, 100, 255};
    } else if (type == "TRIPPLE_SHOT") {
        label = "TRIPPLE SHOT";
        innerColor = {0, 180, 216, 255};
        outerColor = {128, 218, 236, 255};
    } else if (type == "PIERCE_SHOT") {
        label = "PIERCE SHOT";
        innerColor = {243, 144, 44, 255};
        outerColor = {245, 142, 86, 255};
    }
    w = label.size() * 10;
    SDL_FRect itemInner = {x - camera.getX(), y - camera.getY(), w, h};
    SDL_FRect itemOuter = {x - 1 - camera.getX(), y - 1 - camera.getY(), w + 2, h + 2};
    Text text(Window::renderer, "res/Silkscreen.ttf", 12, label, {200, 200, 200, 255});
    // if ()
    SDL_SetRenderDrawColor(Window::renderer, outerColor.r, outerColor.g, outerColor.b, outerColor.a);
    SDL_RenderDrawRectF(Window::renderer, &itemOuter);
    SDL_SetRenderDrawColor(Window::renderer, innerColor.r, innerColor.g, innerColor.b, innerColor.a);
    SDL_RenderFillRectF(Window::renderer, &itemInner);

    text.display(x + w / 2 - text.getW() / 2 - camera.getX(), y + h / 2 - text.getH() / 2 - camera.getY(), Window::renderer);
}
void Item::update() {
    x += speed * cos(direction) * dt;
    y += speed * sin(direction) * dt;
}

bool Item::intersect(double x, double y, double w, double h) {
    return this->x<x + w &&this->x + this->w> x && this->y<y + h &&this->y + this->h> y;
}
bool Item::isOutOfBounds() const {
    return x < 0 || x > MAP_WIDTH || y < 0 || y > MAP_HEIGHT;
}
void Item::applyEffect(Hero &hero) {
    if (type == "FAST_SHOT") {
        hero.setFastShot(true);
        hero.activeItems[type] = SDL_GetTicks();
    } else if (type == "HP_PACK") {
        hero.setHealth(hero.getHealth() < 0.9 ? hero.getHealth() + 0.1 : 1.0);
    } else if (type == "SLOWDOWN_ENEMIES") {
        hero.activeItems[type] = SDL_GetTicks();
        // hero.setSlowdownEnemies(true);
    } else if (type == "TRIPPLE_SHOT") {
        hero.activeItems[type] = SDL_GetTicks();
        hero.setTrippleShot(true);
    } else if (type == "PIERCE_SHOT") {
        hero.activeItems[type] = SDL_GetTicks();
        hero.setPierceShot(true);
    }
}