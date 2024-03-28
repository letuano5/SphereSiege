#include "Button.h"

#include "Text.h"
#include "Window.h"

Button::Button(int w, int h, int x, int y, string label) : w(w), h(h), x(x), y(y), label(label) {
}
Button::~Button() {
}
void Button::draw() {
    SDL_Rect btnInner = {x, y, w, h};
    SDL_Rect btnOuter = {x - 1, y - 1, w + 2, h + 2};
    Text text("res/font/PressStart2P.ttf", 16, label, labelColor);
    SDL_Color inC, outC;
    if (isMouseOver) {
        inC = {60, 60, 60, 255};
        outC = {120, 120, 120, 255};
    } else {
        inC = innerColor;
        outC = outerColor;
    }
    SDL_SetRenderDrawColor(Window::renderer, outC.r, outC.g, outC.b, outC.a);
    SDL_RenderDrawRect(Window::renderer, &btnOuter);
    SDL_SetRenderDrawColor(Window::renderer, inC.r, inC.g, inC.b, inC.a);
    SDL_RenderFillRect(Window::renderer, &btnInner);

    text.display(x + w / 2 - text.getW() / 2, y + h / 2 - text.getH() / 2);
}

bool Button::isClicked(int mouseX, int mouseY) const {
    //    if (mouseX != -1) cout << mouseX << " " << mouseY << " reconized event at" << "\n";
    return inRectangle(w, h, x, y, mouseX, mouseY);
}

void Button::updateHover(int mouseX, int mouseY) {
    if (inRectangle(w, h, x, y, mouseX, mouseY)) {
        isMouseOver = true;
    } else {
        isMouseOver = false;
    }
}
