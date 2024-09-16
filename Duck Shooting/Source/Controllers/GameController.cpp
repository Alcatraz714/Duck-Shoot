#include "../../Duck Shooting/Header/Controllers/GameController.h"
#include <iostream>

GameController::GameController(sf::RenderWindow& win)
    : window(win), player(), gameView(win, player, ducks), wave(1), gameOver(false) {
    loadAssets();
    startNewWave();
}

void GameController::loadAssets() {
    if (!duckTexture.loadFromFile("assets/duck.png")) {
        std::cerr << "Error: Could not load duck texture from 'assets/duck.png'!" << std::endl;
    }
}

void GameController::startNewWave() {
    ducks.clear();
    int numDucks = wave + 2;  // Increase number of ducks with each wave
    for (int i = 0; i < numDucks; ++i) {
        ducks.emplace_back(duckTexture);
    }
}

void GameController::update(float deltaTime) {
    if (isGameOver()) return;

    for (auto& duck : ducks) {
        duck.move(deltaTime);
    }

    checkCollisions();
    gameView.updateUI();

    // If all ducks are dead, start a new wave
    if (std::all_of(ducks.begin(), ducks.end(), [](const Duck& d) { return !d.isAlive(); })) {
        ++wave;
        startNewWave();
    }

    // If player runs out of ammo and ducks are still alive, game over
    if (!player.hasAmmo() && std::any_of(ducks.begin(), ducks.end(), [](const Duck& d) { return d.isAlive(); })) {
        gameOver = true;
    }
}

void GameController::render() {
    gameView.render();
}

void GameController::handleMouseClick(const sf::Vector2f& position) {
    if (!player.hasAmmo()) return;

    player.shoot();

    for (auto& duck : ducks) {
        if (duck.isAlive() && duck.getBounds().contains(position)) {
            duck.die();
            player.increaseScore(10);
            return;
        }
    }
}

void GameController::checkCollisions() {
    // Handle future collisions if needed
}

bool GameController::isGameOver() const {
    return gameOver;
}
