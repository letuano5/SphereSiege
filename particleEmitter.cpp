#include "ParticleEmitter.h"
ParticleEmitter::ParticleEmitter(double x, double y, int count, int spawnRange, int minSpeed, int maxSpeed, double friction, int minDirection, int maxDirection, SDL_Color color) : x(x), y(y), count(count), spawnRange(spawnRange), minSpeed(minSpeed), maxSpeed(maxSpeed), friction(friction), minDirection(minDirection), maxDirection(maxDirection), color(color) {
    for (int i = 0; i < count; i++) {
        double radius = randDouble(0, spawnRange / 10);
        double angle = randDouble(0, 2 * PI);
        double x = this->x + cos(angle) * radius;
        double y = this->y + sin(angle) * radius;
        particles.push_back(Particle(x, y, randDouble(minSpeed, maxSpeed), friction, randDouble(minDirection, maxDirection), randDouble(1, 2), color));
    }
}

ParticleEmitter::~ParticleEmitter() {
    particles.clear();
}

void ParticleEmitter::draw(Camera &camera) {
    for (Particle &p : particles) {
        p.draw(camera);
    }
}

void ParticleEmitter::update() {
    for (Particle &p : particles) {
        p.update();
    }
}
