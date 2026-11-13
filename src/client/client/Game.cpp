//
// Created by tompi on 16/10/2026.
//

#include "Game.h"
#include <iostream>
#include <array>
#include <vector>
#include <string>

using namespace std;
using namespace state;


client::Game::Game() : state(state::State(mutex)) {
}

void client::Game::run() {

    Board &board = state.getBoard();
    board.createPlayground();
    std::array<Player, 2> &players=state.getPlayers();
    string s;
    std::array<int, 2> mov;

    // Collect the current player positions
    auto getPositions = [&players]() {
        vector<array<int, 2>> positions;
        //for (auto &player : players) {
        //    positions.push_back(player.getPosition());
        //}
        positions.push_back(players[0].getPosition());
        return positions;
    };

    while (true) {
        board.showBoard({}, getPositions());

        cout<<"insert piece where? (write (x,y))";
        cin>>s;
        mov[0] = s[1] - '0';
        mov[1] = s[3] - '0';

        // Update tiles and players together
        if (!state.applyInsertion(mov[0],mov[1])) {
            cout << "Illegal insertion" << endl;
            continue;
        }

        // Read the position after the insertion
        std::array<int, 2> position=players[0].getPosition();
        vector<array<int, 2>> atteignables = board.searchPath(position[0],position[1]);
        board.showBoard(atteignables, getPositions());

        cout << "Cases atteignables depuis   "<<position[0]<<position[1]<<endl;
        for (const auto& c : atteignables) {
            cout << "(" << c[0] << "," << c[1] << ") ";
            cout <<"\n";
        }

        cout<<"move to? (write (x,y))";
        cin>>s;
        mov[0] = s[1] - '0';
        mov[1] = s[3] - '0';

        if (state.verifyMovementValidity(mov[0],mov[1],atteignables)) {
            players[0].move(mov[0],mov[1]);
        }

        cout << endl;
    }
}

