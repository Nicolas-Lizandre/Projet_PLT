//
// Created by tompi on 21/11/2026.
//
#include "heuristicAI.h"

#include <iostream>
#include <ostream>
#include <random>

using namespace std;

state::heuristicAI::heuristicAI(int i, int j): Entity(i,j) {
    position[0]=i;
    position[1]=j;
    starting_position[0]=i;
    starting_position[1]=j;
}
std::array<int, 2> state::heuristicAI::chooseInsert(State &state) {
    int minDistance = 1000;
    int distance;
    int rotation;
    array<int, 2> insert;
    vector<std::array<int, 2>> legal_inserts = {
        {0, 1}, {0, 3}, {0, 5},
        {6, 1}, {6, 3}, {6, 5},
        {1, 0}, {3, 0}, {5, 0},
        {1, 6}, {3, 6}, {5, 6}
    };
    for ( array<int, 2> potentialinsert : legal_inserts) {
        for (int i=0; i<4; i++) {
            State tempstate = state;
            for (int j = 0; j < i; j++) {
                tempstate.getBoard().turnMasterplate();
            }
            tempstate.applyInsertion(potentialinsert[0],potentialinsert[1]);
            Board &tempboard = tempstate.getBoard();
            array<int, 2> target;
            auto &tempplayers = tempstate.getPlayers();
            if (treasure_index <= treasure_list.size() -1) {
                target = tempboard.findTreasure(treasure_list[treasure_index]);
            }
            else {
                target = tempplayers[state.getCurrentPlayer()]->getStarting_position();
            }
            if (target[0] == -1 && target[1] == -1) {
                continue;
            }
            auto playerposition = tempplayers[state.getCurrentPlayer()]->getPosition();
            vector<array<int, 2>> reachable =tempboard.searchPath(playerposition[0], playerposition[1]);
            for (array<int, 2> pos : reachable) {
                distance = abs(pos[0]-target[0])+abs(pos[1]-target[1]);
                if (distance < minDistance) {
                    cout<<"distance:"<<distance<<"pour l'insert en:"<< potentialinsert[0]<< potentialinsert[1]<<"et mouvement en"<<pos[0]<<pos[1] <<endl;
                    minDistance = distance;
                    bestMovement = pos;
                    rotation = i;
                    insert = potentialinsert;
                }
            }


        }
    }
    Board &board = state.getBoard();
    for (int i=0; i<rotation; i++) {
        board.turnMasterplate();
    }
    cout<< "insert choisi:"<< insert[0]<< " " <<insert[1] << endl;
    return insert;

}

std::array<int, 2> state::heuristicAI::chooseMovement(std::vector<std::array<int, 2> > reachable, State &state) {
    if (bestMovement[0] != position[0] || bestMovement[1] != position[1] ) {
        return bestMovement;
    }
    std::array<int, 2> mov;
    int movenumber;
    std::random_device randomDevice; // seed
    std::mt19937 generator(randomDevice()); //Mersenne Twister
    std::uniform_int_distribution<int> distribution(0,reachable.size()-1);
    movenumber = distribution(generator);
    mov =reachable[movenumber];
    return mov;
}

std::unique_ptr<state::Entity> state::heuristicAI::clone() {
    return std::make_unique<heuristicAI>(*this);
}
