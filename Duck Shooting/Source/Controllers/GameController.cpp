#include "../../Duck Shooting/Header/Controllers/GameController.h"
#include <iostream>


GameController::GameController(sf::RenderWindow& win)
    : window(win), player(), gameView(win, player, ducks), wave(1), gameOver(false), spawnTimer(0.0f), currentDuckIndex(0) {
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
    int numDucks = wave;  // Number of ducks in the current wave
    for (int i = 0; i < numDucks; ++i) {
        ducks.emplace_back(duckTexture);
    }
    currentDuckIndex = 0; // Reset to the first duck
    spawnTimer = 0.0f;    // Reset spawn timer
}

void GameController::update(float deltaTime) {
    if (isGameOver()) return;

    spawnTimer += deltaTime;

    // Introduce ducks one by one based on the spawn timer
    if (currentDuckIndex < ducks.size() && spawnTimer > 1.5f) {  // Delay of 1.5 seconds between ducks
        spawnTimer = 0.0f;
        currentDuckIndex++;
    }

    // Move the currently spawned ducks
    for (int i = 0; i < currentDuckIndex; ++i) {
        if (ducks[i].isAlive()) {
            ducks[i].move(deltaTime);
        }
    }

    checkCollisions();
    gameView.updateUI();

    // If all ducks are dead, start a new wave
    if (std::all_of(ducks.begin(), ducks.end(), [](const Duck& d) { return !d.isAlive(); })) {
        ++wave;
        startNewWave();
    }

    // End game when player runs out of ammo and ducks are alive
    if (!player.hasAmmo() && std::any_of(ducks.begin(), ducks.end(), [](const Duck& d) { return d.isAlive(); })) {
        gameOver = true;
    }
}

void GameController::render() {
    gameView.render(gameOver);
}

void GameController::handleMouseClick(const sf::Vector2f& position) {
    if (!player.hasAmmo()) return;

    player.shoot();

    for (auto& duck : ducks) {
        if (duck.isAlive() && duck.getBounds().contains(position)) {
            duck.die();
            player.increaseScore(10);
            player.increaseAmmo(2);  // Add 2 bullets after each kill
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

int GameController::getPlayerScore() const {
    return player.getScore();
}
