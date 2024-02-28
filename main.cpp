
#include "Includes.h"
#include "Window.h"
#include "MultiEnemy.h"
#include "Hero.h"
using namespace std;


int main(int argv, char** args) {
    srand(time(NULL));
    Uint64 prevTime = SDL_GetPerformanceCounter();
    Uint64 currTime, deltaTime;

    Window window("Sphere Siege", WINDOW_WIDTH, WINDOW_HEIGHT);
    Hero hero(20, 20, WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2 - 100, "res/triangle.png");
//    vector<Enemy*> enemies;
//    for (int i = 0; i < 5; i++) {
//        enemies.push_back(new Enemy(20, 20, randInt(1, WINDOW_WIDTH), randInt(1, WINDOW_HEIGHT), 2, 2, "res/triangle.png"));
//    }
    MultiEnemy enemies;
//    vector<Enemy> enemies;
//    for (int i = 0; i < 5; i++) {
//        enemies.push_back(Enemy(20, 20, randInt(1, WINDOW_WIDTH), randInt(1, WINDOW_HEIGHT), 2, 2, "res/triangle.png"));
////        cerr << enemies.back().getW() << " " << enemies.back().getH() << " " << enemies.back().getX() << " " << enemies.back().getY() << endl;
//    }
//    Enemy enemy(20, 20, randInt(1, WINDOW_WIDTH), randInt(1, WINDOW_HEIGHT), 2, 2, "res/triangle.png");
//    Enemy enemy2(20, 20, randInt(1, WINDOW_WIDTH), randInt(1, WINDOW_HEIGHT), 2, 2, "res/triangle.png");
//    return 0;

    while (!window.isClosed()) {
        SDL_Event event;
        currTime = SDL_GetPerformanceCounter();
        deltaTime = currTime - prevTime;
        double dt = (double)deltaTime / SDL_GetPerformanceFrequency();

        hero.draw();
        hero.pollEvents(dt);
        hero.update(dt);

        if (SDL_PollEvent(&event)) {
            window.pollEvents(event);
        }

        enemies.generateEnemy(hero);

//        enemies[0]->updateEnemy(hero.getX(), hero.getY());
//        enemies[1]->updateEnemy(hero.getX(), hero.getY());
//        for (auto& enemy : enemies) {
////            cerr << "Before update: " << enemy.getX() << " " << enemy.getY() << endl;
//            enemy.updateEnemy(hero.getX(), hero.getY());
////            cerr << "After update: " << enemy.getX() << " " << enemy.getY() << endl;
////            hero.intersect(enemy.getW(), enemy.getH(), enemy.getX(), enemy.getY());
////            enemy.draw();
//        }

//        hero.intersect(enemies[0]->getW(), enemies[0]->getH(), enemies[0]->getX(), enemies[0]->getY());
//        hero.intersect(enemies[1]->getW(), enemies[1]->getH(), enemies[1]->getX(), enemies[1]->getY());
//        for (const auto& enemy : enemies) {
//            hero.intersect(enemy.getW(), enemy.getH(), enemy.getX(), enemy.getY());
//        }
//
//        enemies[0]->draw();
//        enemies[1]->draw();
//        for (auto& enemy : enemies) {
//            enemy.draw();
//        }

//        enemy.updateEnemy(hero.getX(), hero.getY());
//        enemy2.updateEnemy(hero.getX(), hero.getY());
//        hero.intersect(enemy.getW(), enemy.getH(), enemy.getX(), enemy.getY());
//        hero.intersect(enemy2.getW(), enemy2.getH(), enemy2.getX(), enemy2.getY());
//        enemy.draw();
//        enemy2.draw();

        window.clear();
        prevTime = currTime;

    }

    return 0;
}
