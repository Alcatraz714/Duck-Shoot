#include "../../Duck Shooting/Header/Controllers/GameController.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>

GameController::GameController() : wave(1), areaBulletActive(false) {}

void GameController::startWave() {
    ducks.clear();
    for (int i = 0; i < wave * 2; ++i) {
        ducks.emplace_back(view.duckTexture, rand() % 5 == 0);  // 20% chance of explosive duck
    }
    player.resetAmmo(wave);
    view.updateBackground(wave);
}

void GameController::processShot(sf::Vector2i mousePos) {
    if (player.ammo <= 0) return;
    player.ammo--;

    // Check for area bullet usage
    if (areaBulletActive && player.areaBullet > 0) {
        player.areaBullet--;
        for (auto& duck : ducks) {
            float dist = std::sqrt(std::pow(duck.sprite.getPosition().x - mousePos.x, 2) +
                std::pow(duck.sprite.getPosition().y - mousePos.y, 2));
            if (dist < 50 && duck.alive) {  // 50-pixel radius for area bullet
                duck.die();
                player.score += duck.points;
                if (duck.explosive) checkExplosion(duck);
            }
        }
        view.gunshot.play();
    }
    else {
        for (auto& duck : ducks) {
            if (duck.sprite.getGlobalBounds().contains(mousePos.x, mousePos.y) && duck.alive) {
                duck.die();
                player.score += duck.points;
                view.quack.play();
                if (duck.explosive) checkExplosion(duck);
                break;
            }
        }
    }
}

bool GameController::checkWaveEnd() {
    for (const auto& duck : ducks) {
        if (duck.alive) return false;
    }
    return true;
}

void GameController::run() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Duck Hunt");

    view.loadAssets();
    startWave();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();

            // Left-click for point and click bullet
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                processShot(sf::Mouse::getPosition(window));
            }

            // Right-click for area bullet
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {
                areaBulletActive = true;
                processShot(sf::Mouse::getPosition(window));
                areaBulletActive = false;
            }
        }

        view.display(window, player, ducks);

        if (checkWaveEnd()) {
            ++wave;
            startWave();
        }

        if (player.health <= 0) {
            view.gameOver(window, player);
            window.close();
        }
    }
}

void GameController::checkExplosion(Duck& explosiveDuck) {
    for (auto& duck : ducks) {
        float dist = std::sqrt(std::pow(duck.sprite.getPosition().x - explosiveDuck.sprite.getPosition().x, 2) +
            std::pow(duck.sprite.getPosition().y - explosiveDuck.sprite.getPosition().y, 2));
        if (dist < 100 && duck.alive) {  // 100-pixel radius explosion
            duck.die();
            player.score += duck.points;
        }
    }
}

void GameController::handlePowerUp() {
    if (rand() % 10 == 0) {  // 10% chance of power-up
        player.gainHealth();
    }
}
