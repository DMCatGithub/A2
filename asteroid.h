#ifndef asteroid_h_
#define asteroid_h_

#include <engine.h>
#include <transform.h>

// Asteroid Structure
struct Asteroid {
    Transform transform;
    Vec2 vel;
    Vec2 size;
    float radius;
    float angularVel;
    Texture texture;
    bool active;

    float mass;
    Vec2 force;
};


void randomAsteroid(std::vector<Asteroid> &asteroids, Texture spritesheet, float radius);
void breakAsteroid(std::vector<Asteroid> &asteroids, Asteroid asteroid);
void asteroidCollision(Asteroid &b1, Asteroid &b2);

// Update Asteroid
void updateAsteroid(Asteroid &asteroid, float dt);

// Draw Asteroid
void drawAsteroid(Asteroid &asteroid);

#endif