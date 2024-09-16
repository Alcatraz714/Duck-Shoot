#include "../../Duck Shooting/Header/Views/GameView.h"
#include <iostream>

GameView::GameView(sf::RenderWindow& win, Player& playerRef, std::vector<Duck>& duckList)
    : window(win), player(playerRef), ducks(duckList) {
    loadAssets();

    // Set up UI text elements
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);

    ammoText.setFont(font);
    ammoText.setCharacterSize(24);
    ammoText.setFillColor(sf::Color::White);
}

void GameView::loadAssets() {
    // Load font
    if (!font.loadFromFile("assets/OpenSans.ttf")) {
        std::cerr << "Error: Could not load font from 'assets/arial.ttf'!" << std::endl;
    }

    // Set up background texture (for future use if you add a background)
    if (!backgroundTexture.loadFromFile("assets/background.png")) {
        std::cerr << "Error: Could not load background texture from 'assets/background.png'!" << std::endl;
    }

    backgroundSprite.setTexture(backgroundTexture);
}

void GameView::updateUI() {
    // Update score and ammo display
    scoreText.setString("Score: " + std::to_string(player.getScore()));
    ammoText.setString("Ammo: " + std::to_string(player.getAmmo()));

    // Position UI elements
    scoreText.setPosition(10, 10);
    ammoText.setPosition(10, 40);
}

void GameView::render() {
    window.clear(sf::Color::Black); // Set black background

    // Draw ducks
    for (const auto& duck : ducks) {
        if (duck.isAlive()) {
            window.draw(duck.sprite);
        }
    }

    // Draw UI elements
    window.draw(scoreText);
    window.draw(ammoText);

    window.display();
}
