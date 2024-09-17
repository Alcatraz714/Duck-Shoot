#pragma once
#include <SFML/Graphics.hpp>

class Duck {
public:
    bool alive;
    sf::Sprite sprite;
    sf::Vector2f velocity;
    int points;
    bool explosive;

    Duck(sf::Texture& texture, bool isExplosive = false);
    void die();
    void move(float deltaTime);

    bool isAlive() const { return alive; }
    sf::FloatRect getBounds() const { return sprite.getGlobalBounds(); }

private:
    float movementTimer;
};
