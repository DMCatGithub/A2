#ifndef block_h_
#define block_h_

#include <engine.h>
#include <vector>

class Player;


struct Block {Vec2 pos;
    Vec2 size;
    Texture texture;
    bool isCollidable;
    int type; // 0 = normal block, 1 = oxygen collectable, 3 = to delete
};

struct Tile {Vec2 pos; bool isOccupied; Block* occupyingBlock;};

void collisions(Player &player, Block &block);

void createPlatform(int length, int xStart, int y, std::vector<Block> &blocks, std::vector<std::vector<Tile>> &grid);

void createRock(int x, int y, std::vector<Block> &blocks, std::vector<std::vector<Tile>> &grid);

void createRockPlatform(int length, int xStart, int y, std::vector<Block> &blocks, std::vector<std::vector<Tile>> &grid);

void createColumn(int height, int x, int yBottom, std::vector<Block> &blocks, std::vector<std::vector<Tile>> &grid);

void createOxygenBlock(int x, int y, std::vector<Block> &blocks, std::vector<std::vector<Tile>> &grid);



#endif