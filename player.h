#ifndef player_h_
#define player_h_


#include <vector>
#include <algorithm>
#include <iostream>

#include <block.h>
#include <engine.h>
#include <gameState.h>


// Simple structure to store an animation
// struct Animation;

struct Animation {
    std::vector<Texture> frames;
    int no_frames;
    float duration;
    bool loop;
    float start;
};


// Animation State
enum AnimState {IDLE, RUNNING, JUMPING, FALLING};

// Player
class Player {
    public:
    Vec2 pos;
    Vec2 vel;
    Vec2 size;
    bool isStanding;
    AnimState state;
};

// Load Animation (from series of files)
Animation loadAnimation(const char *file_base, int no_frames, float duration, bool loop);

void player_movement(float dt, float gravity, Player &player, std::vector<Block> &blocks, std::vector<std::vector<Tile>> &grid, std::vector<Animation> &animations);

// Draw Animation
void drawAnimation(Animation anim, Vec2 pos, Vec2 size);

void drawPlayer(Player &player, float screen_scroll_offset, std::vector<Animation> &animations);


#endif