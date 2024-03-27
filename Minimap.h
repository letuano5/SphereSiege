#pragma once

#include "Hero.h"
#include "Includes.h"
#include "Items.h"
#include "MultiEnemy.h"

class Minimap {
   public:
    Minimap();
    ~Minimap();
    void update(const Camera& camera);
    void draw(Hero& hero, MultiEnemy& enemies, Items& items);

   private:
    const double RATIO = 0.12;
    const int WIDTH = MAP_WIDTH * RATIO;
    const int HEIGHT = MAP_HEIGHT * RATIO;
    const int X = WINDOW_WIDTH - WIDTH - 20;
    const int Y = WINDOW_HEIGHT - HEIGHT - 20;
    SDL_Rect minimapRect;
    SDL_Rect cameraRect;
    SDL_Texture* minimap_texture = nullptr;
    SDL_Texture* camera_texture = nullptr;
};
