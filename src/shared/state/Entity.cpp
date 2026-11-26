//
// Created by tompi on 20/11/2026.
//
#include "Entity.h"

#include "State.h"

void state::Entity::move(int i, int j) {
    position[0]=i;
    position[1]=j;
}

std::array<int, 2>  state::Entity::getPosition () {
    return position;
}

state::Treasure state::Entity::getCurrentTreasure() const {
    if (treasure_index >= static_cast<int>(treasure_list.size())) {
        return Treasure::NONE;
    }

    return treasure_list[treasure_index];
}

void state::Entity::setTreasureList(
    const std::array<state::Treasure, 12>& treasures)
{
    treasure_list = treasures;
    treasure_index = 0;
}

void state::Entity::advanceTreasure() {
    if (treasure_index < static_cast<int>(treasure_list.size())) {
        ++treasure_index;
    }
}

state::Entity::Entity(int i, int j) {
    position[0]=i;
    position[1]=j;
    starting_position[0]=i;
    starting_position[1]=j;
}