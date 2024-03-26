#include "Explosion.h"

Explosion::Explosion(int x, int y)
    : x(x), y(y) {
    for (int i = 0; i < numFrames; i++) {
        std::string imagePath = framePath + "explosion-" + std::to_string(i) + ".png";
        SDL_Surface* surface = IMG_Load(imagePath.c_str());
        frames.push_back(SDL_CreateTextureFromSurface(Window::renderer, surface));
        SDL_FreeSurface(surface);
    }
}

Explosion::~Explosion() {
    for (auto frame : frames) {
        SDL_DestroyTexture(frame);
    }
}

void Explosion::update() {
    currentFrame = (currentFrame + 1) % frames.size();
}

void Explosion::draw(Camera& camera) const {
    int w, h;
    SDL_QueryTexture(frames[currentFrame], NULL, NULL, &w, &h);
    SDL_Rect dstRect = {x - camera.getX(), y - camera.getY(), w, h};

    SDL_RenderCopy(Window::renderer, frames[currentFrame], NULL, &dstRect);
}

bool Explosion::isDone() const {
    return currentFrame == frames.size() - 1;
}
