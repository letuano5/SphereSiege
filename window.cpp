#include "Window.h"

#include "Includes.h"


using namespace std;
SDL_Renderer *Window::renderer = nullptr;
Window::Window(const string &title, int width, int height):
    _title(title), _width(width), _height(height) {
            _close = !init();
    }

Window::~Window() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(_window);
    IMG_Quit();
    SDL_Quit();
}

bool Window::init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cerr << "Init fail!";
        return 0;
    }
    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG ) {
        cerr << "Failed to init SDL_image.\n";
    }


    _window = SDL_CreateWindow(
        _title.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        _width, _height,
//        SDL_WINDOW_RESIZABLE
        0
    );
    if (_window == nullptr) {
        cerr << "Failed to create window!";
        return 0;
    }

    renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
//    SDL_RENDERER_PRESENTVSYNC
    if (renderer == nullptr) {
        cerr << "Failed to create renderer!";
        return 0;
    }

    return true;
}


void Window::pollEvents(SDL_Event &event) {
    switch (event.type){
    case SDL_QUIT:
        _close = true;
        break;
    case SDL_KEYDOWN:
        switch (event.key.keysym.sym) {
        case SDLK_ESCAPE:
            _close = true;
            break;
        default:
            break;
        }
    }
}

void Window::clear() const {
    SDL_RenderPresent(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
}
