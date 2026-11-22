//
// Created by nicol on 20/11/2026.
//

#include "state/AssetsPath.h"
using namespace state;


std::string AssetsPath::getPlateAssetPath(Plate plate){
    std::string asset_path;

    if (plate.getNorth() && plate.getSouth() && plate.getEast()) {
        asset_path = "../assets/labyrinth_pieces/├.png";
    }
    else if (plate.getNorth() && plate.getSouth() && plate.getWest()) {
        asset_path = "../assets/labyrinth_pieces/┤.png";
    }
    else if (plate.getEast() && plate.getSouth() && plate.getWest()) {
        asset_path = "../assets/labyrinth_pieces/┬.png";
    }
    else if (plate.getNorth() && plate.getEast() && plate.getWest()) {
        asset_path = "../assets/labyrinth_pieces/┴.png";
    }
    else if (plate.getNorth() && plate.getEast()) {
        asset_path = "../assets/labyrinth_pieces/└.png";
    }
    else if (plate.getNorth() && plate.getWest()) {
        asset_path = "../assets/labyrinth_pieces/┘.png";
    }
    else if (plate.getSouth() && plate.getEast()) {
        asset_path = "../assets/labyrinth_pieces/┌.png";
    }
    else if (plate.getSouth() && plate.getWest()) {
        asset_path = "../assets/labyrinth_pieces/┐.png";
    }
    else if (plate.getNorth() && plate.getSouth()) {
        asset_path = "../assets/labyrinth_pieces/I.png";
    }
    else if (plate.getEast() && plate.getWest()) {
        asset_path = "../assets/labyrinth_pieces/-.png";
    }

    return asset_path;
}

std::string AssetsPath::getTreasureAssetPath(Treasure treasure){
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

}

std::string AssetsPath::getPieceAssetPath(Piece piece)
{
    switch (piece)
    {
        case state::Piece::RED_PIECE:
            return "../assets/Player0_GREEN_PIECE.png";

        case state::Piece::GREEN_PIECE:
            return "../assets/Player1_RED_PIECE.png";

    }
}