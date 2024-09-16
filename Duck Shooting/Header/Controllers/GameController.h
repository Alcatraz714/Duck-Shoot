#pragma once
#include "../../Duck Shooting/Header/Models/Player.h"
#include "../../Duck Shooting/Header/Models/Duck.h"
#include "../../Duck Shooting/Header/Views/GameView.h"
#include <vector>

class GameController {
private:
    Player player;
    GameView view;
    int wave;
    std::vector<Duck> ducks;
    bool areaBulletActive;  // If area bullet is selected

public:
    GameController();
    void startWave();
    void processShot(sf::Vector2i mousePos);
    bool checkWaveEnd();
    void run();
    void checkExplosion(Duck& explosiveDuck); // Explosive duck behavior
    void handlePowerUp();  // Handle random power-ups
};

