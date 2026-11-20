//
// Created by tompi on 08/10/2026.
//
#include "Player.h"

#include <iostream>
#include <ostream>

#include "State.h"

void state::Player::move(int i, int j) {
    position[0]=i;
    position[1]=j;
}

std::array<int, 2>  state::Player::getPosition () {
    return position;
}

state::Treasure state::Player::getCurrentTreasure() const {
    if (treasure_index >= static_cast<int>(treasure_list.size())) {
        return Treasure::NONE;
    }

    return treasure_list[treasure_index];
}

int state::Player::getTreasureIndex () {
    return treasure_index;
}


void state::Player::setTreasureList(
    const std::array<state::Treasure, 12>& treasures)
{
    treasure_list = treasures;
    treasure_index = 0;
}

void state::Player::advanceTreasure() {
    if (treasure_index < static_cast<int>(treasure_list.size())) {
        ++treasure_index;
    }
}

state::Player::Player(int i, int j) {
    position[0]=i;
    position[1]=j;
    starting_position[0]=i;
    starting_position[1]=j;
}