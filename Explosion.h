#include <vector>

#include "Camera.h"

class Explosion {
    std::vector<SDL_Texture*> frames;
    int x, y;
    int currentFrame = 0;
    const int numFrames = 31;
    const std::string framePath = "res/explosion/";

   public:
    Explosion(int x, int y);

    void update();

    void draw(Camera& camera) const;

    bool isDone() const;
};