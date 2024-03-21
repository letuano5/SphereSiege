#include "Items.h"

Items::Items() {
    for (int i = 0; i < 4; i++) {
        itemsProgress[i] = new ProgressBar(120, 8, 20, WINDOW_HEIGHT - 64 + i * 12, itemProgressTypes[i].first, false, itemProgressTypes[i].second);
    }
}
Items::~Items() {
    for (int i = 0; i < int(items.size()); i++) {
        delete items[i];
        items[i] = nullptr;
    }
    items.clear();
    for (int i = 0; i < 4; i++) {
        delete itemsProgress[i];
        itemsProgress[i] = nullptr;
    }
    activeItems.clear();
}
bool Items::checkTime() {
    clock_t currentTime = clock();
    double diffTime = (currentTime - lastTimeSpawned) / double(CLOCKS_PER_SEC);
    return diffTime > DIF_SPAWN_TIME;
}
void Items::spawnItem(Hero& hero, const Camera& camera, MultiEnemy& enemies) {
    for (auto it = activeItems.begin(); it != activeItems.end();) {
        if (SDL_GetTicks() > it->second + itemActiveTime * 1000) {
            if (it->first == "FAST_SHOT") {
                hero.setFastShot(false);
            } else if (it->first == "SLOWDOWN_ENEMIES") {
                enemies.setSlow(false);
            } else if (it->first == "TRIPPLE_SHOT") {
                hero.setTrippleShot(false);
            } else if (it->first == "PIERCE_SHOT") {
                hero.setPierceShot(false);
            }
            it = activeItems.erase(it);
        } else {
            ++it;
        }
    }
    for (int i = 0; i < 4; i++) {
        if (itemsProgress[i] != NULL) {
            itemsProgress[i]->update(0);
            itemsProgress[i]->draw();
        }
    }
    if (items.empty() || checkTime()) {
        lastTimeSpawned = clock();
        int itemType = randInt(0, 4);
        items.push_back(new Item(itemTypes[itemType]));
    }
    for (int i = 0; i < int(items.size()); i++) {
        items[i]->update();
        items[i]->draw(camera);
        if (items[i]->intersect(hero.getX(), hero.getY(), hero.getW(), hero.getH())) {
            if (items[i]->getType() != "HP_PACK") {
                activeItems[items[i]->getType()] = SDL_GetTicks();
            }
            items[i]->applyEffect(hero, enemies);
            delete items[i];
            items[i] = nullptr;
            items.erase(items.begin() + i);
            i--;
            cout << "Item collected\n";
            continue;
        }
        if (items[i]->isOutOfBounds()) {
            delete items[i];
            items[i] = nullptr;
            items.erase(items.begin() + i);
            i--;
            continue;
        }
    }
}
