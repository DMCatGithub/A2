#include <collision.h>

#include <algorithm>
#include <iostream>
#include <vector>

#include <engine.h>
#include <asteroid.h>
#include <block.h>
#include <player.h>

#include <gameState.h>


extern const int gridSize;
extern const int gridMaxX;
extern const int gridMaxY;

extern std::vector<std::vector<Tile>> grid;
extern std::vector<Block> blocks;

extern Player player;

extern float oxygen_level;
extern float oxygen_max;

extern int teleporter_state;

extern GameState gameState;


// Check for collisions between player and tile
void collisions(Player &player, Block &block) {
    // Bounds of player & platform
    //Block platform = *grid[x][y].occupyingBlock;
    //std::cout << "Block Collided X: " << platform.pos.x << std::endl;

    float playerLeft   = player.pos.x - player.size.x/2;
    float playerRight  = player.pos.x + player.size.x/2;
    float playerTop    = player.pos.y - player.size.y/2;
    float playerBottom = player.pos.y + player.size.y/2;

    float platformLeft   = block.pos.x; 
    float platformRight  = block.pos.x + block.size.x;
    float platformTop    = block.pos.y;
    float platformBottom = block.pos.y + block.size.y;

    // Check if player and tile are colliding
    if((playerLeft < platformRight) && (playerRight > platformLeft) &&
        (playerTop < platformBottom) && (playerBottom > platformTop)) {
            if(block.isCollidable) {
                // Process Collision
                double tx = 1000000;
                double ty = 1000000;

                // If player is going left
                if(player.vel.x < 0) {
                    // Calculate time since collision in X
                    tx = (playerLeft - platformRight) / player.vel.x;
                } else if(player.vel.x > 0) {
                    // Calculate time since collision in X
                    tx = (playerRight - platformLeft) / player.vel.x;
                }

                // If player is going up
                if(player.vel.y < 0) {
                    // Calculate time since collision in Y
                    ty = (playerTop - platformBottom) / player.vel.y;
                } else if(player.vel.y > 0) {
                    // Calculate time since collision in Y
                    ty = (playerBottom - platformTop) / player.vel.y;
                }

                // Work out which collision to apply
                if(tx < ty) {
                    // Collided horizontally first
                    if(player.vel.x < 0) {
                        // Stop player moving
                        player.vel.x = 0;

                        // Correct position
                        player.pos.x = platformRight + player.size.x/2;
                    } else {
                        // Stop player moving
                        player.vel.x = 0;

                        // Correct position
                        player.pos.x = platformLeft - player.size.x/2;
                    }
                } else {
                    // Collided vertically first
                    if(player.vel.y < 0) {
                        // Stop player moving
                        player.vel.y = 0;

                        // Correct position
                        player.pos.y = platformBottom + player.size.y/2;
                    } else {
                        // Stop player moving
                        player.vel.y = 0;
                
                        // Correct position
                        player.pos.y = platformTop - player.size.y/2;

                        // Player is standing
                        player.isStanding = true;
                    }
                }

            } else if(!block.isCollidable) {
                // Process non-collidable block (e.g. oxygen)
                if(block.type == 3) {
                    // Collect Oxygen, increase oxygen level, remove block from game
                    oxygen_level +=20;
                    if(oxygen_level > oxygen_max) {
                        oxygen_level = oxygen_max;
                    }
                    // Remove block from vector
                    block.type = 0;
                    grid[block.pos.x/32][block.pos.y/32].isOccupied = false;
                    blocks.erase(std::remove_if(blocks.begin(), blocks.end(), [](Block &b){ return b.type == 0; }), blocks.end());
                } else if (block.type == 5) {
                    // Teleporter block
                    if(teleporter_state == 0) {
                        block.type = 4;
                        teleporter_state = 1; // Start activation
                        game_state = LEVEL_FINISHING; // Level finishing
                        std::cout << "Teleporter Activated! State now: " << teleporter_state << std::endl;
                    }
                }
            }
        }
}

// Check for collisions between player and block
void collisionsBroad(Player &player, std::vector<Block> &blocks, std::vector<std::vector<Tile>> &grid) {
    //TODO: first broad check for closest blocks to player via grid, then only check collisions with those blocks
}
