//
// Created by tompi on 08/10/2026.
//
#include "State.h"
#include <iostream>

state::State::State(): board{}, players{} {

}

state::Board& state::State::getBoard(){
    return board;
}

std::array<state::Player, 2>& state::State::getPlayers()  {
    return players;
}

bool state::State::verifyMovementValidity(int i, int j,std::vector<std::array<int, 2>> legal_moves ) {
    for ( auto& pos : legal_moves) {
        if (pos[0] == i && pos[1] == j) {
            return true;
        }
    }
    return false;
}