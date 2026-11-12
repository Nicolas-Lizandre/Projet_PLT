//
// Created by tompi on 16/10/2026.
//

#include "Game.h"
#include "ListCommands.h"
#include <iostream>
#include <array>
#include <vector>
#include <string>

using namespace std;
using namespace state;

client::Game::Game() {
}

void client::Game::run() {
    int PlayerTurn = 0;
    Board &board = state.getBoard();
    board.createPlayground();
    std::array<Player, 2> &players=state.getPlayers();
    players[1].move(6,6);
    string s;
    std::array<int, 2> mov;


    // Collect the current player positions
    auto getPositions = [&players]() {
        vector<array<int, 2>> positions;
        for (auto &player : players) {
            positions.push_back(player.getPosition());
        }
        return positions;
    };

    while (true) {
        cout << "Player" << PlayerTurn <<"'s turn"<<endl;
        board.showBoard({}, getPositions());

        bool temp= true;
        while (temp) {
            cout<<"Do you want to turn the plate? (y/n)";
            cin>>s;
            if (s == "y") {
                board.turnMasterPlate();
            }
            else if (s == "n") {
                temp= false;
            }
        }


        cout<<"insert plate where? (write xy)";
        cin>>s;
        while (s.size() != 2) {
            cout << "Incorrect message length" << endl;
            cout<<"insert plate where? (write xy)";
            cin>>s;
        }
        mov[0] = s[0] - '0';
        mov[1] = s[1] - '0';

        // Update tiles and players together
        if (!state.applyInsertion(mov[0],mov[1])) {
            cout << "Illegal insertion" << endl;
            continue;
        }

        // Read the position after the insertion
        std::array<int, 2> position=players[PlayerTurn].getPosition();
        vector<array<int, 2>> atteignables = board.searchPath(position[0],position[1]);
        board.showBoard(atteignables, getPositions());

        cout << "Cases atteignables depuis   "<<position[0]<<position[1]<<endl;
        for (const auto& c : atteignables) {
            cout << "(" << c[0] << "," << c[1] << ") ";
            cout <<"\n";
        }

        cout<<"move to? (write xy)";
        cin>>s;
        while (s.size() != 2) {
            cout << "Incorrect message length" << endl;
            cout<<"move to? (write xy)";
            cin>>s;
        }
        mov[0] = s[0] - '0';
        mov[1] = s[1] - '0';

        if (state.verifyMovementValidity(mov[0],mov[1],atteignables)) {
            players[PlayerTurn].move(mov[0],mov[1]);
        }
        PlayerTurn = (PlayerTurn+1)%2;
        cout << endl;
    }
}

