//
// Created by nicol on 19/11/2026.
//
#include "Command.h"

#include <state/Board.h>
#include "render/moveCOMMAND.h"

#include <iostream>
#include <ostream>
#include <state/State.h>
using namespace render;

moveCOMMAND::moveCOMMAND (int i, int j, state::State & gamecore) : i(i), j(j), gamecore(gamecore) {}


void moveCOMMAND::moveCOMMAND::exec () {
    if(gamecore.getPhase() == state::MOVE) {

        std::shared_ptr<state::Entity> & player = gamecore.getPlayers()[gamecore.getCurrentPlayer()];
        std::array<int, 2> player_pos = player->getPosition(); //chope position joueur

        for (auto available_pos : gamecore.getBoard().searchPath(player_pos[0], player_pos[1])) {
            std::cout <<  "ppos " << player_pos[0] << " " << player_pos[1] << std::endl;
            std::cout <<  "avpos " << available_pos[0] << " " << available_pos[1] << std::endl;
            if(available_pos == std::array<int, 2>{i , j}) {
                std::cout << "test MOVE" << std::endl;
                player->move(available_pos[0],available_pos[1]);
                gamecore.obtainTreasure(gamecore.getCurrentPlayer()); //Revoir ftment de la méth (mieux vaut la mettre dans player !)
                gamecore.advanceTurn();
                return;
            }
        }

    }

}

