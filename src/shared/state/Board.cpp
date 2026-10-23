//
// Created by tompi on 08/10/2026.
//

#include "Board.h"
#include "L.h"
#include "T.h"
#include "I.h"

#include <iostream>
#include <memory>
#include <queue>
#include <array>
#include <algorithm>
#include <utility>

state::Board::Board(): playground{}, masterplate{} {

}


bool state::Board::verifyInsertValidity(int i, int j) {
     int legal_inserts[12][2] = {
        {0, 1}, {0, 3}, {0, 5},
        {6, 1}, {6, 3}, {6, 5},
        {1, 0}, {3, 0}, {5, 0},
        {1, 6}, {3, 6}, {5, 6}
    };

    for ( auto& pos : legal_inserts) {
        if (pos[0] == i && pos[1] == j) {
            return true;
        }
    }
    return false;
}

void state::Board::insertPlate(int i, int j) {
    if (verifyInsertValidity(i,j)) {
        auto tempPlate = std::move(masterplate);
        switch (i) {
            case 0:
                masterplate = std::move(playground[6][j]);
                for (int l = 6; l > 0; --l) {
                    playground[l][j] = std::move(playground[l - 1][j]);
                }
                playground[0][j] = std::move(tempPlate);
                return;

            case 6:
                masterplate = std::move(playground[0][j]);
                for (int l = 0;  l<6 ; l++) {
                    playground[l][j] = std::move(playground[l + 1][j]);
                }
                playground[6][j]=std::move(tempPlate);
                return;
        }

        switch (j) {
            case 0:
                masterplate = std::move(playground[i][6]);
                for (int l = 6;  l>0 ; l--) {
                    playground[i][l] = std::move(playground[i][l-1]);
                }
                playground[i][0]=std::move(tempPlate);
                return;

            case 6:
                masterplate = std::move(playground[i][0]);
                for (int l = 0;  l<6 ; l++) {
                    playground[i][l] = std::move(playground[i][l+1]);
                }
                playground[i][6]=std::move(tempPlate);
                return;
        }
    }
}


void state::Board::turnMasterPlate(){
    masterplate->turnPlate();
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
    for (auto& row : playground) {
        for (auto& plate : row) {
            plate = std::make_unique<state::L>();
        }
    }
    masterplate = std::make_unique<state::T>();
}

std::vector<std::array<int, 2>> state::Board::searchPath (int i, int j)
{
    std::vector<std::array<int, 2>> reachable;
 
    if (i < 0 || i >= 7 || j < 0 || j >= 7) return reachable;
 
    if (!playground[i][j]) return reachable;
 
    const int di[4] = { -1, 0, 1, 0 };
    const int dj[4] = { 0, 1, 0, -1 };
 
    auto isOpen = [this](int a, int b, int dir) {
        const std::unique_ptr<Plate>& plate = playground[a][b];
        if (!plate) return false;
        switch (dir) {
        case 0:  return plate->getNorth();
        case 1:  return plate->getEast();
        case 2:  return plate->getSouth();
        case 3:  return plate->getWest();
        default: return false;
        }
    };
 
    bool visited[7][7] = {};               
    std::queue<std::array<int, 2>> file;   
 
    visited[i][j] = true;
    file.push({ i, j });
 
    while (!file.empty()) {
        std::array<int, 2> courante = file.front();   
        file.pop();                                   
        reachable.push_back(courante);                
 
        for (int dir = 0; dir < 4; ++dir) {           
            int ni = courante[0] + di[dir];
            int nj = courante[1] + dj[dir];
 
            if (ni < 0 || ni >= 7 || nj < 0 || nj >= 7) continue;   
            if (visited[ni][nj]) continue;                          
 
            if (isOpen(courante[0], courante[1], dir) &&
                isOpen(ni, nj, (dir + 2) % 4)) {
                visited[ni][nj] = true;     
                file.push({ ni, nj });
            }
        }
    }
    return reachable;
}