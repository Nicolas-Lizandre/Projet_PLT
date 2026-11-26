//
// Created by tompi on 08/10/2026.
//ybyh

#include "Plate.h"
#include <iostream>
state::Plate::Plate(bool n, bool e, bool s, bool w): North(n), East(e), South(s), West(w) {

}

void state::Plate::turnPlate() {
    bool temp= North;
    North= West;
    West= South;
    South= East;
    East= temp;
    rotation= (rotation+1)%4;
};

bool state::Plate::getNorth() const {
    return North;
}

bool state::Plate::getSouth() const {
    return South;
}

bool state::Plate::getEast() const {
    return East;
}

bool state::Plate::getWest() const {
    return West;
}

bool state::Plate::hasTreasure(Treasure expected) const {
    return expected != Treasure::NONE && treasure == expected;
}

void state::Plate::setTreasure(Treasure value) {
    treasure = value;
}


void state::Plate::showPlate()
{
    const char* symbol = " ";

    if (North && South && East) {
        symbol = "├";
    }
    else if (North && South && West) {
        symbol = "┤";
    }
    else if (East && South && West) {
        symbol = "┬";
    }
    else if (North && East && West) {
        symbol = "┴";
    }
    else if (North && East) {
        symbol = "└";
    }
    else if (North && West) {
        symbol = "┘";
    }
    else if (South && East) {
        symbol = "┌";
    }
    else if (South && West) {
        symbol = "┐";
    }
    else if (North && South) {
        symbol = "|";
    }
    else if (East && West) {
        symbol = "─";
    }

    std::cout << symbol;
}

/*
std::string state::Plate::getPlateAssetFromAcesses () const {
    std::string asset_path;

    if (North && South && East) {
        asset_path = "../assets/labyrinth_pieces/├.png";
    }
    else if (North && South && West) {
        asset_path = "../assets/labyrinth_pieces/┤.png";
    }
    else if (East && South && West) {
        asset_path = "../assets/labyrinth_pieces/┬.png";
    }
    else if (North && East && West) {
        asset_path = "../assets/labyrinth_pieces/┴.png";
    }
    else if (North && East) {
        asset_path = "../assets/labyrinth_pieces/└.png";
    }
    else if (North && West) {
        asset_path = "../assets/labyrinth_pieces/┘.png";
    }
    else if (South && East) {
        asset_path = "../assets/labyrinth_pieces/┌.png";
    }
    else if (South && West) {
        asset_path = "../assets/labyrinth_pieces/┐.png";
    }
    else if (North && South) {
        asset_path = "../assets/labyrinth_pieces/I.png";
    }
    else if (East && West) {
        asset_path = "../assets/labyrinth_pieces/-.png";
    }

    return asset_path;
}
*/
state::Treasure state::Plate::getTreasure() const {
    return treasure;
}


/*
std::string state::Plate::getPlateTreasureAsset () const {
    std::string asset_path;
    switch (treasure) { //NONE + 24 Trésors
        case Treasure::NONE: asset_path = "../assets/labyrinth_treasures/NONE.png"; break;//Ce n'est jamais censé arriver - c'est quand même mis au cas où
        case Treasure::BAT: asset_path = "../assets/labyrinth_treasures/BAT.png"; break;
        case Treasure::BEETLE: asset_path = "../assets/labyrinth_treasures/BEETLE.png"; break;
        case Treasure::BOOK: asset_path = "../assets/labyrinth_treasures/BOOK.png"; break;
        case Treasure::CANDLEHOLDER: asset_path = "../assets/labyrinth_treasures/CANDLEHOLDER.png"; break;
        case Treasure::CAT: asset_path = "../assets/labyrinth_treasures/CAT.png"; break;
        case Treasure::CROWN: asset_path = "../assets/labyrinth_treasures/CROWN.png"; break;
        case Treasure::CUP: asset_path = "../assets/labyrinth_treasures/CUP.png"; break;
        case Treasure::DAGGER: asset_path = "../assets/labyrinth_treasures/DAGGER.png"; break;
        case Treasure::DRAGON: asset_path = "../assets/labyrinth_treasures/DRAGON.png"; break;
        case Treasure::ENSEA: asset_path = "../assets/labyrinth_treasures/ENSEA.png"; break;
        case Treasure::GEM: asset_path = "../assets/labyrinth_treasures/GEM.png"; break;
        case Treasure::GENIE: asset_path = "../assets/labyrinth_treasures/GENIE.png"; break;
        case Treasure::GHOST: asset_path = "../assets/labyrinth_treasures/GHOST.png"; break;
        case Treasure::GNOME: asset_path = "../assets/labyrinth_treasures/GNOME.png"; break;
        case Treasure::HELMET: asset_path = "../assets/labyrinth_treasures/HELMET.png"; break;
        case Treasure::KEY: asset_path = "../assets/labyrinth_treasures/KEY.png"; break;
        case Treasure::LIZARD: asset_path = "../assets/labyrinth_treasures/LIZARD.png"; break;
        case Treasure::OWL: asset_path = "../assets/labyrinth_treasures/OWL.png"; break;
        case Treasure::POTION: asset_path = "../assets/labyrinth_treasures/POTION.png"; break;
        case Treasure::PURSE: asset_path = "../assets/labyrinth_treasures/PURSE.png"; break;
        case Treasure::RAT: asset_path = "../assets/labyrinth_treasures/RAT.png"; break;
        case Treasure::RING: asset_path = "../assets/labyrinth_treasures/RING.png"; break;
        case Treasure::SPIDER: asset_path = "../assets/labyrinth_treasures/SPIDER.png"; break;
        case Treasure::UNICORN: asset_path = "../assets/labyrinth_treasures/UNICORN.png"; break;
    }
    return asset_path;

}*/


