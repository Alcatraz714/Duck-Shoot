#include "../../Duck Shooting/Header/Models/Duck.h"
#include <cstdlib> // For rand()
#include <ctime>   // For seeding random values

Duck::Duck(sf::Texture& texture, bool isExplosive)
    : explosive(isExplosive), alive(true), points(isExplosive ? 5 : 1) {

    // Set random seed for more varied positions
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    sprite.setTexture(texture);
    sprite.setPosition(rand() % 800, rand() % 600); // Random starting position

    // Ensure a slower velocity
    float speedX = ((rand() % 2 == 0 ? 1 : -1) * (rand() % 30 + 10)); // Reduced speed range for slower movement
    float speedY = ((rand() % 2 == 0 ? 1 : -1) * (rand() % 30 + 10)); // Reduced speed range for slower movement

    velocity = sf::Vector2f(speedX, speedY);

    sprite.setScale(0.3f, 0.3f);  // Adjust sprite size
}

void Duck::die() {
    alive = false;
}

void Duck::move(float deltaTime) {
    sprite.move(velocity * deltaTime);

    // Bounce off the screen edges
    if (sprite.getPosition().x < 0 || sprite.getPosition().x + sprite.getGlobalBounds().width > 800) {
        velocity.x = -velocity.x;
    }
    if (sprite.getPosition().y < 0 || sprite.getPosition().y + sprite.getGlobalBounds().height > 600) {
        velocity.y = -velocity.y;
    }
}
