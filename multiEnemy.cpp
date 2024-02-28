#include "MultiEnemy.h"

MultiEnemy::MultiEnemy() {
    ;
}

void MultiEnemy::generateEnemy(const Hero& hero) {
    for (int i = 0; i < int(enemies.size()); i++) {
        const Enemy& enemy = enemies[i];
        if (rectOutOfBound(enemy.getW(), enemy.getH(), enemy.getX(), enemy.getY())) {
            enemies.erase(enemies.begin() + i);
            i--;
        }
        if (enemy.getHealthPoint() <= 0) {
            enemies.erase(enemies.begin() + i);
            i--;
        }
    }
    if (enemies.empty()) {
//        getTime.init();
        enemies.emplace_back(20, 20, randInt(1, WINDOW_WIDTH), randInt(1, WINDOW_HEIGHT), randInt(1, 1.5), randInt(1, 2), "res/triangle.png");
    }
    for (int i = 0; i < int(enemies.size()); i++) {
        Enemy& enemy = enemies[i];
        enemy.updateEnemy(hero.getX(), hero.getY());
        cerr << "check " << enemy.getW() << " " << enemy.getH() << " " << enemy.getX() << " " << enemy.getY() << endl;
        if (hero.intersect(enemy.getW(), enemy.getH(), enemy.getX(), enemy.getY()) == WIN) {
            enemy.decreaseHealthPoint(1);
        }
        enemy.draw();
    }
}
