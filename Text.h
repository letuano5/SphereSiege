#pragma once
#include "Includes.h"

class Text {
   public:
    Text(SDL_Renderer *renderer, const string &font_path, int font_size, const string &message_text, const SDL_Color &color);

    void display(int x, int y, SDL_Renderer *renderer) const;

    static SDL_Texture *loadFont(SDL_Renderer *renderer, const string &font_path, int font_size, const string &message_text, const SDL_Color &color);

    int getW() const;
    int getH() const;
    int getX() const;
    int getY() const;

   private:
    int x, y;
    SDL_Texture *text_texture = nullptr;
    mutable SDL_Rect text_rect;
};
