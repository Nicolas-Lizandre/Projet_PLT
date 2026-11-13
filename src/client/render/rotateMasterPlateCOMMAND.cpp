//
// Created by nicol on 11/11/2026.
//

#include <state/Board.h>

#include "rotateMasterplateCOMMAND.h"

using namespace render;

rotateMasterplateCOMMAND::rotateMasterplateCOMMAND (state::Board & board) : board(board) {

}
void rotateMasterplateCOMMAND::exec () {
    board.turnMasterPlate();//Rotation TRIGO
}