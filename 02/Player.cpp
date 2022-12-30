//
// Created by Mali Abramovitch on 02/12/2022.
//

#include "Player.h"

Player::Player(char colorr, int scoree) : color(colorr), score(scoree) {}

void Player::operator++() {
    ++score;
}

void Player::operator--() {
    --score;
}



