#include "Items.h"

Items::Items() {}
Items::~Items() {
    for (int i = 0; i < int(items.size()); i++) {
        delete items[i];
        items[i] = NULL;
    }
    items.clear();
}
bool Items::checkTime() {
    clock_t currentTime = clock();
    int diffTime = (currentTime - lastTimeSpawned) / double(CLOCKS_PER_SEC);
    return diffTime > DIF_SPAWN_TIME;
}
void Items::spawnItem(Hero& hero, const Camera& camera) {
    if (items.empty() || checkTime()) {
        lastTimeSpawned = clock();
        int itemType = rand() % 5;
        items.push_back(new Item(itemTypes[itemType]));
    }
    for (int i = 0; i < int(items.size()); i++) {
        items[i]->draw(camera);
        items[i]->update();
        if (items[i]->intersect(hero.getX(), hero.getY(), hero.getW(), hero.getH())) {
            items[i]->applyEffect(hero);
            delete items[i];
            items.erase(items.begin() + i);
            i--;
            cout << "Item collected\n";
            continue;
        }
        if (items[i]->isOutOfBounds()) {
            delete items[i];
            items.erase(items.begin() + i);
            i--;
            continue;
        }
    }
}