//
// Created by tompi on 08/10/2026.
//
#include "Player.h"
#include "Board.h"
#include <iostream>
using namespace std;

state::Player::Player(int i, int j): Entity(i,j) {
    position[0]=i;
    position[1]=j;
    starting_position[0]=i;
    starting_position[1]=j;
}

std::array<int, 2> state::Player::chooseInsert(Board &board) {
    bool temp = true;
    string s;
    std::array<int, 2> mov;
    while (temp) {
        cout << " Masterplate: ";
        board.displayMasterplate();
        cout << " \n Do you want to turn the plate? (y/n)";
        cin >> s;

        if (s == "y") {
            board.turnMasterPlate();
        } else if (s == "n") {
            temp = false;
        }
    }

    cout << "insert plate where? (write xy)";
    cin >> s;

    while (s.size() != 2) {
        cout << "Incorrect message length" << endl;
        cout << "insert plate where? (write xy)";
        cin >> s;
    }

    mov[0] = s[0] - '0';
    mov[1] = s[1] - '0';
    return mov;
}

std::array<int, 2> state::Player::chooseMovement(std::vector<std::array<int, 2> > reachable, Board &board) {
    string s;
    std::array<int, 2> mov;

    cout << "move to? (write xy)";
    cin >> s;
    while (s.size() != 2) {
        cout << "Incorrect message length" << endl;
        cout << "move to? (write xy)";
        cin >> s;
    }

    mov[0] = s[0] - '0';
    mov[1] = s[1] - '0';
    return mov;
}
