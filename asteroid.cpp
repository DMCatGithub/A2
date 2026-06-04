// #include <transform.h>
#include <asteroid.h>
#include <block.h>
#include <player.h>
#include <engine.h>
#include <algorithm>
#include <iostream>
#include <vector>


extern const int gridSize;
extern const int gridMaxX;
extern const int gridMaxY;

extern std::vector<std::vector<Tile>> grid;
extern std::vector<Block> blocks;

extern Player player;

static bool explosionActive = false;
static Vec2 explosionPosition = Vec2::zero;
static Vec2 explosionSize = Vec2::zero;
static Vec2 explosionVel = Vec2::zero;
static float explosionAngle = 0.0f;
static float explosionAngularVel = 0.0f;
static float explosionStart = 0.0f;

std::vector<Asteroid> asteroids;

void initAsteroid() {
    // your init logic
}

void checkLaserAsteroidCollisions() {
    // your collision logic
}



// asteroidTexture = loadTexture("./assets/spritesheet.png",Vec2(480,0),Vec2(240,240));

// Generate a new asteroid
void randomAsteroid(Asteroid &asteroid, float leftEdge, float rightEdge) {
    asteroid.radius = uniform(16, 32);
    asteroid.size  = Vec2(asteroid.radius*2, asteroid.radius*2);

    asteroid.pos = Vec2(rightEdge + 100, uniform(0, WINDOW_HEIGHT-200));
    asteroid.vel = Vec2(-(1000), uniform(-1000, 0));

    asteroid.angle = uniform(0,360);
    asteroid.angularVel =  uniform(-180,180);

    asteroid.active = true;
}

// Collision (Point-AABB)
bool collision(Vec2 pos0, Vec2 pos1, Vec2 size1) {
    return (pos0.x < pos1.x + size1.x) &&
            (pos1.x < pos0.x) &&
            (pos0.y < pos1.y + size1.y) &&
            (pos1.y < pos0.y);
}

// Collision (AABB-Circle  - Player/blocks and asteroid)
bool collision(Vec2 pos0, float radius0, Vec2 pos1, Vec2 size1) {
    float tx, ty;

    // Check if circle is inside the rectangle >> uses Point-AABB
    if(collision(pos0, pos1, size1)) {
        return true;
    }

    // Find point on Rectangle closest to Circle (x)
    if(pos0.x < pos1.x) {
        tx = pos1.x; // Left Side
    } else if(pos0.x > pos1.x + size1.x) {
        tx = pos1.x + size1.x; // Right Side
    } else {
        tx = pos0.x; // Circle position
    }

    // Find point on Rectangle closest to Circle (y)
    if(pos0.y < pos1.y) {
        ty = pos1.y; // Top Side
    } else if(pos0.y > pos1.y + size1.y) {
        ty = pos1.y + size1.y; // Bottom Side
    } else {
        ty = pos0.y; // Circle position
    }

    // Compare distance between circle centre and closest point to radius
    if(distance(Vec2(tx, ty), pos0) < radius0) {
        return true;
    }
    return false;
}

// Update asteroid
void updateAsteroid(Asteroid &asteroid, float dt) {
    if (!asteroid.active) return;

    // Move Asteroid
    asteroid.pos += asteroid.vel * dt;
    asteroid.angle += asteroid.angularVel * dt;


    // Asteroid collisions with blocks (Circle-AABB)
    // Check 3x3 grid at asteroid

    // Work out asteroid grid position
    int asteroidGridX = (int)(asteroid.pos.x / gridSize);
    int asteroidGridY = (int)(asteroid.pos.y / gridSize);

    // Check 3x3 positions
    for (int x = asteroidGridX - 1; x <= asteroidGridX + 1; x++) {
        for (int y = asteroidGridY - 1; y <= asteroidGridY + 1; y++) {

            // Skip positions that are off the screen
            if (x < 0 || y < 0 || x >= gridMaxX || y >= gridMaxY)
            continue;

            // Skip is grid position is not occupied
            if (grid[x][y].isOccupied == false)
            continue;

            Block &block = *grid[x][y].occupyingBlock;

            // Use Collision (Circle-AABB)
            if (collision(asteroid.pos, asteroid.radius, block.pos, block.size)) {
                asteroid.active = false;
                createExplosion(asteroid);
                return;
            }
        }
    }

    // Asteroid collision with player (Circle -AABB)
    Vec2 playerPos = player.pos - player.size/2;
    Vec2 playerSize = player.size;

    if(collision(asteroid.pos, asteroid.radius, playerPos, playerSize)) {
        knockbackPlayer(player, asteroid.pos);
        asteroid.active = false;
        createExplosion(asteroid);
        return;
    }
}

void drawAsteroid(Asteroid &asteroid, float screen_scroll_offset) {
    if (!asteroid.active) return;

    Vec2 screenPos = asteroid.pos;
    screenPos.x -= screen_scroll_offset;

    drawTexture(asteroid.texture, screenPos - asteroid.size/2, asteroid.size, asteroid.angle);
}



void createExplosion(Asteroid &asteroid) {
    explosionPosition = asteroid.pos;
    explosionSize = asteroid.size;
    explosionStart = getTimeInSeconds();

    explosionVel = asteroid.vel / 2;
    explosionAngle = asteroid.angle;
    explosionAngularVel = asteroid.angularVel;

    explosionActive = true;
}

void knockbackPlayer(Player &player, Vec2 asteroidPos) {
    Vec2 n = unit(player.pos - asteroidPos);
    player.vel += n * 300.0f;
}




























