#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../../Duck Shooting/Header/Models/Player.h"
#include "../../Duck Shooting/Header/Models/Duck.h"
#include <vector>

class GameView {
public:
    sf::Font font;
    sf::Text playerText;
    sf::Sprite crosshair;
    sf::Texture crosshairTexture;
    sf::Texture duckTexture;
    sf::Music backgroundMusic;
    sf::SoundBuffer shotBuffer, quackBuffer;
    sf::Sound gunshot, quack;
    sf::RectangleShape background;
    GameView();
    void display(sf::RenderWindow& window, const Player& player, const std::vector<Duck>& ducks);
    void gameOver(sf::RenderWindow& window, const Player& player);
    void loadAssets(); // Load textures, sounds, and music
    void updateBackground(int wave);
};
