#include "Minimap.h"

Minimap::Minimap() {
    minimapRect = {X, Y, WIDTH, HEIGHT};
    SDL_Surface* minimap_surface = IMG_Load("res/image/minimap.png");
    if (!minimap_surface) {
        cerr << "Failed to load minimap image.\n";
    }
    minimap_texture = SDL_CreateTextureFromSurface(Window::renderer, minimap_surface);
    if (!minimap_texture) {
        cerr << "Failed to create vignette texture.\n";
    }
    SDL_Surface* camera_surface = IMG_Load("res/image/minicamera.png");
    if (!camera_surface) {
        cerr << "Failed to load camera image.\n";
    }
    camera_texture = SDL_CreateTextureFromSurface(Window::renderer, camera_surface);
    if (!camera_texture) {
        cerr << "Failed to create camera texture.\n";
    }

    SDL_FreeSurface(minimap_surface);
    SDL_FreeSurface(camera_surface);
}
Minimap::~Minimap() {
    SDL_DestroyTexture(minimap_texture);
    SDL_DestroyTexture(camera_texture);
}
void Minimap::update(const Camera& camera) {
    cameraRect = {X + (camera.getX() * RATIO), Y + (camera.getY() * RATIO), (WINDOW_WIDTH * RATIO), (WINDOW_HEIGHT * RATIO)};
}
void Minimap::draw(Hero& hero, MultiEnemy& enemies, Items& items) {
    if (minimap_texture) {
        SDL_RenderCopy(Window::renderer, minimap_texture, NULL, &minimapRect);
    }
    // Draw the hero on the minimap
    SDL_Rect rect = {X + (hero.getX() * RATIO), Y + (hero.getY() * RATIO), (hero.getW() * RATIO), (hero.getH() * RATIO)};
    SDL_SetRenderDrawColor(Window::renderer, 200, 200, 200, 255);
    SDL_RenderFillRect(Window::renderer, &rect);

    // Draw the enemies on the minimap
    auto E = enemies.getEnemies();
    auto I = items.getItems();
    auto B = hero.getBullets();

    for (auto enemy : E) {
        if (enemy->enemyOutOfMap()) {
            continue;
        }
        SDL_FRect rect = {X + enemy->getX() * RATIO, Y + enemy->getY() * RATIO, 2, 2};
        SDL_SetRenderDrawColor(Window::renderer, 40, 158, 176, 255);
        SDL_RenderFillRectF(Window::renderer, &rect);
    }
    // Draw the items on the minimap
    for (auto item : I) {
        if (item->isOutOfMap()) {
            continue;
        }
        SDL_FRect rect = {X + item->getX() * RATIO, Y + item->getY() * RATIO, item->getW() * RATIO, item->getH() * RATIO};
        SDL_SetRenderDrawColor(Window::renderer, item->getInnerColor().r, item->getInnerColor().g, item->getInnerColor().b, item->getInnerColor().a);
        SDL_RenderFillRectF(Window::renderer, &rect);
    }
    // Draw the bullets on the minimap
    for (auto bullet : B) {
        if (bullet.bulletOutOfMap()) {
            continue;
        }
        SDL_FRect rect = {X + bullet.getX() * RATIO, Y + bullet.getY() * RATIO, 1, 1};
        SDL_SetRenderDrawColor(Window::renderer, 180, 180, 180, 255);
        SDL_RenderFillRectF(Window::renderer, &rect);
    }
    // Draw the camera on the minimap
    if (camera_texture) {
        SDL_RenderCopy(Window::renderer, camera_texture, NULL, &cameraRect);
    }
}
