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
    bool isAlive() const { return alive; }
    const sf::Sprite& getSprite() const { return sprite; }
    sf::FloatRect getBounds() const;  // Add this line

private:
    enum class PathPattern {
        STRAIGHT_UP,
        TOP_LEFT,
        TOP_RIGHT,
        CUSTOM
    };

    PathPattern pattern;
    float movementTimer;

    void setRandomPattern();
    void updateVelocityForPattern();
};