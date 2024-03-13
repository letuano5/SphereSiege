#pragma once
#include "Includes.h"

class Text {
   public:
    Text(SDL_Renderer *renderer, const string &font_path, int font_size, const string &message_text, const SDL_Color &color);

    void display(double x, double y, SDL_Renderer *renderer) const;

    static SDL_Texture *loadFont(SDL_Renderer *renderer, const string &font_path, int font_size, const string &message_text, const SDL_Color &color);

    int getW() const;
    int getH() const;
    double getX() const;
    double getY() const;

   private:
    double x, y;
    SDL_Texture *text_texture = nullptr;
    mutable SDL_FRect text_rect;
};
