//
// Created by tompi on 16/10/2026.
//

#include "Game.h"
#include "ListCommands.h"
#include <iostream>
using namespace std;
using namespace state;


client::Game::Game() {
}

void client::Game::run() {
    Board &board = state.getBoard();
    board.createPlayground();
    std::array<Player, 2> &players=state.getPlayers();
    string s;
    std::array<int, 2> mov;
    while (true) {
        board.showBoard();
        std::array<int, 2> position=players[0].getPosition();
        cout<<"insert piece where? (write (x,y))";
        cin>>s;
        mov[0] = s[1] - '0';
        mov[1] = s[3] - '0';
        board.insertPlate(mov[0],mov[1]);
        vector<array<int, 2>> atteignables = board.searchPath(position[0],position[1]);
        board.showBoard();
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