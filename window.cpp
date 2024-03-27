#include "Window.h"

#include "Includes.h"

using namespace std;

SDL_Renderer *Window::renderer = nullptr;
Window::Window(const string &title, int width, int height) : _title(title), _width(width), _height(height) {
    _close = !init();
}

Window::~Window() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(_window);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    Mix_CloseAudio();
    SDL_DestroyTexture(mapTexture);
}

bool Window::init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cerr << "Init fail!";
        return 0;
    }
    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
        cerr << "Failed to init SDL_image.\n";
        return 0;
    }
    if (TTF_Init() == -1) {
        cerr << "Failed to init SDL_ttf.\n";
        return 0;
    }
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
        cerr << "Failed to init SDL_mixer.\n";
        return 0;
    }

    _window = SDL_CreateWindow(
        _title.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        _width, _height,
        //        SDL_WINDOW_RESIZABLE
        0);
    if (_window == nullptr) {
        cerr << "Failed to create window!";
        return 0;
    }

    renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    //    SDL_RENDERER_PRESENTVSYNC
    if (renderer == nullptr) {
        cerr << "Failed to create renderer!";
        return 0;
    }
    SDL_Surface *mapSurface = IMG_Load("res/map.png");
    if (!mapSurface) {
        cerr << "Failed to load image: " << IMG_GetError() << endl;
        return 0;
    }
    mapTexture = SDL_CreateTextureFromSurface(renderer, mapSurface);
    SDL_FreeSurface(mapSurface);

    return true;
}

pair<int, int> Window::pollEvents(SDL_Event &event) {
    switch (event.type) {
        case SDL_QUIT:
            _close = true;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    _close = true;
                    break;
                case SDLK_p:
                    isPaused = !isPaused;
                    break;
                case SDLK_f:
                    heroAutoShoot = !heroAutoShoot;
                    break;
                default:
                    break;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            int x, y;
            Uint32 mouseState = SDL_GetMouseState(&x, &y);
            return {x, y};
            break;
    }
    return {-1, -1};
}

void Window::clear() const {
    SDL_SetRenderDrawColor(renderer, 35, 35, 35, 255);
    SDL_RenderClear(renderer);
    if (mapTexture) {
        SDL_RenderCopy(renderer, mapTexture, NULL, NULL);
    }
}
void Window::present() const {
    SDL_RenderPresent(renderer);
}