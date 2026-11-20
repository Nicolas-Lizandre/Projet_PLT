//
// Created by tompi on 08/10/2026.
//
#include "State.h"
#include <iostream>
#include "Player.h"
#include "easyAI.h"
state::State::State(std::mutex & mutex): mutex(mutex), board{}, players{} {
    players[0] = std::make_unique<Player>(0,0);
    players[1] = std::make_unique<easyAI>(6,6);

}

state::Board& state::State::getBoard(){
    return board;
}

std::array<std::unique_ptr<state::Entity>, 2>& state::State::getPlayers()  {
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
        std::array<int, 2> p = player->getPosition();

        if (i == 0 || i == 6) {
            // Shift players on column j
            if (p[1] == j) {
                player->move(
                    (p[0] + (i == 0 ? 1 : 6)) % 7,
                    j
                );
            }
        } else {
            // Shift players on row i
            if (p[0] == i) {
                player->move(
                    i,
                    (p[1] + (j == 0 ? 1 : 6)) % 7
                );
            }
        }
    }
}

bool state::State::obtainTreasure(int playerIndex) {
    if (playerIndex < 0 ||
        playerIndex >= static_cast<int>(players.size())) {
        return false;
    }

    Entity &player = *players[playerIndex];
    std::array<int, 2> position = player.getPosition();

    if (!board.hasTreasureAt(position[0], position[1],
                            player.getCurrentTreasure())) {
        return false;
    }

    player.advanceTreasure();
    return true;
}