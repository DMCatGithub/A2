#include <level.h>
#include <engine.h>
#include <gameState.h>
#include <block.h>

extern Texture spritesheet;
// extern Block teleporter;
// extern int teleporter_state;

extern std::vector<Texture> blockTex;
extern Texture rockTex;
extern std::vector<Texture> columnTex;
extern Texture oxygen_block_tex;

Block teleporter;
int teleporter_state;
int level_width = 1400;


// Create platforms, columns, and pickups for level 1
void populateLevel1(std::vector<Block>& blocks, std::vector<std::vector<Tile>>& grid) {
    // Ground platforms
    createPlatform(34, 0, 22, blocks, grid);
    createPlatform(7, 36, 22, blocks, grid);
    createPlatform(38, 45, 22, blocks, grid);
    createPlatform(34, 85, 22, blocks, grid);

    // Smaller platforms 
    createPlatform(3, 10, 19, blocks, grid);
    createPlatform(2, 38, 19, blocks, grid);
    createPlatform(4, 40, 16, blocks, grid);
    createPlatform(3, 45, 16, blocks, grid);
    createPlatform(1, 47, 19, blocks, grid);
    createPlatform(1, 50, 19, blocks, grid);
    createPlatform(3, 53, 19, blocks, grid);
    createPlatform(1, 54, 16, blocks, grid);
    createPlatform(1, 59, 19, blocks, grid);
    createPlatform(2, 60, 16, blocks, grid);
    createPlatform(3, 64, 16, blocks, grid);
    createPlatform(1, 65, 19, blocks, grid);
    createPlatform(2, 93, 16, blocks, grid);

    // Create rocks
    createRockPlatform(4, 67, 21, blocks, grid);
    createRockPlatform(3, 68, 20, blocks, grid);
    createRockPlatform(2, 69, 19, blocks, grid);
    createRockPlatform(1, 70, 18, blocks, grid);

    createRockPlatform(4, 73, 21, blocks, grid);
    createRockPlatform(3, 73, 20, blocks, grid);
    createRockPlatform(2, 73, 19, blocks, grid);
    createRockPlatform(1, 73, 18, blocks, grid);

    createRockPlatform(4, 79, 21, blocks, grid);
    createRockPlatform(3, 80, 20, blocks, grid);
    createRockPlatform(2, 81, 19, blocks, grid);
    createRockPlatform(1, 82, 18, blocks, grid);

    createRockPlatform(4, 85, 21, blocks, grid);
    createRockPlatform(3, 85, 20, blocks, grid);
    createRockPlatform(2, 85, 19, blocks, grid);
    createRockPlatform(1, 85, 18, blocks, grid);

    for(int i = 2; i < 10; i++) {
        createRockPlatform(i, 108-i, 12+i, blocks, grid);
    }

    createRock(111, 21, blocks, grid);

    // Create columns
    createColumn(2, 15, 21, blocks, grid);
    createColumn(2, 20, 21, blocks, grid);
    createColumn(3, 24, 21, blocks, grid);
    createColumn(3, 30, 21, blocks, grid);
    createColumn(2, 91, 21, blocks, grid);
    createColumn(2, 98, 21, blocks, grid);

    // Create oxygen blocks
    createOxygenBlock(20, 18, blocks, grid);
    createOxygenBlock(17, 15, blocks, grid);
    teleporter = { grid[5][21].pos, {32, 16}, subTexture(spritesheet, 128, 32, 32, 16), false, 5 };
    blocks.push_back(teleporter);
    teleporter_state = 0;
}

// // Create platforms of block structures
// void createPlatform(int length, int xStart, int y, std::vector<Block> &blocks, std::vector<std::vector<Tile>> &grid) {
//     for(int i = 0; i < length; i++) {
//         int randomIndex = rand() % blockTex.size();
//         blocks.push_back({ {grid[xStart + i][y].pos.x, grid[xStart + i][y].pos.y}, {32, 32}, blockTex[randomIndex], true, 1 });
//         grid[xStart + i][y].isOccupied = true;
//         grid[xStart + i][y].occupyingBlock = &blocks.back(); 
//     }
// }


// void createRock(int x, int y, std::vector<Block> &blocks, std::vector<std::vector<Tile>> &grid) {
//     blocks.push_back({ grid[x][y].pos, {32, 32}, rockTex, true, 1 });
//     grid[x][y].isOccupied = true;
//     grid[x][y].occupyingBlock = &blocks.back();
// }

// void createRockPlatform(int length, int xStart, int y, std::vector<Block> &blocks, std::vector<std::vector<Tile>> &grid) {
//     for(int i = 0; i < length; i++) {
//         createRock(xStart + i, y, blocks, grid);
//     }
// }

// // Create oxygen block
// void createOxygenBlock(int x, int y, std::vector<Block> &blocks, std::vector<std::vector<Tile>> &grid) {
//     blocks.push_back({ grid[x][y].pos, {32, 32}, oxygen_block_tex, false, 3 });
//     grid[x][y].isOccupied = true;
//     grid[x][y].occupyingBlock = &blocks.back();
// }

// // Create column blocks
// void createColumn(int height, int x, int yBottom, std::vector<Block> &blocks, std::vector<std::vector<Tile>> &grid) {
//     for(int i = 0; i < height; i++) {
//         if(i == height - 1) {
//             blocks.push_back({ grid[x][yBottom - i].pos, {32, 32}, columnTex[0], true, 2 });
//         } else if(i == 0 && height > 1){
//             blocks.push_back({ grid[x][yBottom - i].pos, {32, 32}, columnTex[2], true, 2 });
//         } else {
//             blocks.push_back({ grid[x][yBottom - i].pos, {32, 32}, columnTex[1], true, 2 });
//         }
//         grid[x][yBottom - i].isOccupied = true;
//         grid[x][yBottom - i].occupyingBlock = &blocks.back(); 
//     }
// }
