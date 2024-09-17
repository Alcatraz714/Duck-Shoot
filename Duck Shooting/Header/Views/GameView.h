#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../../Duck Shooting/Header/Models/Player.h"
#include "../../Duck Shooting/Header/Models/Duck.h"
#include <vector>

class GameView {
public:
    GameView(sf::RenderWindow& window, Player& player, std::vector<Duck>& ducks);

    void render(bool gameOver);
    void updateUI();
    void loadAssets();

private:
    sf::RenderWindow& window;
    Player& player;
    std::vector<Duck>& ducks;
    sf::Font font;
    sf::Text scoreText;
    sf::Text ammoText;
    sf::Text gameOverText;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
};
