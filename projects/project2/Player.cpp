#include <iostream>
#include "Player.hpp"

using std::string;

Player::Player(string name, int budget) {
    this->name = name;
    this->budget = budget;
}

string Player::getName() { 
    return this->name;
}

int Player::getBudget() {
    return this->budget;
}

bool Player::bet(int amount) {
    this->budget -= amount;
    return true;
}

void Player::collectWinnings(int amount) {
    this->budget+= amount;
}
