#include "starfield.h"
#include <engine.h>
#include <vector>

std::vector<Star> stars;
int star_count = 200;
float star_off_time = 0.5f;
// float star_twinkle_timer = 0;

Vec2 screen_star_pos = Vec2::zero;


void initStarfield(int level_width) {
    for(int i = 0; i < star_count; i++) {
        Star star;
        star.x = uniform(0, level_width + WINDOW_WIDTH/2); // Screen scrolls after 1/2 window_width
        star.y = uniform(0, WINDOW_HEIGHT);
        star.size = uniform(1, 3);
        star.star_twinkle_timer = 0;
        stars.push_back(star);
    }  
}



void updateStarfield(float dt) {
        // Starfield /// WORK ON THIS
    for(int i = 0; i < star_count; i++) {
        stars[i].star_twinkle_timer -= dt;
        if (stars[i].star_twinkle_timer > 0) {
            continue;
        }

        if (stars[i].star_twinkle_timer < 0) {
            stars[i].star_twinkle_timer = 0;
        }

        if (uniform(0,1) < 0.001f) {
            stars[i].star_twinkle_timer = star_off_time;
        }
    }
}


void renderStarfield(float screen_scroll_offset) {
    // Draw starfield
    for(int i = 0; i < star_count; i++) {
        Vec2 star_pos = Vec2(stars[i].x, stars[i].y);
        // star_pos.x -= screen_scroll_offset * (stars[i].x / level_width); // Stretching starfield 
        
        Vec2 screen_star_pos = star_pos;
        screen_star_pos.x -= screen_scroll_offset/ (3*(4-stars[i].size));
        
        if (stars[i].star_twinkle_timer == 0) {
            fillEllipse(screen_star_pos, Vec2(stars[i].size, stars[i].size), Color::white);
        }
    }
}