#include "../../Duck Shooting/Header/Models/Duck.h"
#include <cstdlib> // For rand()
#include <ctime>   // For random seed

Duck::Duck(sf::Texture& texture, bool isExplosive)
    : explosive(isExplosive), alive(true), points(isExplosive ? 5 : 1), movementTimer(0.0f) {
    /*sprite.setTexture(texture);
    sprite.setPosition(0, 600); // Start from the bottom-left corner
    velocity = sf::Vector2f(300, -300); // Start moving up was (50, -100)
    sprite.setScale(0.5f, 0.5f);  // Adjust sprite size */
    
    // Seed the random number generator
    static bool seeded = false;
    if (!seeded) {
        std::srand(static_cast<unsigned>(std::time(0)));
        seeded = true;
    }

    // Set texture and scale
    sprite.setTexture(texture);
    sprite.setScale(0.5f, 0.5f);  // Adjust sprite size

    // Randomize starting position along the bottom of the screen
    float startX = static_cast<float>(std::rand() % 800);  // Random X position between 0 and 800
    sprite.setPosition(startX, 600); // Start from the bottom

    // Set random movement pattern
    setRandomPattern();
    updateVelocityForPattern();
}

void Duck::die() {
    alive = false;
}

void Duck::move(float deltaTime) {
    movementTimer += deltaTime;

    /* Define the different movement stages : up, across, down
    if (sprite.getPosition().y <= 100 && velocity.y < 0) {
        // Reached near the top, move to the right and down
        velocity.x = 400;
        velocity.y = 400;
    }*/

    // Change velocity periodically based on the pattern
    if (movementTimer > 2.0f) { // Adjust path change interval as needed
        updateVelocityForPattern();
        movementTimer = 0.0f; // Reset timer
    }

    sprite.move(velocity * deltaTime);

    // Remove duck if it goes beyond the right boundary
    if (sprite.getPosition().x > 800 || sprite.getPosition().y > 600) {
        alive = false; // The duck has completed its path and will be removed
    }
}

void Duck::setRandomPattern() {
    int patternValue = std::rand() % 4;
    pattern = static_cast<PathPattern>(patternValue);
}

void Duck::updateVelocityForPattern() {
    switch (pattern) {
    case PathPattern::STRAIGHT_UP:
        velocity = sf::Vector2f(0, -300); // Move straight up
        break;
    case PathPattern::TOP_LEFT:
        velocity = sf::Vector2f(-300, -300); // Move diagonally to top-left
        break;
    case PathPattern::TOP_RIGHT:
        velocity = sf::Vector2f(300, -300); // Move diagonally to top-right
        break;
    case PathPattern::CUSTOM:
        // Custom pattern with randomized speed and direction
        float speedX = static_cast<float>(std::rand() % 200 + 100); // Random speed between 100 and 300
        float speedY = static_cast<float>(std::rand() % 200 + 100); // Random speed between 100 and 300
        velocity = sf::Vector2f((std::rand() % 2 == 0 ? 1 : -1) * speedX, (std::rand() % 2 == 0 ? 1 : -1) * speedY);
        break;
    }
}

sf::FloatRect Duck::getBounds() const {
    return sprite.getGlobalBounds(); // Return the global bounds of the sprite
}