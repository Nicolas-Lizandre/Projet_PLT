//
// Created by tompi on 08/10/2026.
//
#include "Player.h"


state::Player::Player(int i, int j): Entity(i,j) {
    position[0]=i;
    position[1]=j;
    starting_position[0]=i;
    starting_position[1]=j;
}

std::array<int, 2> state::Player::chooseInsert() {
    return std::array<int, 2>{0,1};
}

std::array<int, 2> state::Player::chooseMovement(std::vector<std::array<int, 2> > reachable) {
    return std::array<int, 2>{0,1};
}
