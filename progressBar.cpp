#include "ProgressBar.h"

#include "Text.h"
#include "Window.h"

ProgressBar::ProgressBar(int w, int h, int x, int y, string label, bool hasOutline, SDL_Color color) : w(w), h(h), x(x), y(y), label(label), hasOutline(hasOutline), color(color) {}

ProgressBar::~ProgressBar() {}

void ProgressBar::draw() const {
    Text text(Window::renderer, "res/PressStart2P.ttf", h, label, {color.r, color.g, color.b, color.a});
    text.display(x, y, Window::renderer);
    SDL_Rect inner = {x + text.getW() + 10, y, _w, h};
    if (hasOutline) {
        SDL_Rect outer = {x + text.getW() + 10, y, w, h};
        SDL_SetRenderDrawColor(Window::renderer, color.r, color.g, color.b, color.a);
        SDL_RenderDrawRect(Window::renderer, &outer);
        SDL_RenderFillRect(Window::renderer, &inner);
    } else {
        SDL_SetRenderDrawColor(Window::renderer, color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(Window::renderer, &inner);
    }
}

void ProgressBar::update(double progress) {
    this->progress = progress;
    _w = progress * w;
}
