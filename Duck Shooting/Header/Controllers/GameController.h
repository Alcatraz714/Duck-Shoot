#pragma once
#include "../../Duck Shooting/Header/Models/Player.h"
#include "../../Duck Shooting/Header/Models/Duck.h"
#include "../../Duck Shooting/Header/Views/GameView.h"
#include <vector>
#include <SFML/Graphics.hpp>


class GameController {
private:
    sf::RenderWindow& window;
    Player player;
    std::vector<Duck> ducks;

    GameView gameView;
    sf::Texture duckTexture;

    int wave;               // Tracks the current wave number
    bool gameOver;          // Tracks if the game is over
    float spawnTimer;       // Timer for spawning ducks
    int currentDuckIndex;   // Index of the current duck being spawned

    void loadAssets();      // Loads textures and other assets
    void startNewWave();    // Starts a new wave of ducks
    void checkCollisions(); // Handles shooting logic

public:
    GameController(sf::RenderWindow& win);

    void update(float deltaTime);         // Update game state
    void render();                        // Render the game state
    void handleMouseClick(const sf::Vector2f& position); // Handle mouse input
    bool isGameOver() const;              // Check if the game is over
    int getPlayerScore() const;           // Retrieve the player's score
};
