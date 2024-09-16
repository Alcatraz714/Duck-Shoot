#pragma once
#include <SFML/Graphics.hpp>

class Player {
public:
    Player();

    void shoot();
    void increaseScore(int amount);
    int getScore() const { return score; }
    int getAmmo() const { return ammo; }
    bool hasAmmo() const { return ammo > 0; }

private:
    int score;
    int ammo;
};

