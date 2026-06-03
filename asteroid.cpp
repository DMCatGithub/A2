#include <asteroid.h>
#include <algorithm>

float K = 2500;
float damping = 0.8;

// Create a random asteroid
void randomAsteroid(std::vector<Asteroid> &asteroids, Texture spritesheet, float radius) {
    // Create a random Asteroid
    Asteroid asteroid;

    asteroid.mass = 100;
    asteroid.force = Vec2::zero;

    asteroid.texture = subTexture(spritesheet, {480, 0, 240, 240});

    asteroid.transform.localPosition = Vec2(uniform(0, WINDOW_WIDTH), uniform(0, WINDOW_HEIGHT));
    asteroid.transform.localAngle = uniform(0, 360);

    asteroid.vel = Vec2(uniform(-200, 200), uniform(-200, 200));
    asteroid.radius = radius;
    asteroid.size = Vec2(asteroid.radius*2.35, asteroid.radius*2.35);

    asteroid.angularVel = uniform(-90, 90);

    asteroid.active = true;

    // Add to list
    asteroids.push_back(asteroid);
}

// Break an asteroid into two pieces
void breakAsteroid(std::vector<Asteroid> &asteroids, Asteroid asteroid) {
    if(asteroid.radius < 25) {
        if(asteroids.size() < 3) {
            randomAsteroid(asteroids, asteroid.texture, 60);
        }
        return;
    }

    // Create a random Asteroid
    Asteroid a, b;

    a.texture = asteroid.texture;
    b.texture = asteroid.texture;
    a.radius = asteroid.radius * 0.8;
    b.radius = asteroid.radius * 0.8;
    a.mass = asteroid.mass * 0.5;
    b.mass = asteroid.mass * 0.5;

    a.force = Vec2::zero;
    b.force = Vec2::zero;


    Vec2 axis = unit(Vec2(uniform(-1, 1), uniform(-1, 1)));

    a.transform.localPosition = asteroid.transform.position() + axis * a.radius;
    b.transform.localPosition = asteroid.transform.position() - axis * b.radius;

    a.transform.localAngle = uniform(0, 360);
    b.transform.localAngle = uniform(0, 360);

    float rVel = uniform(50, 100);

    a.vel = asteroid.vel + axis * rVel;
    b.vel = asteroid.vel - axis * rVel;
    
    a.size = Vec2(a.radius*2.35, a.radius*2.35);
    b.size = Vec2(b.radius*2.35, b.radius*2.35);

    a.angularVel = uniform(-90, 90);
    b.angularVel = uniform(-90, 90);

    a.active = true;
    b.active = true;

    // Add to list
    asteroids.push_back(a);
    asteroids.push_back(b);
}

// Test and perform (force) collision
void asteroidCollision(Asteroid &b1, Asteroid &b2) {
    // Get position
    Vec2 p1 = b1.transform.position();
    Vec2 p2 = b2.transform.position();

    // Check if the asteroids are near the border of the window and adjust if necessary
    if(p1.x <= b1.radius+b2.radius && p2.x >= WINDOW_WIDTH-b2.radius-b1.radius) {
        p1.x += WINDOW_WIDTH;
    }
    if(p2.x <= b1.radius+b2.radius && p1.x >= WINDOW_WIDTH-b2.radius-b1.radius) {
        p2.x += WINDOW_WIDTH;
    }
    if(p1.y <= b1.radius+b2.radius && p2.y >= WINDOW_HEIGHT-b2.radius-b1.radius) {
        p1.y += WINDOW_HEIGHT;
    }
    if(p2.y <= b1.radius+b2.radius && p1.y >= WINDOW_HEIGHT-b2.radius-b1.radius) {
        p2.y += WINDOW_HEIGHT;
    }

    // Get Distance Squared
    float distanceSq = pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2);

    // Check for collisions
    if(distanceSq < pow((b1.radius + b2.radius), 2) && distanceSq > 0) {
        // Calculate Penetration Depth
        float d = ((b1.radius + b2.radius) - sqrt(distanceSq));

        Vec2 u1 = unit(p2 - p1);
        Vec2 u2 = unit(p1 - p2);

        // Average velocity
        Vec2 vavg = (b1.vel + b2.vel) * 0.5;

        // Relative Velocities
        Vec2 v1r = b1.vel - vavg;
        Vec2 v2r = b2.vel - vavg;

        // Apply forces
        b1.force += u1 * (-K * d) - u1 * dot(v1r, u1) * damping * 2.0 * sqrt(K*b1.mass);
        b2.force += u2 * (-K * d) - u2 * dot(v2r, u2) * damping * 2.0 * sqrt(K*b2.mass);
    }
}

// Update an Asteroid
void updateAsteroid(Asteroid &asteroid, float dt) {
    // Move Asteroid
    asteroid.transform.localPosition += asteroid.vel * dt;
    asteroid.transform.localAngle += asteroid.angularVel * dt;
    asteroid.vel += asteroid.force / asteroid.mass * dt;
    asteroid.force = Vec2::zero;

    // Periodic Bounaries
    if(asteroid.transform.position().x < 0) asteroid.transform.localPosition.x += WINDOW_WIDTH;
    if(asteroid.transform.position().x > WINDOW_WIDTH) asteroid.transform.localPosition.x -= WINDOW_WIDTH;
    if(asteroid.transform.position().y < 0) asteroid.transform.localPosition.y += WINDOW_HEIGHT;
    if(asteroid.transform.position().y > WINDOW_HEIGHT) asteroid.transform.localPosition.y -= WINDOW_HEIGHT;
}

// Draw Asteroid
void drawAsteroid(Asteroid &asteroid) {
    // If Asteroid is active
    if(asteroid.active) {
        // Asteroid position
        Vec2 pos = asteroid.transform.position();

        // Draw Texture and Hitbox
        drawTexture(asteroid.texture, asteroid.transform.position() - asteroid.size/2, asteroid.size, asteroid.transform.angle());

        bool xCond = pos.x < asteroid.radius || pos.x > WINDOW_WIDTH-asteroid.radius;
        bool yCond = pos.y < asteroid.radius || pos.y > WINDOW_HEIGHT-asteroid.radius;
        int xOffset = (pos.x < asteroid.radius) ? WINDOW_WIDTH : -WINDOW_WIDTH;
        int yOffset = (pos.y < asteroid.radius) ? WINDOW_HEIGHT : -WINDOW_HEIGHT;

        if(xCond) {
            // Draw Asteroid offset in X
            Vec2 posOffset = pos + Vec2(xOffset, 0);
            drawTexture(asteroid.texture, posOffset - asteroid.size/2, asteroid.size, asteroid.transform.angle());
        }
        if(yCond) {
            // Draw Asteroid offset in Y
            Vec2 posOffset = pos + Vec2(0, yOffset);
            drawTexture(asteroid.texture, posOffset - asteroid.size/2, asteroid.size, asteroid.transform.angle());
        }
        if(xCond && yCond) {
            // Draw Asteroid offset in X and Y
            Vec2 posOffset = pos + Vec2(xOffset, yOffset);
            drawTexture(asteroid.texture, posOffset - asteroid.size/2, asteroid.size, asteroid.transform.angle());
        }
    }
}