//
// Created by tompi on 08/10/2026.
//

#include "Board.h"
#include <iostream>
#include <array>
#include <queue>
#include <vector>

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

}

void state::Board::showBoard() {
    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 7; ++j) {
            board[i][j].showPlate();
        }
        std::cout << '\n';
    }
}

std::vector<std::array<int, 2>> state::Board::searchPath (int i, int j)
{
    std::vector<std::array<int, 2>> reachable;

    if (i < 0 || i >= 7 || j < 0 || j >= 7) return reachable;

    const int di[4] = { -1, 0, 1, 0 };
    const int dj[4] = { 0, 1, 0, -1 };

    auto isOpen = [](const Plate& plate, int dir) {
        switch (dir) {
        case 0:  return plate.getNorth();
        case 1:  return plate.getEast();
        case 2:  return plate.getSouth();
        case 3:  return plate.getWest();
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

        if (isOpen(board[courante[0]][courante[1]], dir) &&
            isOpen(board[ni][nj], (dir + 2) % 4)) {
            visited[ni][nj] = true;     
            file.push({ ni, nj });
        }
        }
    }
    return reachable;
}