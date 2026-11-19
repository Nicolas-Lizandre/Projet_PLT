//
// Created by nicol on 11/11/2026.
//
#include "InsertPlateCOMMAND.h"

#include <iostream>
#include <ostream>
#include <state/Board.h>
#include <state/State.h>
using namespace render;


InsertPlateCOMMAND::InsertPlateCOMMAND (state::State & gamecore, int i, int j) : gamecore(gamecore), i(i), j(j) {}
void InsertPlateCOMMAND::exec() {
    gamecore.getBoard().insertPlate(i,j); // verify à l'intérieur
}
