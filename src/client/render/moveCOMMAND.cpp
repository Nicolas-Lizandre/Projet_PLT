//
// Created by nicol on 19/11/2026.
//

#include <state/Board.h>
#include "moveCOMMAND.h"

#include <state/State.h>
using namespace render;

moveCOMMAND::moveCOMMAND (int i, int j, state::State & gamecore) : i(i), j(j), gamecore(gamecore) {}


void moveCOMMAND::exec () {
    /*
    //Besoin de l'Id du joueur faisant la commande ! - Ici on lira juste le champ player_turn et
    int idx_player = gamecore.getPlayerTurn();
    state::Player player = gamecore.getPlayers()[idx_player];

    std::array<int, 2> pos = gamecore.getPlayers()[idx_player].getPosition();
    for (auto position_candidate : gamecore.getBoard().searchPath(i, j)) {
        if(player.getPosition() == position_candidate) {
            player.move(position_candidate[0],position_candidate[1]);
            return;
        }
    }
    */
}
