#include "Items.h"
bool replace(string& str, const string& from, const string& to) {
    size_t start_pos = str.find(from);
    if (start_pos == string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}
Items::Items() {
    for (int i = 0; i < 5; i++) {
        string name = itemProgressTypes[i].first;
        replace(name, "_", " ");
        itemsProgress.push_back({itemProgressTypes[i].first, new ProgressBar(120, 8, 20, WINDOW_HEIGHT - 76 + i * 12, name, false, itemProgressTypes[i].second, textColor)});
    }
    powerUp_sound = Mix_LoadWAV("res/audio/powerUp.wav");
    if (!powerUp_sound) {
        cerr << "Failed to load item sound effect! SDL_mixer Error: " << Mix_GetError() << endl;
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
    Mix_FreeChunk(powerUp_sound);
}
bool Items::checkTime() {
    clock_t currentTime = clock();
    double diffTime = (currentTime - lastTimeSpawned) / double(CLOCKS_PER_SEC);
    return diffTime > DIF_SPAWN_TIME;
}
void Items::spawnItem(Hero& hero, const Camera& camera, MultiEnemy& enemies, Menu& stats) {
    for (auto it = activeItems.begin(); it != activeItems.end();) {
        if (getTick() > it->second + itemActiveTime * 1000) {
            //            cerr << "kill " << it->first << ": " << getTick() << " " << it->second << endl;
            if (it->first == "FAST_SHOT") {
                hero.setFastShot(false);
            } else if (it->first == "SLOWDOWN_ENEMIES") {
                enemies.setSlow(false);
            } else if (it->first == "TRIPPLE_SHOT") {
                hero.setTrippleShot(false);
            } else if (it->first == "PIERCE_SHOT") {
                hero.setPierceShot(false);
            } else if (it->first == "SHIELD") {
                hero.setShield(false);
            }
            it = activeItems.erase(it);
        } else {
            ++it;
        }
    }
    for (auto& itemPair : itemsProgress) {
        auto it = activeItems.find(itemPair.first);
        if (it != activeItems.end()) {
            Uint32 currentTime = getTick();
            float progress = 1.0f - (float)(currentTime - it->second) / (itemActiveTime * 1000);
            itemPair.second->update(progress);
            itemPair.second->setTextColor(textActiveColor);
        } else {
            itemPair.second->update(0);
            itemPair.second->setTextColor(textColor);
        }
    }
    for (int i = 0; i < 5; i++) {
        if (itemsProgress[i].second != NULL) {
            itemsProgress[i].second->draw();
        }
    }
    if (items.empty() || checkTime()) {
        lastTimeSpawned = clock();
        int itemType = randInt(0, 5);
        items.push_back(new Item(itemTypes[itemType], itemDirPath[itemType]));
    }
    for (int i = 0; i < int(items.size()); i++) {
        items[i]->update();
        items[i]->draw(camera);
        if (items[i]->intersect(hero.getX(), hero.getY(), hero.getW(), hero.getH())) {
            stats.dat[stats.ITEMS_COLLECTED]++;
            if (items[i]->getType() != "HP_PACK") {
                activeItems[items[i]->getType()] = getTick();
            }
            items[i]->applyEffect(hero, enemies);
            delete items[i];
            items[i] = nullptr;
            items.erase(items.begin() + i);
            i--;
            if (!isMuted && Mix_PlayChannel(-1, powerUp_sound, 0) == -1) {
                cerr << "Failed to play shoot sound: " << Mix_GetError() << "\n";
            }
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

void Items::saveItem() {
    ofstream out("res/save/items.txt");
    out << activeItems.size() << "\n";
    for (const auto& remainItem : activeItems) {
        out << remainItem.first << " " << remainItem.second << "\n";
    }
    out << items.size() << "\n";
    for (const auto& item : items) {
        out << setprecision(9) << fixed << item->getX() << " " << item->getY() << "\n";
        out << setprecision(9) << fixed << item->getDir() << "\n";
        out << setprecision(9) << fixed << item->getSpeed() << "\n";
        out << item->getType() << "\n";
        out << item->getPath() << "\n";
    }
    out.close();
}

bool checkType(string curType) {
    for (string s : itemTypes) {
        if (s == curType) {
            return true;
        }
    }
    return false;
}

bool Items::setItem() {
    ifstream inp("res/save/items.txt");
    int numActive = -1;
    inp >> numActive;
    if (numActive < 0 || numActive > 1e6) {
        inp.close();
        return false;
    }
    map<string, Uint32> curActive;
    for (int i = 0; i < numActive; i++) {
        string curType;
        Uint32 lastTime = 1e9;
        inp >> curType >> lastTime;
        if (lastTime == 1e9) {
            inp.close();
            return false;
        }
        if (!checkType(curType)) {
            inp.close();
            return false;
        }
        //        cerr << "add " << curType << " " << lastTime << endl;
        curActive[curType] = lastTime;
    }
    if (int(curActive.size()) != numActive) {
        inp.close();
        return false;
    }
    activeItems.swap(curActive);
    int numRemain = -1;
    inp >> numRemain;
    if (numRemain < 0 || numRemain > 1e6) {
        return false;
    }
    vector<Item*> curItems;
    for (int i = 0; i < numRemain; i++) {
        double x = -1e9, y = -1e9;
        inp >> x >> y;
        if (equalF(x, -1e9) || equalF(y, -1e9)) {
            inp.close();
            return false;
        }
        double dir = -1;
        inp >> dir;
        if (dir < 0 || dir > 2 * PI) {
            inp.close();
            return false;
        }
        double speed;
        inp >> speed;
        if (speed < 20 || speed > 100) {
            inp.close();
            return false;
        }
        string type;
        inp >> type;
        if (!checkType(type)) {
            inp.close();
            return false;
        }
        string path;
        inp >> path;
        if (path.empty()) {
            inp.close();
            return false;
        }
        curItems.push_back(new Item(x, y, dir, speed, type, path));
    }
    if (int(curItems.size()) != numRemain) {
        return false;
    }
    items.swap(curItems);
    inp.close();
    return true;
}
