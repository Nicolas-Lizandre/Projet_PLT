//
// Created by tompi on 08/10/2026.
//

#include "Board.h"
#include "L.h"
#include "T.h"
#include "I.h"

#include <iostream>
#include <memory>

state::Board::Board(): playground{}, masterplate{} {
}

void state::Board::insertPlate(int i, int j) {
    auto tempPlate = std::move(masterplate);
    switch (i) {
        case 0:
            masterplate = std::move(playground[6][j]);
            for (int l = 6; l > 0; --l) {
                playground[l][j] = std::move(playground[l - 1][j]);
            }
            playground[0][j] = std::move(tempPlate);
            break;

        case 6:
            masterplate = std::move(playground[0][j]);
            for (int l = 0;  l<6 ; l++) {
                playground[l][j] = std::move(playground[l + 1][j]);
            }
            playground[6][j]=std::move(tempPlate);
            break;
    }

    switch (j) {
        case 0:
            masterplate = std::move(playground[i][6]);
            for (int l = 6;  l>0 ; l--) {
                playground[i][l] = std::move(playground[i][l]);
            }
            playground[i][0]=std::move(tempPlate);
            break;

        case 6:
            masterplate = std::move(playground[i][0]);
            for (int l = 0;  l<6 ; l++) {
                playground[i][l] = std::move(playground[i][l+1]);
            }
            playground[i][6]=std::move(tempPlate);
            break;
    }
}


void state::Board::turnMasterPlate(Plate masterplate){

}

void state::Board::showBoard() {
    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 7; ++j) {
            playground[i][j]->showPlate();
        }
        std::cout << '\n';
    }
}

void state::Board::createPlayground() {
    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 7; ++j) {
            playground[i][j] = std::make_unique<state::L>();
        }
    }
    masterplate = std::make_unique<state::T>();
}