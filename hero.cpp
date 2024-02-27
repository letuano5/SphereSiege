#include "Hero.h"
#include "Includes.h"

using namespace std;

pair<int, int> getMousePosition() {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    return make_pair(mouseX, mouseY);
}

Hero::Hero(int w, int h, int x, int y, const string &image_path) : w(w), h(h), x(x), y(y) {
    auto surface = IMG_Load(image_path.c_str());
    if (!surface) {
        cerr << "Failed to create surface.\n";
    }
    triangle_texture = SDL_CreateTextureFromSurface(Window::renderer, surface);
    if (!triangle_texture) {
        cerr << "Failed to create texture.\n";
    }
    SDL_FreeSurface(surface);
}

Hero::~Hero() {
    SDL_DestroyTexture(triangle_texture);
}

void Hero::draw() const {
    SDL_Rect hero = {x, y, w, h};
//    cerr << "Draw hero at " << x << " " << y << endl;
    if (triangle_texture) {
        pair<int, int> mousePos = getMousePosition();
        int mouseX = mousePos.first;
        int mouseY = mousePos.second;
        double dx = mouseX - (x + w / 2);
        double dy = mouseY - (y + h / 2);
        double angle = atan2(dy, dx) * 180 / M_PI;

        SDL_RenderCopyEx(Window::renderer, triangle_texture, nullptr, &hero, angle, nullptr, SDL_FLIP_NONE);

        for (const auto &bullet : bullets) {
            bullet.draw();
        }

    } else {
        cout << "No texture.\n";
    }
}
void Hero::pollEvents(double dt) {
    double dx = 0;
    double dy = 0;

    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_A]) {
        dx -= 1;
    }
    if (state[SDL_SCANCODE_RIGHT] || state[SDL_SCANCODE_D]) {
        dx += 1;
    }
    if (state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_W]) {
        dy -= 1;
    }
    if (state[SDL_SCANCODE_DOWN] || state[SDL_SCANCODE_S]) {
        dy += 1;
    }
    double length = sqrt(dx * dx + dy * dy);
    if (length > 0) {
        dx /= length;
        dy /= length;
        x += dx * moveSpeed * dt;
        y += dy * moveSpeed * dt;
    }

    int x, y;
    Uint32 mouseState = SDL_GetMouseState(&x, &y);
    if (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)) {
        double currentTime = SDL_GetTicks() / 1000.0;
        if (currentTime - lastShot >= fireRate) {
            shoot(x, y);
            lastShot = currentTime;
        }
    }
}

void Hero::shoot(int mouseX, int mouseY) {
    int dx = mouseX - (x + w / 2);
    int dy = mouseY - (y + h / 2);
    double angle = atan2(dy, dx);

    int bulletX = x + w / 2 + cos(angle) * (w / 2);
    int bulletY = y + h / 2 + sin(angle) * (h / 2);

    bullets.emplace_back(bulletX, bulletY, angle);
}


void Hero::update(double dt) {
    for (int i = 0; i < int(bullets.size()); i++) {
        bullets[i].update(dt);
        if (bullets[i].outOfBound()) {
            bullets.erase(bullets.begin() + i);
            i--;
        }
    }
}

int Hero::intersect(const Enemy& enemy) {
    if (intersectRectangle(w, h, x, y, enemy.getW(), enemy.getH(), enemy.getX(), enemy.getY())) {
        cerr << "YOU LOSE!" << endl;
        exit(0);
        return LOSE;
    }
    for (int i = 0; i < int(bullets.size()); i++) {
        const Bullet& bullet = bullets[i];
        if (intersectRectangle(enemy.getW(), enemy.getH(), enemy.getX(), enemy.getY(), bullet.getW(), bullet.getH(), bullet.getX(), bullet.getY())) {
            cerr << "This enemy has been killed" << endl;
            exit(0);
            return WIN;
        } else {

        }
    }
    cerr << "..." << endl;
    return CONTINUE;
}
