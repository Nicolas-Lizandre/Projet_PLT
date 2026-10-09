//
// Created by tompi on 08/10/2026.
//
#include "Player.h"

#include "State.h"

void state::Player::move(int i, int j) {
    position[0]=i;
    position[1]=j;
}

void state::Player::obtainTreasure(State *state) {
    treasure_index+=1;
}
