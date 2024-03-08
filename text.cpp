#include "Text.h"

#include <iostream>

#include "Window.h"

Text::Text(SDL_Renderer *renderer, const string &font_path, int font_size, const string &message_text, const SDL_Color &color) {
    text_texture = loadFont(renderer, font_path, font_size, message_text, color);
    SDL_QueryTexture(text_texture, nullptr, nullptr, &text_rect.w, &text_rect.h);
}

void Text::display(int x, int y, SDL_Renderer *renderer) const {
    text_rect.x = x;
    text_rect.y = y;
    SDL_RenderCopy(renderer, text_texture, nullptr, &text_rect);
}

SDL_Texture *Text::loadFont(SDL_Renderer *renderer, const string &font_path, int font_size, const string &message_text, const SDL_Color &color) {
    TTF_Font *font = TTF_OpenFont(font_path.c_str(), font_size);
    if (!font) {
        cerr << "Failed to load font.\n";
    }

    auto text_surface = TTF_RenderText_Solid(font, message_text.c_str(), color);
    if (!text_surface) {
        cerr << "Failed to create text surface.\n";
    }

    auto text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    if (!text_texture) {
        cerr << "Failed to create text texture.\n";
    }
    SDL_FreeSurface(text_surface);
    return text_texture;
}

int Text::getW() const {
    return text_rect.w;
}

int Text::getH() const {
    return text_rect.h;
}
int Text::getX() const {
    return text_rect.x;
}

int Text::getY() const {
    return text_rect.y;
}