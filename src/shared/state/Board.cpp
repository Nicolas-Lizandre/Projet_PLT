//
// Created by tompi on 08/10/2026.
//

#include "Board.h"
#include <iostream>

void state::Board::insertPlate(int i, int j, Plate plate) {
    Plate tempPlate= masterplate;
    switch (i) {
        case 0:
            masterplate = board[6][j];
            for (int l = 0;  l<6 ; l++) {
                board[6-l][j] = board[5-l][j];
            }
            board[0][j]=tempPlate;
            break;

        case 6:
            masterplate = board[0][j];
            for (int l = 0;  l<6 ; l++) {
                board[l][j] = board[l+1][j];
            }
            board[6][j]=tempPlate;
            break;
    }

    switch (j) {
        case 0:
            masterplate = board[i][6];
            for (int l = 0;  l<6 ; l++) {
                board[i][6-l] = board[i][5-l];
            }
            board[i][0]=tempPlate;
            break;

        case 6:
            masterplate = board[i][0];
            for (int l = 0;  l<6 ; l++) {
                board[i][l] = board[i][l+1];
            }
            board[i][6]=tempPlate;
            break;
    }
}


void state::Board::turnMasterPlate(Plate masterplate){
    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 7; ++j) {
            board[i][j].showPlate();
        }
        std::cout << '\n';
    }
}