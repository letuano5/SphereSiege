#include "Rect.h"

#include "Includes.h"

using namespace std;

Rect::Rect(int w, int h, int x, int y, int r, int g, int b, int a) : w(w), h(h), x(x), y(y), r(r), g(g), b(b), a(a) {
}
Rect::Rect(int w, int h, int x, int y, const string &image_path) : w(w), h(h), x(x), y(y) {
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

Rect::~Rect() {
    SDL_DestroyTexture(triangle_texture);
}

void Rect::draw() const {
    SDL_Rect rect = {x, y, w, h};
    if (triangle_texture) {
        SDL_RenderCopy(Window::renderer, triangle_texture, nullptr, &rect);
    } else {
        SDL_SetRenderDrawColor(Window::renderer, r, g, b, a);
        SDL_RenderFillRect(Window::renderer, &rect);
    }
}
void Rect::pollEvents(SDL_Event &event) {
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
    }
}
