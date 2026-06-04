#include <block.h>
// #include <player.h>
#include <engine.h>
#include <vector>
#include <algorithm>
#include <gameState.h>

extern std::vector<std::vector<Tile>> grid;
extern std::vector<Block> blocks;

// extern Texture rockTex;
// extern std::vector<Texture> blockTex;
// extern std::vector<Texture> columnTex;
// extern Texture oxygen_block_tex;

Texture rockTex;
std::vector<Texture> blockTex;
std::vector<Texture> columnTex;
Texture oxygen_block_tex;

extern Block teleporter;
extern int teleporter_state;

extern float oxygen_level;
extern float oxygen_max;

int gridSize = 32;
int gridMaxX = 125;
int gridMaxY = 25;

std::vector<std::vector<Tile>> grid(gridMaxX, std::vector<Tile>(gridMaxY));

// float oxygen_level = 25;
// float oxygen_max = 50;

extern Texture oxygen_fill_tex;
extern Texture highlight_tex;
extern Texture cannister_tex;




// extern GameState game_state;


// Create platforms of block structures
void createPlatform(int length, int xStart, int y, std::vector<Block> &blocks, std::vector<std::vector<Tile>> &grid) {
    for(int i = 0; i < length; i++) {
        int randomIndex = rand() % blockTex.size();
        blocks.push_back({ {grid[xStart + i][y].pos.x, grid[xStart + i][y].pos.y}, {32, 32}, blockTex[randomIndex], true, 1 });
        grid[xStart + i][y].isOccupied = true;
        grid[xStart + i][y].occupyingBlock = &blocks.back(); 
    }
}

void createRock(int x, int y, std::vector<Block> &blocks, std::vector<std::vector<Tile>> &grid) {
    blocks.push_back({ grid[x][y].pos, {32, 32}, rockTex, true, 1 });
    grid[x][y].isOccupied = true;
    grid[x][y].occupyingBlock = &blocks.back();
}

void createRockPlatform(int length, int xStart, int y, std::vector<Block> &blocks, std::vector<std::vector<Tile>> &grid) {
    for(int i = 0; i < length; i++) {
        createRock(xStart + i, y, blocks, grid);
    }
}

// Create oxygen block
void createOxygenBlock(int x, int y, std::vector<Block> &blocks, std::vector<std::vector<Tile>> &grid) {
    blocks.push_back({ grid[x][y].pos, {32, 32}, oxygen_block_tex, false, 3 });
    grid[x][y].isOccupied = true;
    grid[x][y].occupyingBlock = &blocks.back();
}

// Create column blocks
void createColumn(int height, int x, int yBottom, std::vector<Block> &blocks, std::vector<std::vector<Tile>> &grid) {
    for(int i = 0; i < height; i++) {
        if(i == height - 1) {
            blocks.push_back({ grid[x][yBottom - i].pos, {32, 32}, columnTex[0], true, 2 });
        } else if(i == 0 && height > 1){
            blocks.push_back({ grid[x][yBottom - i].pos, {32, 32}, columnTex[2], true, 2 });
        } else {
            blocks.push_back({ grid[x][yBottom - i].pos, {32, 32}, columnTex[1], true, 2 });
        }
        grid[x][yBottom - i].isOccupied = true;
        grid[x][yBottom - i].occupyingBlock = &blocks.back(); 
    }
}

