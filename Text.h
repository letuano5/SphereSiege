#pragma once
#include "Includes.h"
#include "Window.h"
class Text {
   public:
    Text(const string &font_path, int font_size, const string &message_text, const SDL_Color &color);
    ~Text();
    void display(double x, double y) const;

    static SDL_Texture *loadFont(const string &font_path, int font_size, const string &message_text, const SDL_Color &color);

    int getW() const;
    int getH() const;
    double getX() const;
    double getY() const;

private :
    double x, y;
    SDL_Texture *text_texture = nullptr;
    mutable SDL_FRect text_rect;
};
