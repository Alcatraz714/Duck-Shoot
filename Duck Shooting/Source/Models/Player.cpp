#include "../../Duck Shooting/Header/Models/Player.h"

Player::Player() : score(0), ammo(5) {}

void Player::shoot() {
    if (ammo > 0) {
        --ammo;
    }
}

void Player::increaseScore(int amount) {
    score += amount;
}
