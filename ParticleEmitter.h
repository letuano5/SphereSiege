#pragma once

#include "Camera.h"
#include "Includes.h"
#include "Particle.h"
class ParticleEmitter {
   public:
    ParticleEmitter(double x, double y, int count, int spawnRange, int minSpeed, int maxSpeed, double friction, int minDirection, int maxDirection, SDL_Color color);
    ~ParticleEmitter();
    void draw(Camera& camera);
    void update();
    Particle getParticle(int i) const { return particles[i]; }
    vector<Particle> getAllParticles() const { return particles; }
    bool isDead() {
        for (Particle& particle : particles) {
            if (particle.getSpeed() > 10) {
                return false;
            }
        }
        return true;
    }

   private:
    vector<Particle> particles;
    double x, y;
    int count, spawnRange, minSpeed, maxSpeed;
    double friction, minDirection, maxDirection;
    SDL_Color color;
};
