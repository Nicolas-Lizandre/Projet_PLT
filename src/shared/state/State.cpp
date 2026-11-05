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

bool state::State::applyInsertion(int i, int j) {
    // Insert the plate before moving the players
    if (!board.insertPlate(i, j)) {
        return false;
    }

    movePlayers(i, j);
    return true;
}

void state::State::movePlayers(int i, int j) {
    for (auto &player : players) {
        std::array<int, 2> p = player.getPosition();

        if (i == 0 || i == 6) {
            // Shift players on column j
            if (p[1] == j) {
                player.move(
                    (p[0] + (i == 0 ? 1 : 6)) % 7,
                    j
                );
            }
        } else {
            // Shift players on row i
            if (p[0] == i) {
                player.move(
                    i,
                    (p[1] + (j == 0 ? 1 : 6)) % 7
                );
            }
        }
    }
}