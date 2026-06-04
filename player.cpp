#include <player.h>
#include <laser.h>
#include <block.h>
#include <asteroid.h>
#include <engine.h>
#include <gameState.h>

#include <vector>
#include <algorithm>
#include <iostream>

extern float leftEdge;
extern float rightEdge;

// List of Animation
extern std::vector<Animation> animations;

// Player
Player player;

// extern int player_max_vel_x;
// extern int player_min_vel_x;
// extern int player_min_max_vel_x;

// extern int player_max_vel_y;
// extern int player_min_vel_y;
// extern int player_min_max_vel_y;

extern float gravity_phase;
extern int level_width;

extern float oxygen_level;
extern float oxygen_max;

extern std::vector<std::vector<Tile>> grid;
extern std::vector<Block> blocks;

extern int teleporter_state;

extern GameState game_state;


// int player_max_vel_y = -300;
// int player_min_vel_x = 100;
// int player_min_max_vel_x = 100; // or whatever your logic uses

int player_max_vel_x = 200;
int player_min_vel_x = 100;
int player_min_max_vel_x = player_max_vel_x - player_min_vel_x;

int player_max_vel_y = -300;
int player_min_vel_y = -100;
int player_min_max_vel_y = player_max_vel_y - player_min_vel_y;





// Load Animation (from series of files)
Animation loadAnimation(const char *file_base, int no_frames, float duration, bool loop) {
    // File name
    char file[1024];

    // Animation
    Animation result;

    // Load frames
    for(int i = 0; i < no_frames; i++) {
        snprintf(file, 1024, "%s%03d.png", file_base, i);
        result.frames.push_back(loadTexture(file));
    }

    // Set parameters
    result.no_frames = result.frames.size();
    result.duration = duration;
    result.loop = loop;

    // Return
    return result;
}


void player_movement(float dt, float gravity, Player &player, std::vector<Block> &blocks, std::vector<std::vector<Tile>> &grid, std::vector<Animation> &animations)
{
    // Right Key
    if (keyIsPressed(KEY_RIGHT) || keyIsPressed(KEY_D))
    {
        // player.vel.x += 250;
        player.vel.x += player_min_vel_x + player_min_max_vel_x * gravity_phase; // Player speed increases with gravity
    }

    // Left Key
    if (keyIsPressed(KEY_LEFT) || keyIsPressed(KEY_A))
    {
        // player.vel.x -= 250;
        player.vel.x -= player_min_vel_x + player_min_max_vel_x * gravity_phase;
    }

    // Jump
    if (keyPressedThisFrame(KEY_SPACE) || keyPressedThisFrame(KEY_UP) || keyPressedThisFrame(KEY_W))
    {
        // player.vel.y = -750; // Initial setting
        if (player.isStanding)
        {
            player.vel.y = player_max_vel_y;
            player.state = JUMPING;
            animations[2].start = getTimeInSeconds();
        }
    }

    // Apply gravity
    // player.vel.y += 981 * dt; // Earth Gravity
    player.vel.y += gravity * dt; // Gravity changes

    // Move Player
    player.pos += player.vel * dt;
    if (player.pos.x < player.size.x / 2)
    {
        player.pos.x = player.size.x / 2;
    }
    else if (player.pos.x > level_width - player.size.x / 2)
    {
        player.pos.x = level_width - player.size.x / 2;
    }

    // Clear standing flag
    player.isStanding = false;

    // Process collisions
    for (int i = 0; i < blocks.size(); i++)
    {
        collisions(player, blocks[i]);
    }
    // collisionsBroad(player, blocks, grid);

    // Update Animation
    if (player.state == IDLE)
    {
        // Idle Transitions
        if (player.isStanding && player.vel.x != 0)
        {
            player.state = RUNNING;
        }
        else if (player.isStanding == false)
        {
            player.state = FALLING;
        }
    }
    else if (player.state == RUNNING)
    {
        // Running Transitions
        if (player.isStanding && player.vel.x == 0)
        {
            player.state = IDLE;
            animations[0].start = getTimeInSeconds();
        }
        else if (player.isStanding == false)
        {
            player.state = FALLING;
        }
    }
    else if (player.state == JUMPING)
    {
        // Jumping Transitions
        if (player.isStanding && player.vel.x == 0)
        {
            player.state = IDLE;
        }
        else if (player.isStanding && player.vel.x != 0)
        {
            player.state = RUNNING;
        }
        else if (getTimeInSeconds() > animations[2].start + animations[2].duration)
        {
            player.state = FALLING;
        }
    }
    else if (player.state == FALLING)
    {
        // Falling Transitions
        if (player.isStanding && player.vel.x == 0)
        {
            player.state = IDLE;
        }
        else if (player.isStanding && player.vel.x != 0)
        {
            player.state = RUNNING;
        }
    }
}



// // Check for collisions between player and tile
// void collisions(Player &player, Block &block) {
//     // Bounds of player & platform
//     //Block platform = *grid[x][y].occupyingBlock;
//     //std::cout << "Block Collided X: " << platform.pos.x << std::endl;

//     float playerLeft   = player.pos.x - player.size.x/2;
//     float playerRight  = player.pos.x + player.size.x/2;
//     float playerTop    = player.pos.y - player.size.y/2;
//     float playerBottom = player.pos.y + player.size.y/2;

//     float platformLeft   = block.pos.x; 
//     float platformRight  = block.pos.x + block.size.x;
//     float platformTop    = block.pos.y;
//     float platformBottom = block.pos.y + block.size.y;

//     // Check if player and tile are colliding
//     if((playerLeft < platformRight) && (playerRight > platformLeft) &&
//         (playerTop < platformBottom) && (playerBottom > platformTop)) {
//             if(block.isCollidable) {
//                 // Process Collision
//                 double tx = 1000000;
//                 double ty = 1000000;

//                 // If player is going left
//                 if(player.vel.x < 0) {
//                     // Calculate time since collision in X
//                     tx = (playerLeft - platformRight) / player.vel.x;
//                 } else if(player.vel.x > 0) {
//                     // Calculate time since collision in X
//                     tx = (playerRight - platformLeft) / player.vel.x;
//                 }

//                 // If player is going up
//                 if(player.vel.y < 0) {
//                     // Calculate time since collision in Y
//                     ty = (playerTop - platformBottom) / player.vel.y;
//                 } else if(player.vel.y > 0) {
//                     // Calculate time since collision in Y
//                     ty = (playerBottom - platformTop) / player.vel.y;
//                 }

//                 // Work out which collision to apply
//                 if(tx < ty) {
//                     // Collided horizontally first
//                     if(player.vel.x < 0) {
//                         // Stop player moving
//                         player.vel.x = 0;

//                         // Correct position
//                         player.pos.x = platformRight + player.size.x/2;
//                     } else {
//                         // Stop player moving
//                         player.vel.x = 0;

//                         // Correct position
//                         player.pos.x = platformLeft - player.size.x/2;
//                     }
//                 } else {
//                     // Collided vertically first
//                     if(player.vel.y < 0) {
//                         // Stop player moving
//                         player.vel.y = 0;

//                         // Correct position
//                         player.pos.y = platformBottom + player.size.y/2;
//                     } else {
//                         // Stop player moving
//                         player.vel.y = 0;
                
//                         // Correct position
//                         player.pos.y = platformTop - player.size.y/2;

//                         // Player is standing
//                         player.isStanding = true;
//                     }
//                 }

//             } else if(!block.isCollidable) {
//                 // Process non-collidable block (e.g. oxygen)
//                 if(block.type == 3) {
//                     // Collect Oxygen, increase oxygen level, remove block from game
//                     oxygen_level +=20;
//                     if(oxygen_level > oxygen_max) {
//                         oxygen_level = oxygen_max;
//                     }
//                     // Remove block from vector
//                     block.type = 0;
//                     grid[block.pos.x/32][block.pos.y/32].isOccupied = false;
//                     blocks.erase(std::remove_if(blocks.begin(), blocks.end(), [](Block &b){ return b.type == 0; }), blocks.end());
//                 } else if (block.type == 5) {
//                     // Teleporter block
//                     if(teleporter_state == 0) {
//                         block.type = 4;
//                         teleporter_state = 1; // Start activation
//                         game_state = LEVEL_FINISHING; // Level finishing
//                         std::cout << "Teleporter Activated! State now: " << teleporter_state << std::endl;
//                     }
//                 }
//             }
//         }
// }

// // Check for collisions between player and block
// void collisionsBroad(Player &player, std::vector<Block> &blocks, std::vector<std::vector<Tile>> &grid) {
//     //TODO: first broad check for closest blocks to player via grid, then only check collisions with those blocks
// }




// Draw Animation
void drawAnimation(Animation anim, Vec2 pos, Vec2 size) {
    float elapsed = getTimeInSeconds() - anim.start;
    int index = (elapsed / anim.duration) * anim.no_frames;

    if(anim.loop) {
        index = index % anim.no_frames;
    } else {
        index = min(index, anim.no_frames-1);
    }
    drawTexture(anim.frames[index], pos, size);
}

void drawPlayer(Player &player, float screen_scroll_offset, std::vector<Animation> &animations) {
    Vec2 screen_pos = player.pos;
    screen_pos.x -= screen_scroll_offset;


    if(player.state == IDLE) {
        // Play Idle Animation
        Vec2 size = Vec2(player.size.x, player.size.y);
        int pos_y = size.y/2;
        drawAnimation(animations[0], Vec2(screen_pos.x-size.x/2, screen_pos.y - pos_y+6), size);
    } else if(player.state == RUNNING) {
        // Play Running Animation
        if(player.vel.x < 0) {
            Vec2 size = Vec2(-44, player.size.y);
            int pos_y = size.y/2;
            //size.x *= 376.f/290.f;
            //size.y *= 520.f/500.f;
            drawAnimation(animations[1], Vec2(screen_pos.x-size.x/2, screen_pos.y - pos_y+6), size);
            //drawAnimation()
        } else {
            Vec2 size = Vec2(44, player.size.y);
            int pos_y = size.y/2;
            //size.x *= 376.f/290.f;
            //size.y *= 520.f/500.f;
            drawAnimation(animations[1], Vec2(screen_pos.x-size.x/2, screen_pos.y - pos_y+6), size);
        }
    } else if(player.state == JUMPING) {
        // Play Jumping Animation
        if(player.vel.x < 0) {
            Vec2 size = Vec2(-player.size.x, player.size.y);
            size.x *= 399.f/290.f;
            size.y *= 543.f/500.f;
            drawAnimation(animations[2], screen_pos-size/2, size);
        } else {
            Vec2 size = player.size;
            size.x *= 399.f/290.f;
            size.y *= 543.f/500.f;
            drawAnimation(animations[2], screen_pos-size/2, size);
        }
    } else if(player.state == FALLING) {
        // Play Falling Animation
        if(player.vel.x < 0) {
            Vec2 size = Vec2(-player.size.x, player.size.y);
            size.x *= 399.f/290.f;
            size.y *= 543.f/500.f;
            drawAnimation(animations[3], screen_pos-size/2, size);
        } else {
            Vec2 size = player.size;
            size.x *= 399.f/290.f;
            size.y *= 543.f/500.f;
            drawAnimation(animations[3], screen_pos-size/2, size);
        }
    }
}