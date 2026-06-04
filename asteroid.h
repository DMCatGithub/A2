#ifndef asteroid_h_
#define asteroid_h_

// #include <transform.h>
// #include <block.h>
// #include <player.h>
#include <engine.h>
// #include <algorithm>
// #include <gameState.h>

// #include <iostream>
// #include <vector>

class Player;


// Asteroid Structure
struct Asteroid {
    Vec2 pos;
    Vec2 vel;
    Vec2 size;
    float radius;
    float angle;
    float angularVel;
    bool active;

    Texture texture;
};



// Update Asteroid
void randomAsteroid(Asteroid &asteroid, float leftEdge, float rightEdge);
void updateAsteroid(Asteroid &asteroid, float dt);
void drawAsteroid(Asteroid &asteroid, float screen_scroll_offset);

bool collision(Vec2 pos0, Vec2 pos1, Vec2 size1);
bool collision(Vec2 pos0, float radius0, Vec2 pos1, Vec2 size1);

void createExplosion(Asteroid &asteroid);
void knockbackPlayer(Player &player, Vec2 asteroidPos);


#endif