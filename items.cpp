#include "Items.h"

Items::Items() {}
Items::~Items() {
    for (int i = 0; i < int(items.size()); i++) {
        delete items[i];
        items[i] = nullptr;
    }
    items.clear();
}
bool Items::checkTime() {
    clock_t currentTime = clock();
    double diffTime = (currentTime - lastTimeSpawned) / double(CLOCKS_PER_SEC);
    return diffTime > DIF_SPAWN_TIME;
}
void Items::spawnItem(Hero& hero, const Camera& camera, MultiEnemy &enemies) {
    if (items.empty() || checkTime()) {
        lastTimeSpawned = clock();
        int itemType = randInt(0, 4);
        items.push_back(new Item(itemTypes[itemType]));
    }
    for (int i = 0; i < int(items.size()); i++) {
        items[i]->draw(camera);
        items[i]->update();
        if (items[i]->intersect(hero.getX(), hero.getY(), hero.getW(), hero.getH())) {
            items[i]->applyEffect(hero, enemies);
            delete items[i];
            items[i] = nullptr;
            items.erase(items.begin() + i);
            i--;
            cout << "Item collected\n";
            continue;  // Skip the rest of the loop
        }
        if (items[i]->isOutOfBounds()) {
            delete items[i];
            items[i] = nullptr;
            items.erase(items.begin() + i);
            i--;
            continue;  // Skip the rest of the loop
        }
    }
}
