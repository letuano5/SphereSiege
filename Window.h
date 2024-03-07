#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include <string>

#include "Includes.h"

using namespace std;
class Window {
   public:
    Window(const string &title, int width, int height);
    ~Window();

    int getW() const { return _width; }
    int getH() const { return _height; }

    pair<int, int> pollEvents(SDL_Event &event);
    void clear() const;
    bool isClosed() const { return _close; }

   private:
    bool init();

   private:
    string _title;
    int _width = 800;
    int _height = 600;

    bool _close = false;

    SDL_Window *_window = nullptr;

   public:
    static SDL_Renderer *renderer;
    static int height;
    static int width;
};
