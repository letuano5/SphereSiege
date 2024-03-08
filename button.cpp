#include "Button.h"

#include "Text.h"
#include "Window.h"

Button::Button(int w, int h, int x, int y, string label) : w(w), h(h), x(x), y(y), label(label) {}
Button::~Button() {}
void Button::draw() const {
    SDL_Rect btnInner = {x, y, w, h};
    SDL_Rect btnOuter = {x - 1, y - 1, w + 2, h + 2};
    Text text(Window::renderer, "res/PressStart2P.ttf", 16, label, {200, 200, 200, 255});

    SDL_SetRenderDrawColor(Window::renderer, 100, 100, 100, 255);
    SDL_RenderDrawRect(Window::renderer, &btnOuter);
    SDL_SetRenderDrawColor(Window::renderer, 45, 45, 45, 255);
    SDL_RenderFillRect(Window::renderer, &btnInner);

    text.display(x + w / 2 - text.getW() / 2, y + h / 2 - text.getH() / 2, Window::renderer);
}

bool Button::isClicked(int mouseX, int mouseY) const {
//    if (mouseX != -1) cout << mouseX << " " << mouseY << " reconized event at" << "\n";
    return inRectangle(w, h, x, y, mouseX, mouseY);
}