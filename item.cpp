#include "Item.h"
Item::Item(double x, double y, string type) : x(x), y(y), type(type) {}
Item::~Item() {}

void Item::draw(const Camera &camera) {
    cout << direction << " " << speed << "\n";
    int w = 100, h = 20;
    string label = "ITEM";
    SDL_FRect btnInner = {x - camera.getX(), y - camera.getY(), w, h};
    SDL_FRect btnOuter = {x - 1 - camera.getX(), y - 1 - camera.getY(), w + 2, h + 2};
    Text text(Window::renderer, "res/Silkscreen.ttf", 16, label, {200, 200, 200, 255});
    // if ()
    SDL_SetRenderDrawColor(Window::renderer, 100, 100, 100, 255);
    SDL_RenderDrawRectF(Window::renderer, &btnOuter);
    SDL_SetRenderDrawColor(Window::renderer, 45, 45, 45, 255);
    SDL_RenderFillRectF(Window::renderer, &btnInner);

    text.display(x + w / 2 - text.getW() / 2 - camera.getX(), y + h / 2 - text.getH() / 2 - camera.getY(), Window::renderer);
}
void Item::update() {
    x += cos(direction) * speed;
    y += sin(direction) * speed;
}
