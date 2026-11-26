//
// Created by tompi on 20/11/2026.
//
#include "easyAI.h"
#include <random>

state::easyAI::easyAI(int i, int j): Entity(i,j) {
    position[0]=i;
    position[1]=j;
    starting_position[0]=i;
    starting_position[1]=j;
}
std::array<int, 2> state::easyAI::chooseInsert(State &state) {
    auto &board = state.getBoard();
    std::random_device randomDevice; // seed
    std::mt19937 generator(randomDevice()); //Mersenne Twister
    std::array<int, 2> insert;
    int insertnumber;
    int rotation = 0;

    int legal_inserts[12][2] = {
        {0, 1}, {0, 3}, {0, 5},
        {6, 1}, {6, 3}, {6, 5},
        {1, 0}, {3, 0}, {5, 0},
        {1, 6}, {3, 6}, {5, 6}
    };

    std::uniform_int_distribution<int> rotationDistribution(0, 3); // uniform distribution for rotation
    rotation = rotationDistribution(generator);
    for (int i = 0; i < rotation; i++) {
        board.turnMasterplate();
    }
    std::uniform_int_distribution<int> distribution(0,11);
    insertnumber = distribution(generator);
    insert[0] = legal_inserts[insertnumber][0];
    insert[1] = legal_inserts[insertnumber][1];
    return insert;
}

std::array<int, 2> state::easyAI::chooseMovement(std::vector<std::array<int, 2> > reachable, State &state) {
    auto &board = state.getBoard();
    std::array<int, 2> mov;
    int movenumber;
    const auto &playground = std::move(board.getPlayground());
    for (std::array<int, 2> reach : reachable) {
        if (playground[reach[0]][reach[1]]->hasTreasure(treasure_list[treasure_index]) ) {
            return reach;
        }
    }

    std::random_device randomDevice; // seed
    std::mt19937 generator(randomDevice()); //Mersenne Twister
    std::uniform_int_distribution<int> distribution(0,reachable.size()-1);
    movenumber = distribution(generator);
    mov =reachable[movenumber];
    return mov;
}

std::unique_ptr<state::Entity> state::easyAI::clone() {
    return std::make_unique<easyAI>(*this);
}
