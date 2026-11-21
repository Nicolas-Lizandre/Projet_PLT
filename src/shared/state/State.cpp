//
// Created by tompi on 08/10/2026.
//
#include "State.h"
#include <iostream>

state::State::State(std::mutex & mutex): mutex(mutex), board{}, players{} {

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

bool state::State::obtainTreasure(int playerIndex) {
    if (playerIndex < 0 ||
        playerIndex >= static_cast<int>(players.size())) {
        return false;
    }

    Player &player = players[playerIndex];
    std::array<int, 2> position = player.getPosition();

    if (!board.hasTreasureAt(position[0], position[1],
                            player.getCurrentTreasure())) {
        return false;
    }

    player.advanceTreasure();
    return true;
}




state::TurnPhase state::State::getPlayingPhase () {
    return playing_phase;
}

int state::State::getPlayingPiecePlayerID () {
    switch (playing_piece) {
        case(GREEN_PIECE) : return 0;
        case(RED_PIECE) : return 1;
    }
    return 0;
}

state::Piece state::State::getPlayingPiece () {
    return playing_piece;
}
void state::State::advanceTurn () {
    std::cout << "hello" << std::endl;
    std::cout << playing_piece << std::endl;
    std::cout << playing_phase << std::endl;

    if (playing_phase == INSERT_PIECE) {
        playing_phase = MOVE;
        return;
    }

    if (playing_phase == MOVE) {
        switch (playing_piece) {
            case(GREEN_PIECE) : playing_piece = RED_PIECE; break;
            case(RED_PIECE) : playing_piece = GREEN_PIECE; break;
        }
        playing_phase = INSERT_PIECE;
        return;
    }

}
/*
void state::State::initPlayingPiece (){
    playing_piece = GREEN_PIECE;
}
void state::State::initPlayingPhase () {
    playing_phase = INSERT_PIECE;
}*/