#pragma once
#include "../../Duck Shooting/Header/Models/Player.h"
#include "../../Duck Shooting/Header/Models/Duck.h"
#include "../../Duck Shooting/Header/Views/GameView.h"
#include <vector>
#include <SFML/Graphics.hpp>

class GameController {
public:
    GameController(sf::RenderWindow& window);

    void update(float deltaTime);
    void render();
    void handleMouseClick(const sf::Vector2f& position);
    bool isGameOver() const;
    int getPlayerScore() const { return player.getScore(); }

private:
    sf::RenderWindow& window;
    std::vector<Duck> ducks;
    Player player;
    GameView gameView;
    sf::Texture duckTexture;
    int wave;
    bool gameOver;

    void loadAssets();
    void startNewWave();
    void checkCollisions();
};
