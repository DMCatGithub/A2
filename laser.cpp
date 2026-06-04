#include <laser.h>

#include <engine.h>

// #include "laser.h"

// #include "engine.h"


extern float leftEdge;
extern float rightEdge;




// Create a Laser
void createLaser(std::vector<Laser> &lasers, Vec2 startPos, Texture spritesheet) {
    Laser laser;

    laser.pos = startPos + Vec2(0,-40);
    laser.vel = Vec2(500,0);
    laser.angle = 0; //Check orientation

    laser.texture = subTexture(spritesheet, {240, 0, 240, 240});
    laser.size = Vec2(10, 40);
    laser.active = true;
    
    lasers.push_back(laser);
}

// Update Laser
void updateLaser(Laser &laser, float dt) {
    // If Laser Is Active
    if(laser.active) {
        // Move Laser
        laser.pos += laser.vel * dt;

        // Destroy at Boundary
        if(laser.pos.x < leftEdge) laser.active = false;
        if(laser.pos.x > rightEdge) laser.active = false;
        if(laser.pos.y < 0) laser.active = false;
        if(laser.pos.y > WINDOW_HEIGHT) laser.active = false;
    }
}

// Draw Laser
void drawLaser(Laser &laser) {
    // If Laser is active
    if(laser.active) {
        // Draw Texture and Hitbox
        drawTexture(laser.texture, laser.pos - Vec2(1,1) * 30, Vec2(2,2) * 30, laser.angle);
    }
}