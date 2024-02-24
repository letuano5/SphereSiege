#pragma once

class Bullet {
public:
    Bullet(int x, int y, double angle);
    ~Bullet();
    void update();
//    bool isOffScreen() const;

    int getX() const { return x; }
    int getY() const { return y; }

private:
    int x, y;
    double angle;
    static constexpr int speed = 2;
};
