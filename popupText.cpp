#include "PopupText.h"

#include "Text.h"
PopupText::PopupText(double x, double y, string text, int size, double speed, SDL_Color color)
    : x(x), y(y), text(text), size(size), speed(speed), color(color) {
}

PopupText::~PopupText() {
}

void PopupText::update() {
    speed *= friction;
    y -= speed * dt;
}

void PopupText::draw(Camera& camera) {
    Text pText("res/font/PressStart2P.ttf", size, text, color);
    pText.display(x - camera.getX(), y - camera.getY());
}