//
// Created by tompi on 08/10/2026.
//
#include "Player.h"

#include "State.h"

void state::Player::move(int i, int j) {
    position[0]=i;
    position[1]=j;
}

std::array<int, 2>  state::Player::getPosition () {
    return position;
}

void state::Player::obtainTreasure(State *state) {
    treasure_index+=1;
}

state::Player::Player(int i, int j) {
    position[0]=i;
    position[1]=j;
    starting_position[0]=i;
    starting_position[1]=j;
}