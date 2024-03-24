#include "Items.h"
bool replace(string& str, const string& from, const string& to) {
    size_t start_pos = str.find(from);
    if (start_pos == string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}
Items::Items() {
    for (int i = 0; i < 4; i++) {
        string name = itemProgressTypes[i].first;
        replace(name, "_", " ");
        itemsProgress.push_back({itemProgressTypes[i].first, new ProgressBar(120, 8, 20, WINDOW_HEIGHT - 64 + i * 12, name, false, itemProgressTypes[i].second, textColor)});
    }
}
Items::~Items() {
    for (int i = 0; i < int(items.size()); i++) {
        delete items[i];
        items[i] = nullptr;
    }
    items.clear();
    for (auto& item : itemsProgress) {
        delete item.second;
        item.second = nullptr;
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
    for (auto& itemPair : itemsProgress) {
        auto it = activeItems.find(itemPair.first);
        if (it != activeItems.end()) {
            Uint32 currentTime = SDL_GetTicks();
            float progress = 1.0f - (float)(currentTime - it->second) / (itemActiveTime * 1000);
            itemPair.second->update(progress);
            itemPair.second->setTextColor(textActiveColor);
        } else {
            itemPair.second->update(0);
            itemPair.second->setTextColor(textColor);
        }
    }
    for (int i = 0; i < 4; i++) {
        if (itemsProgress[i].second != NULL) {
            itemsProgress[i].second->draw();
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
