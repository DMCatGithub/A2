#ifndef starfield_h_
#define starfield_h_
#include <engine.h>
#include <vector>


struct Star {float x; float y; float size; float star_twinkle_timer;};

extern std::vector<Star> stars;

void initStarfield(int level_width);
void updateStarfield(float dt);
void renderStarfield(float screen_scroll_offset);

#endif