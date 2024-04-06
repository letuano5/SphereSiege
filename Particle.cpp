#include "Particle.h"

Particle::Particle(double x, double y, double speed, double friction, double direction, double lineWidth, SDL_Color color) : x(x), y(y), speed(speed), friction(friction), direction(direction), lineWidth(lineWidth), color(color) {}
Particle::~Particle() {}

void Particle::draw(Camera& camera) {
    SDL_SetRenderDrawColor(Window::renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawLineF(Window::renderer, x - camera.getX(), y - camera.getY(), x - camera.getX() + cos(direction) * lineWidth, y - camera.getY() + sin(direction) * lineWidth);
}

void Particle::update() {
    speed *= friction;
    x += cos(direction) * speed * dt;
    y += sin(direction) * speed * dt;
}
