//
// Created by tompi on 08/10/2026.
//
#include "State.h"
#include <iostream>
#include "Player.h"
#include "easyAI.h"
#include"heuristicAI.h"
state::State::State(std::mutex & mutex): mutex(mutex), board{}, players{} {
    players[0] = std::make_unique<Player>(0,0);
    players[1] = std::make_unique<heuristicAI>(6,6);

}

state::Board& state::State::getBoard(){
    return board;
}

std::array<std::shared_ptr<state::Entity>, 2>& state::State::getPlayers()  {
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


state::State::State(State& other)
    : mutex(other.mutex), board(other.board)
{
    for (int i = 0; i < 2; i++) {
        if (other.players[i]) {
            players[i] = other.players[i]->clone();
        }
    }
}




state::TurnPhase state::State::getPhase () {
    return phase;
}



int state::State::getCurrentPlayer() {
    return currentPlayer;
}

void state::State::advanceTurn () {
    //if the first player is a CPU - we need to do an advance turn immediately


    //Case Human
    if(typeid(*players.at(currentPlayer)) == typeid(Player)) {
        if (phase == INSERT_PIECE) {
            phase = MOVE;
            return;
        }

        if (phase == MOVE) {
            switch (currentPlayer) {
                case(0) : currentPlayer = 1; break;
                case(1) : currentPlayer = 0; break;
            }
            phase = INSERT_PIECE;
            //return; <- If the next turn is for CPUs it will be done immediatly
        }
    }



    //Case CPU
    if(typeid(*players.at(currentPlayer)) != typeid(Player)) {
        std::cout<<currentPlayer<<std::endl;
        std::array<int, 2> mov;
        //INSERT_PIECE
        mov = players.at(currentPlayer)->chooseInsert(*this); //Supposed always true
        this->applyInsertion(mov[0], mov[1]);


        //MOVE
        std::vector<std::array<int, 2>> atteignables = board.searchPath(
            players.at(currentPlayer)->getPosition()[0],
            players.at(currentPlayer)->getPosition()[1]);
        mov = players.at(currentPlayer)->chooseMovement(atteignables,*this); //Supposed always true
        players[currentPlayer]->move(mov[0], mov[1]);
        obtainTreasure(currentPlayer);
        std::cout<<"IA Treasures INDEX: "<< players[currentPlayer]->getTreasureIndex() <<std::endl;

        if(players[currentPlayer]->getTreasureIndex() == 12 &&
            players[currentPlayer]->getStarting_position() == players[currentPlayer]->getPosition()) {
            return; //Avoid 2 consecutives CPU to play despite the first one being the winner
        }
        //Needed : CPU does 2 turns at once
        switch (currentPlayer) {
            case(0) : currentPlayer = 1; break;
            case(1) : currentPlayer = 0; break;
        }
        if (typeid(*players[currentPlayer%2])!=typeid(Player)){//if next player is CPU
            return advanceTurn();
        }
    }



}
/*
void state::State::initPlayingPiece (){
    playing_piece = GREEN_PIECE;
}
void state::State::initPlayingPhase () {
    playing_phase = INSERT_PIECE;
}*/