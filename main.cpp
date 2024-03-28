#include "Enemy.h"
#include "Hero.h"
#include "Includes.h"
#include "Items.h"
#include "Level.h"
#include "Menu.h"
#include "Minimap.h"
#include "MultiEnemy.h"
#include "ProgressBar.h"
#include "Score.h"
#include "Window.h"

using namespace std;

Window window("Sphere Siege", WINDOW_WIDTH, WINDOW_HEIGHT);
Hero* hero = NULL;
ProgressBar* Health = NULL;
ProgressBar* Progress = NULL;
Score* score = NULL;
Score* best = NULL;
MultiEnemy* enemies = NULL;
Camera* camera = NULL;
Items* items = NULL;
Minimap minimap;
Level* level = NULL;

Menu start("start");
Menu pause("pause");
Menu lost("lost");

Uint64 prevTime = SDL_GetPerformanceCounter();
Uint64 currTime, deltaTime;

void reset() {
    delete hero;
    hero = NULL;
    delete Health;
    Health = NULL;
    delete Progress;
    Progress = NULL;
    delete score;
    score = NULL;
    delete best;
    best = NULL;
    delete enemies;
    enemies = NULL;
    delete camera;
    camera = NULL;
    delete items;
    items = NULL;
    delete level;
    level = NULL;
}

void init() {
    reset();
    hero = new Hero(24, 32, WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2 - 100, "res/image/hero.png");
    Health = new ProgressBar(120, 12, 20, 20, "HP", true, {0, 255, 0, 255}, {});
    Progress = new ProgressBar(120, 12, 220, 20, "progress", true, {150, 150, 150, 255}, {});
    score = new Score(0, "score: ", 520, 20, false, "res/save/score.txt");
    best = new Score(0, "best: ", 750, 20, true, "res/save/best.txt");
    enemies = new MultiEnemy();
    camera = new Camera();
    items = new Items();
    best->readScore();
    level = new Level();
    lastTick = 0;
}

bool canLoad() {
    if (!hero->setHero()) {
        cerr << "cant reinit hero" << endl;
        return false;
    }
    if (!enemies->setEnemies()) {
        cerr << "cant reinit enemies" << endl;
        return false;
    }
    if (!camera->setCamera()) {
        cerr << "cant reinit camera" << endl;
        return false;
    }
    if (!items->setItem()) {
        cerr << "cant reinit items" << endl;
        return false;
    }
    if (!score->readScore()) {
        cerr << "cant reinit score" << endl;
        return false;
    }
    if (!level->readLevel()) {
        cerr << "cant reinit level" << endl;
        return false;
    }
    ifstream inp("res/save/time.txt");
    inp >> lastTick;
    //    cerr << lastTick << endl;
    inp.close();
    return true;
}

void loadGame() {
}

void play() {
    pair<int, int> mousePos = {-1, -1};
    window.clear();
    SDL_Event event;
    currTime = SDL_GetPerformanceCounter();
    deltaTime = currTime - prevTime;
    dt = (double)deltaTime / SDL_GetPerformanceFrequency();
    prevTime = currTime;
    if (SDL_PollEvent(&event)) {
        mousePos = window.pollEvents(event);
    }
    //    cerr << isContinued << endl;
    if (isContinued) {
        //        cout << db << endl;
        //        SDL_Delay(100);
        //        loadGame();
        isStarted = 1;
        isContinued = 0;
        // currTime = SDL_GetPerformanceCounter();
        // deltaTime = currTime - prevTime;
        // dt = (double)deltaTime / SDL_GetPerformanceFrequency();
        // prevTime = currTime;
    }
    //    cout << "? " << isContinued << endl;
    if (isStarted && isPaused) {
        pause.draw(mousePos.first, mousePos.second);
        SDL_RenderPresent(Window::renderer);
        return;
    }

    if (isStarted && isLost) {
        lost.draw(mousePos.first, mousePos.second);
        SDL_RenderPresent(Window::renderer);
        if (!isLost) {
            init();
        }
        return;
    }
    if (isStarted) {
        if (isStarted == 2) {
            init();
            isStarted = 1;
        }

        if (!startTick) {
            startTick = SDL_GetTicks();
        }
        enemies->generateEnemy(*hero, *score, *camera, level->getLevel());
        items->spawnItem(*hero, *camera, *enemies);
        Progress->draw();
        Health->draw();
        score->draw();
        best->draw();
        if (score->getScore() >= best->getScore()) {
            best->update(score->getScore());
        }
        Health->update(hero->health_point);
        Progress->update(level->getLevelProgress());
        hero->draw(*camera);
        hero->pollEvents(*camera);
        hero->update();
        camera->update(dt);
        minimap.update(*camera);
        minimap.draw(*hero, *enemies, *items);
        level->update(score->getScore());

        hero->saveHero();
        enemies->saveEnemies();
        camera->saveCamera();
        items->saveItem();
        score->writeScore();
        best->writeScore();
        level->writeLevel();

        //        cerr << "cam: " << camera->getX() << " " << camera->getY() << endl;
        //        cerr << "hero: " << hero->getX() << " " << hero->getY() << endl;
    } else {
        //        cerr << isStarted << endl;
        start.draw(mousePos.first, mousePos.second);
    }
    window.present();
}

int main(int argv, char** args) {
    srand(time(NULL));
    init();
    canContinue = canLoad();
    while (!window.isClosed()) {
        play();
    }

    ofstream out("res/save/time.txt");
    out << getTick() << "\n";
    out.close();

    reset();

    return 0;
}
