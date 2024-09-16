#include "../../Duck Shooting/Header/Models/Player.h"

Player::Player() {
    health = 3;
    ammo = 10;
    score = 0;
    areaBullet = 1;  // Only one area bullet available per wave
}

void Player::resetAmmo(int wave) {
    ammo = 10 + wave;  // Increase ammo slightly as waves progress
    areaBullet = 1;    // Reset area bullet availability each wave
}

void Player::loseHealth() {
    health -= 1;
}

void Player::gainHealth() {
    if (health < 5) health += 1;  // Cap health at 5
}
