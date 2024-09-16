#include "../../Duck Shooting/Header/Models/Duck.h"
#include <cstdlib> // For rand()
#include <ctime>   // For random seed
#include <cstdlib>

Duck::Duck(sf::Texture& texture, bool isExplosive)
    : explosive(isExplosive), alive(true), points(isExplosive ? 5 : 1), movementTimer(0.0f) {
    sprite.setTexture(texture);
    sprite.setPosition(0, 600); // Start from the bottom-left corner
    velocity = sf::Vector2f(50, -100); // Start moving up
    sprite.setScale(0.3f, 0.3f);  // Adjust sprite size
}

void Duck::die() {
    alive = false;
}

void Duck::move(float deltaTime) {
    movementTimer += deltaTime;

    // Define the different movement stages: up, across, down
    if (sprite.getPosition().y <= 100 && velocity.y < 0) {
        // Reached near the top, move to the right and down
        velocity.x = 200;
        velocity.y = 200;
    }

    sprite.move(velocity * deltaTime);

    // Remove duck if it goes beyond the right boundary
    if (sprite.getPosition().x > 800 || sprite.getPosition().y > 600) {
        alive = false; // The duck has completed its path and will be removed
    }
}


