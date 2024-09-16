#include "../../Duck Shooting/Header/Views/GameView.h"
#include <iostream>

GameView::GameView() {
    // Load font for displaying text
    font.loadFromFile("assets/OpenSans.ttf");
    playerText.setFont(font);
    playerText.setCharacterSize(24);
    playerText.setFillColor(sf::Color::White);

    // Load textures and sounds
    loadAssets();

    // Set up the crosshair sprite
    crosshair.setTexture(crosshairTexture);
    crosshair.setScale(0.05f, 0.05f); // Scale down the crosshair

    // Set up the background rectangle (dynamic color based on wave)
    background.setSize(sf::Vector2f(800, 600));

    // Start background music
    backgroundMusic.setLoop(true);
    backgroundMusic.play();
}

void GameView::loadAssets() {
    // Load duck sprite texture
    duckTexture.loadFromFile("assets/duck.png");

    // Load crosshair texture
    crosshairTexture.loadFromFile("assets/crosshair.png");

    // Load gunshot and quack sounds
    shotBuffer.loadFromFile("assets/gunshot.wav");
    quackBuffer.loadFromFile("assets/quack.wav");

    gunshot.setBuffer(shotBuffer);
    quack.setBuffer(quackBuffer);

    // Load background music
    backgroundMusic.openFromFile("assets/background_music.ogg");
}

void GameView::display(sf::RenderWindow& window, const Player& player, const std::vector<Duck>& ducks) {
    window.clear();

    // Draw background
    window.draw(background);

    // Display player stats
    playerText.setString("Health: " + std::to_string(player.health) +
        " Ammo: " + std::to_string(player.ammo) +
        " Score: " + std::to_string(player.score));
    window.draw(playerText);

    // Draw ducks
    for (const auto& duck : ducks) {
        if (duck.alive) {
            window.draw(duck.sprite);
        }
    }

    // Draw the crosshair at the current mouse position
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    crosshair.setPosition(mousePos.x - crosshair.getGlobalBounds().width / 2, mousePos.y - crosshair.getGlobalBounds().height / 2);
    window.draw(crosshair);

    window.display();
}

void GameView::gameOver(sf::RenderWindow& window, const Player& player) {
    window.clear();
    playerText.setString("Game Over! Final Score: " + std::to_string(player.score));
    window.draw(playerText);
    window.display();
}

void GameView::updateBackground(int wave) {
    // Make the background darker as waves progress
    int colorValue = 255 - wave * 10;
    background.setFillColor(sf::Color(colorValue, colorValue, colorValue));
}
