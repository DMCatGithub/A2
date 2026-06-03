#include "Collision.h"
#include <algorithm>


// Collision (Point-Axis Aligned Bounding Box)
bool collision(Vec2 pos0, Vec2 pos1, Vec2 size1) {
    return (pos0.x < pos1.x + size1.x) &&
            (pos1.x < pos0.x) &&
            (pos0.y < pos1.y + size1.y) &&
            (pos1.y < pos0.y);
}

// Collision (Circle-Axis Aligned Bounding Box)
bool collision(Vec2 pos0, float radius0, Vec2 pos1, Vec2 size1) {
    float tx, ty;

    // Check if circle is inside the rectangle
    if(collision(pos0, pos1, size1)) {
        return true;
    }

    // Find point on Rectangle closest to Circle (x)
    if(pos0.x < pos1.x) {
        tx = pos1.x; // Left Side
    } else if(pos0.x > pos1.x + size1.x) {
        tx = pos1.x + size1.x; // Right Side
    } else {
        tx = pos0.x; // Circle position
    }

    // Find point on Rectangle closest to Circle (y)
    if(pos0.y < pos1.y) {
        ty = pos1.y; // Top Side
    } else if(pos0.y > pos1.y + size1.y) {
        ty = pos1.y + size1.y; // Bottom Side
    } else {
        ty = pos0.y; // Circle position
    }

    // Compare distance between circle centre and closest point to radius
    if(distance(Vec2(tx, ty), pos0) < radius0) {
        return true;
    }
    return false;
}
