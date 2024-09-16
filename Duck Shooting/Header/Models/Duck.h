#pragma once
#include <SFML/Graphics.hpp>

class Duck {
public:
    bool alive;
    sf::Sprite sprite;
    sf::Vector2f velocity;
    int points;
    bool explosive;  // Explosive duck

    Duck(sf::Texture& texture, bool isExplosive = false);
    void die();
    void move(float deltaTime);
};
