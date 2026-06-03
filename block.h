#ifndef block_h_
#define block_h_
#include <engine.h>

struct Block {
    public:
    Vec2 pos;
    Vec2 size;
    Texture texture;
    bool isCollidable;
    int type; // 0 = normal block, 1 = oxygen collectable, 3 = to delete
};

#endif