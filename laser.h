#ifndef laser_h_
#define laser_h_

#include <engine.h>
#include <vector>


struct Laser {
    Vec2 pos;
    Vec2 vel;
    Vec2 size;
    Texture texture;
    float angle;
    bool active;
};

void createLaser(std::vector<Laser> &lasers, Vec2 startPos, Texture spritesheet);
void updateLaser(Laser &laser, float dt);
void drawLaser(Laser &laser);

#endif