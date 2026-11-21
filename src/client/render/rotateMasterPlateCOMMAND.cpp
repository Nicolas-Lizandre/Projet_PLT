//
// Created by nicol on 11/11/2026.
//

#include <state/Board.h>
#include <state/State.h>

#include "rotateMasterplateCOMMAND.h"

using namespace render;

rotateMasterplateCOMMAND::rotateMasterplateCOMMAND (state::State & gamecore) : gamecore(gamecore) {
}

void rotateMasterplateCOMMAND::exec () {
    gamecore.getBoard().turnMasterPlate();//Rotation TRIGO
}
