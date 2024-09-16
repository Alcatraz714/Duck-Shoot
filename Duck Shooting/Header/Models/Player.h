#pragma once

class Player {
public:
    int health;
    int ammo;
    int score;
    int areaBullet; // Number of area bullets available

    Player();
    void resetAmmo(int wave);
    void loseHealth();
    void gainHealth(); // Power-up to gain health
};
