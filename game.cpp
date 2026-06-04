// #include <animation.h>
#include <asteroid.h>
#include <block.h>
#include <collision.h>
#include <game.h>
#include <gameState.h>
#include <laser.h>
#include <player.h>
#include <starfield.h>
// #include <screenScroll.h>
// #include <tile.h>

#include <engine.h>
#include <vector>

#include <level.h>

float oxygen_level = 25;
float oxygen_max = 50;
Texture oxygen_fill_tex;
Texture highlight_tex;
Texture cannister_tex;



extern Player player;

std::vector<Block> blocks;

std::vector<Animation> animations;

std::vector<Laser> lasers;

Texture spritesheet;
Texture sunspritetest;

// Vec2 screen_star_pos = Vec2::zero;
float screen_scroll_offset = 0.0f;




// extern float gravity;
// extern float gravity_phase;
extern int level_width;
// int level_width =1400;
// extern float screen_scroll_offset;

extern Vec2 earth_pos;
// extern Texture earth_texture;
extern Vec2 earth_size;

extern Block teleporter;
extern int teleporter_state;

// extern Texture spritesheet;
// extern Texture cannister_tex;
// extern Texture oxygen_fill_tex;
// extern Texture highlight_tex;



// extern std::vector<std::vector<Tile>> grid;


extern int gridMaxX;
extern int gridMaxY;
extern const int gridSize;
extern std::vector<std::vector<Tile>> grid;


extern std::vector<Asteroid> asteroids;
extern void populateLevel1(std::vector<Block>&, std::vector<std::vector<Tile>>&);

extern void initAsteroid();
extern void checkLaserAsteroidCollisions();

// extern int gravity_background_colour;

extern int star_count;
extern std::vector<Star> stars;

extern Vec2 screen_star_pos;
extern Vec2 earth_screen_pos;

// extern Texture sunspritetest;

// extern float oxygen_level;

float leftEdge = 0.0f;
float rightEdge = WINDOW_WIDTH;

Texture earth_texture;
Vec2 earth_size;
Vec2 earth_pos;
Vec2 earth_screen_pos;

float gravity = 0.0f;
float gravity_phase = 0.0f;
int gravity_background_colour = 0;



// ***************************************************************************
void init() {
// ***************************************************************************

    setWindowTitle("Platformer");
    game_state = PLAYING; // Set game state to playing




    // Level
    // level_width = 4000;
    // leftEdge = 0;
    // rightEdge = 0;
    
    // Load spritesheet (TODO clean up unsuded spritesheet loads)
    spritesheet = loadTexture("./assets/images/spritesheet.png"); // Used for planet + 
    sunspritetest = loadTexture("./assets/images/sun.png"); // Used for sun
    
    earth_texture = subTexture(spritesheet, 0, 65, 210, 210); 

    earth_pos = Vec2::zero;
    // earth_texture = subTexture(spritesheet, 0, 64, 64, 64);
    earth_size = Vec2(64, 64);


    // Load oxygen textures
    // cannister_tex = subTexture(spritesheet, 128, 0, 64, 15);
    // highlight_tex = subTexture(spritesheet, 128, 0, 64, 15);
    // oxygen_fill_tex = subTexture(spritesheet, 128, 16, 64, 15);
    // oxygen_block_tex = subTexture(spritesheet,256, 0, gridSize, gridsize);


    // Load animations
    // 0 = Idle, 1 = Run, 2 = Jump, 3 = Jump Peak, 4 = Teleport Activation, 5 = teleport beep
    // animations.push_back(loadAnimation("./assets/images/astronautIdle", 3, 1.0f, true));
    // animations.push_back(loadAnimation("./assets/images/aRun", 4, 0.5f, true));
    // animations.push_back(loadAnimation("./assets/images/Jump__", 10, 0.5f, false));
    // //loadAnimation("assest/images/Jump__", 
    // animations.push_back(Animation {std::vector<Texture>({loadTexture("./assets/images/Jump__009.png")}), 1, 1.0f, true});
    // // animations.push_back(loadAnimation("./assets/images/teleportActivation__", 18, 10.0f, false));
    // animations.push_back(loadAnimation("./assets/images/teleporter__", 18, 10.0f, false));
    // animations.push_back(loadAnimation("./assets/images/teleportBeep__", 2, 6.0f, false));


    animations.push_back(loadAnimation("./assets/images/astronautIdle", 3, 1.0f, true));
    animations.push_back(loadAnimation("./assets/images/aRun", 4, 1.0f, true));
    animations.push_back(loadAnimation("./assets/images/Jump__", 10, 0.5f, false));
    //loadAnimation("assest/images/Jump__", 
    animations.push_back(Animation {std::vector<Texture>({loadTexture("./assets/images/Jump__009.png")}), 1, 1.0f, true});
    animations.push_back(loadAnimation("./assets/images/teleporter__", 17, 17.0f, false));
    //animations.push_back(loadAnimation("./assets/images/teleporting__", 7, 1.0f, false));

    // Set oxygen levels
    // oxygen_max = 50;
    // oxygen_min = 0;
    // oxygen_level = 25;
    // oxygen_rate = 0; // 0 for testing, increase for more challenge


    // Create Player
    player.pos = Vec2(WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
    player.vel = Vec2::zero;
    player.size = Vec2(gridSize, gridSize*2);
    player.state = IDLE;
    player.isStanding = false;

    // player_max_vel_x = 200;
    // player_min_vel_x = 100;
    // player_min_max_vel_x = player_max_vel_x - player_min_vel_x;

    // player_max_vel_y = -300;
    // player_min_vel_y = -100;
    // player_min_max_vel_y = player_max_vel_y - player_min_vel_y;

    // Create a vector of tiles to act as a grid system for block and tile placement; each cell in the grid is 32x32 pixels
    
    gridMaxX = level_width / gridSize;
    gridMaxY = WINDOW_HEIGHT / gridSize;

    // std::vector<std::vector<Tile>> grid(gridMaxX, std::vector<Tile>(gridMaxY));

    grid.resize(gridMaxX);
    for (int x = 0; x < gridMaxX; x++) {
        grid[x].resize(gridMaxY);
    }


    for (int x = 0; x < gridMaxX; x++) {
        for (int y = 0; y < gridMaxY; y++) {
            grid[x][y] = {Vec2(x * gridSize, y * gridSize ), false, nullptr};
        }
    }


    populateLevel1(blocks, grid);


    initAsteroid();
}
// ***************************************************************************
void update(float dt) {
// ***************************************************************************
    if(game_state == PLAYING || game_state == LEVEL_FINISHING || game_state == LEVEL_FINISHED) {
        
        //updatePlaying(dt);
        // player.vel.x = 0;
        player_movement(dt, gravity, player, blocks, grid, animations);

        // Screen scrolling
        // screenScroll.update(player.pos.x);



        // Update lasers
        for (Laser &laser : lasers) {
            updateLaser(laser, dt);
        }

        // Update asteroids
        for (Asteroid &asteroid : asteroids) {
            updateAsteroid(asteroid, dt);
        }

        // Update laser-asteroid collisions
        checkLaserAsteroidCollisions();
    }
}

// ***************************************************************************
void render(float lag) {
// ***************************************************************************
    clear(Color(24, 20, gravity_background_colour));

    // Scrolling screen
    Vec2 screen_pos = player.pos;
    screen_pos.x -= screen_scroll_offset;

    // Draw starfield
    for(int i = 0; i < star_count; i++) {
        Vec2 star_pos = Vec2(stars[i].x, stars[i].y);
        
        screen_star_pos = star_pos;
        screen_star_pos.x -= screen_scroll_offset/ (3*(4-stars[i].size));
        
        if (stars[i].star_twinkle_timer == 0) {
            fillEllipse(screen_star_pos, Vec2(stars[i].size, stars[i].size), Color::white);
        }
    }

    //Draw blocks
    for(int i = 0; i < blocks.size(); i++) {
        Vec2 screen_block_pos = blocks[i].pos;
        screen_block_pos.x -= screen_scroll_offset;
        if(blocks[i].type != 5 && blocks[i].type != 4) { // Don't draw teleporter block (type 5) as it is drawn separately with animation, and don't draw blocks marked for deletion (type 0)
            // drawTexture(blocks[i].texture, screen_block_pos, {gridSize, gridSize});
            drawTexture(blocks[i].texture, screen_block_pos, Vec2(gridSize, gridSize));

        } 
    }

    // Draw teleporter (one tile below actual position so it is collided with by walking on top of)
    Vec2 screen_teleporter_pos = teleporter.pos;
    screen_teleporter_pos.x -= screen_scroll_offset;
    screen_teleporter_pos.y += gridSize;
    if(teleporter_state == 0) {
        drawTexture(teleporter.texture, screen_teleporter_pos, teleporter.size);
        //std::cout << "Teleporter State: " << teleporter_state << std::endl;
    } else if(teleporter_state == 1) {
        drawAnimation(animations[4], screen_teleporter_pos, teleporter.size);
    } else if(teleporter_state == 2) {
        //drawTexture(animations[5].frames[0], screen_teleporter_pos, teleporter.size);
        drawAnimation(animations[5], screen_teleporter_pos, teleporter.size);
    } else if(teleporter_state == 3) {
        //std::cout << "Teleporter State: " << teleporter_state << std::endl;
        drawTexture(subTexture(spritesheet, 128, 48, 32, 16), screen_teleporter_pos, teleporter.size);
    }

    // Draw Earth / Sun??
    earth_screen_pos = earth_pos;
    earth_screen_pos.x -= screen_scroll_offset;
    drawTexture(earth_texture, earth_screen_pos, earth_size, 0);

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


    // Draw oxygen UI
    drawTexture(cannister_tex, grid[1][1].pos, {64, 15});
    drawTexture(oxygen_fill_tex, grid[1][1].pos, {oxygen_level + 7, 15});
    drawTexture(highlight_tex, grid[1][1].pos, {64, 15});
}


// Close the Game
void close() {
    // TODO: implement save file?
    exit(0);
}
