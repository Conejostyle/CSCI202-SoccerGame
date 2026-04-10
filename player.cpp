#include "player.h"
//getters
std::string Player::getName() const {
    return name;
}
std::string Player::getPosition() const {
    return position;
}
int Player::getDefendingStat() const {
    return defendingStat;
}
int Player::getPassingStat() const {
    return passingStat;
}
int Player::getShootingStat() const {
    return shootingStat;
}
int Player::getDribblingStat() const {
    return dribblingStat;
}

//setters
void Player::setName(const std::string& playerName) {
    name = playerName;
}
void Player::setPosition(const std::string& playerPosition) {
    position = playerPosition;
}
void Player::setDefendingStat(int stat) {
    defendingStat = stat;
}
void Player::setPassingStat(int stat) {
    passingStat = stat;
}
void Player::setShootingStat(int stat) {
    shootingStat = stat;
}
void Player::setDribblingStat(int stat) {
    dribblingStat = stat;
}
