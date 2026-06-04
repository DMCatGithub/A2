#ifndef level_h_
#define level_h_

#include <vector>
#include<block.h>

extern int level_width; 

void populateLevel1(std::vector<Block>& blocks, std::vector<std::vector<Tile>>& grid);

// void createPlatform(int length, int xStart, int y, std::vector<Block>& blocks, std::vector<std::vector<Tile>>& grid);

// void createRock(int x, int y, std::vector<Block>& blocks, std::vector<std::vector<Tile>>& grid);

// void createRockPlatform(int length, int xStart, int y, std::vector<Block>& blocks, std::vector<std::vector<Tile>>& grid);

// void createColumn(int height, int x, int yBottom, std::vector<Block>& blocks, std::vector<std::vector<Tile>>& grid);

// void createOxygenBlock(int x, int y, std::vector<Block>& blocks, std::vector<std::vector<Tile>>& grid);


#endif