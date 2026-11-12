//
// Created by nicol on 11/11/2026.
//
#include "InsertPlateCOMMAND.h"

#include <state/Board.h>
using namespace render;


InsertPlateCOMMAND::InsertPlateCOMMAND (state::Board & board, int i, int j) : board(board), i(i), j(j) {}
void InsertPlateCOMMAND::exec() {
    board.insertPlate(i,j);
}
