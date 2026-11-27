//
// Created by nicol on 27/11/2026.
//
#include "setEntitiesCOMMAND.h"

#include <iostream>
#include <ostream>
#include <SFML/System/Vector2.hpp>
#include <state/easyAI.h>
#include <state/heuristicAI.h>
#include <state/Player.h>
#include <state/State.h>

inline const std::array<std::array<int, 2>, 4> initial_positions{{
    {0, 0},
    {6, 6},
    {6, 0},
    {0, 6}
}};


using namespace render;

setEntitiesCOMMAND::setEntitiesCOMMAND (state::State & gamecore, std::array<EntityQUERIED,4> demand_entity_list) :
gamecore(gamecore), demand_entity_list(demand_entity_list) {
}

//HARD AI not implemented !!!!!!!!!!!!
void setEntitiesCOMMAND::exec () {
    //Cannot FAIL
    int given_placement = 0; //In case a NONE that would break
    for(int i = 0; i < demand_entity_list.size(); i++) {
        switch(demand_entity_list[i]) {
            case HUMAN : gamecore.getPlayers().at(given_placement) =
                std::make_unique<state::Player>(initial_positions[given_placement][0],initial_positions[given_placement][1]); break;
            case EASY_AI : gamecore.getPlayers().at(given_placement) =
                std::make_unique<state::easyAI>(initial_positions[given_placement][0],initial_positions[given_placement][1]); break;
            case HEURISTIC_AI : gamecore.getPlayers().at(given_placement) =
                std::make_unique<state::heuristicAI>(initial_positions[given_placement][0],initial_positions[given_placement][1]); break;
            case HARD_AI : /*gamecore.getPlayers().at(given_placement) =
                std::make_unique<state::hardAI>(initial_positions[given_placement][0],initial_positions[given_placement][1]);*/ break;
            //To cancel given_placement
            case NONE : given_placement --; break;
        }
        given_placement++;
    }
    //Treasures need to be dealt with "literally"
    gamecore.dealTreasures();

    //Necessary if the first player is an AI
    if(typeid(*gamecore.getPlayers().at(0))!=typeid(state::Player)) {
        gamecore.advanceTurn();
    }
}