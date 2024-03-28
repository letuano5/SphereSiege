#include "Hero.h"

#include "Includes.h"

Hero::Hero(int w, int h, int x, int y, const string &image_path) : w(w), h(h), x(x), y(y) {
    auto hero_surface = IMG_Load(image_path.c_str());
    if (!hero_surface) {
        cerr << "Failed to create surface.\n";
    }
    hero_texture = SDL_CreateTextureFromSurface(Window::renderer, hero_surface);
    if (!hero_texture) {
        cerr << "Failed to create texture.\n";
    }
    vignette_texture = SDL_CreateTexture(Window::renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, WINDOW_WIDTH, WINDOW_HEIGHT);
    if (!vignette_texture) {
        cerr << "Failed to create vignette texture.\n";
    }
    auto shield_surface = IMG_Load("res/image/shield.png");
    if (!shield_surface) {
        cerr << "Failed to create shield surface.\n";
    }
    shield_texture = SDL_CreateTextureFromSurface(Window::renderer, shield_surface);
    if (!shield_texture) {
        cerr << "Failed to create shield texture.\n";
    }
    shoot_sound = Mix_LoadWAV("res/audio/shoot.wav");
    if (!shoot_sound) {
        cerr << "Failed to load shoot sound.\n";
    }
    hit_sound = Mix_LoadWAV("res/audio/hitHurt.wav");
    if (!hit_sound) {
        cerr << "Failed to load hit sound.\n";
    }
    lost_sound = Mix_LoadWAV("res/audio/chaydeloroi.wav");
    if (!lost_sound) {
        cerr << "Failed to load lost sound.\n";
    }
    SDL_FreeSurface(hero_surface);
    SDL_FreeSurface(shield_surface);
}

Hero::~Hero() {
    SDL_DestroyTexture(hero_texture);
    SDL_DestroyTexture(vignette_texture);
    SDL_DestroyTexture(shield_texture);
    Mix_FreeChunk(shoot_sound);
    Mix_FreeChunk(hit_sound);
    Mix_FreeChunk(lost_sound);
}

void Hero::draw(Camera &camera) {
    x = max(x, 0);
    x = min(x, MAP_WIDTH - w);
    y = max(y, 0);
    y = min(y, MAP_HEIGHT - h);
    //    cerr << x << " " << y << endl;
    camera.adjust(getX(), getY(), getW(), getH());
    SDL_Rect hero = {getX(camera), getY(camera), w, h};

    if (hero_texture) {
        pair<int, int> mousePos = getMousePosition();
        int mouseX = mousePos.first;
        int mouseY = mousePos.second;
        mouseX += camera.getX();
        mouseY += camera.getY();
        double dx = mouseX - (x + w / 2);
        double dy = mouseY - (y + h / 2);
        double angle = atan2(dy, dx) * 180 / M_PI;
        if (shakeDuration > 0) {
            hero.x += randInt(-shakeIntensity, shakeIntensity);
            hero.y += randInt(-shakeIntensity, shakeIntensity);
            shakeDuration--;
        }

        SDL_RenderCopyEx(Window::renderer, hero_texture, nullptr, &hero, angle, nullptr, SDL_FLIP_NONE);
        if (hasShield) {
            SDL_Rect shield = {getX(camera) - 10, getY(camera) - 10, w + 20, h + 20};
            SDL_RenderCopy(Window::renderer, shield_texture, nullptr, &shield);
        }
        for (const auto &bullet : bullets) {
            bullet.draw(camera);
        }

    } else {
        cout << "No texture.\n";
    }
}
void Hero::pollEvents(const Camera &camera) {
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
    x += camera.getX();
    y += camera.getY();
    if (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT) || heroAutoShoot) {
        double currentTime = SDL_GetTicks() / 1000.0;
        double effectiveFireRate = fireRate;
        if (fastShoot) {
            effectiveFireRate /= 2;
        }
        if (currentTime - lastShot >= effectiveFireRate) {
            shoot(x, y);
            lastShot = currentTime;
        }
    }
}

void Hero::shoot(int mouseX, int mouseY) {
    if (!isMuted && Mix_PlayChannel(-1, shoot_sound, 0) == -1) {
        cerr << "Failed to play shoot sound: " << Mix_GetError() << "\n";
    }
    int dx = mouseX - (x + w / 2);
    int dy = mouseY - (y + h / 2);
    double angle = atan2(dy, dx);

    int bulletX = x + w / 2 + cos(angle) * (w / 2);
    int bulletY = y + h / 2 + sin(angle) * (h / 2);

    if (trippleShot) {
        bullets.push_back(Bullet(bulletX, bulletY, angle - PI / 15));
        bullets.push_back(Bullet(bulletX, bulletY, angle));
        bullets.push_back(Bullet(bulletX, bulletY, angle + PI / 15));
    } else {
        bullets.push_back(Bullet(bulletX, bulletY, angle));
    }
}

void Hero::update() {
    for (int i = 0; i < int(bullets.size()); i++) {
        bullets[i].update(dt);
        if (bullets[i].outOfBound()) {
            bullets.erase(bullets.begin() + i);
            i--;
        }
    }
}

int Hero::intersect(int enemyW, int enemyH, double enemyX, double enemyY, Score &score, double enemyDmg) {
    //    cerr << w << " " << h << " " << x << " " << y << " " << enemyW << " " << enemyH << " " << enemyX << " " << enemyY << " " << intersectRectangle(w, h, x, y, enemyW, enemyH, enemyX, enemyY) << endl;
    if (intersectRectangle(w, h, x, y, enemyW, enemyH, enemyX, enemyY)) {
        bool isFlickering = false;
        double currentTime = SDL_GetTicks() / 1000.0;
        if (!hasShield && currentTime - enemyLastHit >= enemyDmgRate) {
            health_point -= enemyDmg;
            enemyLastHit = currentTime;
            isFlickering = true;
            shakeDuration = 7;  // 7 frames
            shakeIntensity = 2;
        }
        if (health_point <= EPS) {
            isLost = 1;
            if (!isMuted && Mix_PlayChannel(-1, lost_sound, 0) == -1) {
                cerr << "Failed to play lost sound: " << Mix_GetError() << "\n";
            }
        }
        if (isFlickering) {
            SDL_SetTextureAlphaMod(vignette_texture, 128);
            SDL_Rect vignette_rect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
            SDL_RenderCopy(Window::renderer, vignette_texture, nullptr, &vignette_rect);
        }
        isFlickering = false;
        return LOSE;
    }
    for (int i = 0; i < int(bullets.size()); i++) {
        const Bullet &bullet = bullets[i];
        if (intersectRectangle(enemyW, enemyH, enemyX, enemyY, bullet.getW(), bullet.getH(), bullet.getX(), bullet.getY())) {
            if (!pierceShot) {
                bullets.erase(bullets.begin() + i);
                i--;
            }
            if (!isMuted && Mix_PlayChannel(-1, hit_sound, 0) == -1) {
                cerr << "Failed to play hit sound: " << Mix_GetError() << "\n";
            }
            return WIN;
        }
    }
    return CONTINUE;
}

void Hero::setFastShot(bool fastShoot) {
    this->fastShoot = fastShoot;
}

void Hero::setHealth(double health) {
    health_point = health;
}

void Hero::setTrippleShot(bool trippleShot) {
    this->trippleShot = trippleShot;
}

void Hero::setPierceShot(bool pierceShot) {
    this->pierceShot = pierceShot;
}
void Hero::setShield(bool shield) {
    hasShield = shield;
}

void Hero::saveHero() {
    //    cerr << "saving hero's info..." << endl;
    ofstream out("res/save/hero.txt");
    out << x << " " << y << "\n";
    out << fastShoot << " " << trippleShot << " " << pierceShot << " " << heroAutoShoot << " " << hasShield << " " << isMuted << "\n";
    out << bullets.size() << "\n";
    for (const auto &bullet : bullets) {
        out << bullet.getX() << " " << bullet.getY() << " ";
        out << setprecision(9) << fixed << bullet.getAngle() << "\n";
    }
    out << setprecision(9) << fixed << health_point << "\n";
    out.close();
}

bool Hero::setHero() {
    ifstream inp("res/save/hero.txt");
    if (!inp.is_open()) {
        return false;
    }
    int x = -1, y = -1;
    inp >> x >> y;
    if (x < 0 || x > MAP_WIDTH || y < 0 || y > MAP_HEIGHT) {
        inp.close();
        return false;
    }
    this->x = x, this->y = y;
    int fastShoot = -1, trippleShot = -1, pierceShot = -1;
    int autoShoot = -1;
    int settingIsMuted = -1;
    int shield = -1;
    inp >> fastShoot >> trippleShot >> pierceShot >> autoShoot >> shield >> settingIsMuted;
    if (fastShoot < 0 || fastShoot > 1) {
        inp.close();
        return false;
    }
    if (trippleShot < 0 || trippleShot > 1) {
        inp.close();
        return false;
    }
    if (pierceShot < 0 || pierceShot > 1) {
        inp.close();
        return false;
    }
    if (autoShoot < 0 || autoShoot > 1) {
        inp.close();
        return false;
    }
    heroAutoShoot = autoShoot;
    isMuted = settingIsMuted;

    this->fastShoot = fastShoot;
    this->trippleShot = trippleShot;
    this->pierceShot = pierceShot;
    this->hasShield = shield;
    int numBullet = -1;
    inp >> numBullet;
    if (numBullet < 0 || numBullet > 1e6) {
        inp.close();
        return false;
    }
    vector<Bullet> bullets;
    for (int i = 0; i < numBullet; i++) {
        int x = -1, y = -1;
        double angle = -1e9;
        inp >> x >> y >> angle;
        if (x < 0 || x > MAP_WIDTH || y < 0 || y > MAP_HEIGHT) {
            inp.close();
            return false;
        }
        if (equalF(angle, -1e9)) {
            inp.close();
            return false;
        }
        bullets.push_back(Bullet(x, y, angle));
    }
    if (int(bullets.size()) != numBullet) {
        inp.close();
        return false;
    }
    this->bullets.swap(bullets);
    double hp = -1;
    inp >> hp;
    if (hp < 0 || hp > 1) {
        return false;
    }
    health_point = hp;
    inp.close();
    return true;
}
