//
// Created by nicol on 05/11/2026.
//
#include "GameScreen.h"

#include <iostream>
#include <state/AssetsPath.h>
#include <state/Board.h>
#include <state/I.h>
#include <state/Plate.h>
#include <state/T.h>

#include "ArialFont.h"
#include "InsertPlateCOMMAND.h"
#include "ListCommands.h"
#include "moveCOMMAND.h"
#include "rotateMasterplateCOMMAND.h"

using namespace render;

#define PLAYGROUND_POSITION sf::Vector2f(125, 125)
#define PLATE_SIZE 50
#define TREASURES_TO_FIND_AT_2_PLAYERS 12
inline const std::array<sf::Vector2f, 12> respective_graybox_position{
    //ligne du haut
    sf::Vector2f(175.f, 50.f),
    sf::Vector2f(275.f, 50.f),
    sf::Vector2f(375.f, 50.f),
    //colonne de gauche
    sf::Vector2f(50.f, 175.f),
    sf::Vector2f(50.f, 275.f),
    sf::Vector2f(50.f, 375.f),
    //colonne de droite
    sf::Vector2f(500.f, 175.f),
    sf::Vector2f(500.f, 275.f),
    sf::Vector2f(500.f, 375.f),
    //ligne du bas
    sf::Vector2f(175.f, 500.f),
    sf::Vector2f(275.f, 500.f),
    sf::Vector2f(375.f, 500.f)
};




ScreenStateQUERIED GameScreen::getDemandScreenChange () {
    return demand_screen_change;
}

GameScreen::GameScreen (sf::RenderWindow & window, state::State & gamecore, ListCommands & list_commands)
: ScreenState(window), gamecore(gamecore), list_commands(list_commands) {
    std::cout << "Created GameScreen" << std::endl;

    /*All the Sprite are for the background so no need to erase them in drawablesUpdate
     *The following assets could be regrouped into 1*/

    //Background (red-yellow gradient)
    addCompleteSprite("../assets/Background_LABYRINTHE.png",
        {0, 0},{1.f, 1.f},true);
    //Board
    addCompleteSprite("../assets/Board_LABYRINTHE.png",
        {100, 100},{1,1},true,"Board_LABYRINTHE");
    //Gray boxes
    for(int i = 0; i < respective_graybox_position.size(); i++) {
        addCompleteSprite("../assets/insertPiece_graybox.png",
        respective_graybox_position[i],{1,1},true,"insertPiece_graybox");
    }
    //MasterPlate Gray box - Invisible
    addCompleteSprite("../assets/insertPiece_graybox.png",
        {575.f, 150.f},{4,4},true,"masterplate_graybox");
    //TreasureCard
    addCompleteSprite("../assets/Card_LABYRINTHE.png",
        {560.f, 375.f},{0.25, 0.25},true,"masterplate_graybox");


    //Backgound Texts
    addCompleteText(sf::Text(ArialFont::font,"TOUR :",50),
        sf::Color::White, {575.f, 20.f},true);
    addCompleteText(sf::Text(ArialFont::font,"Reste :",25),
        sf::Color::White, {700.f, 375.f},true);

}



void GameScreen::handleEvents (sf::Event & event) {
    //State Based events (chances are here is not the good place)
    for (auto &player : gamecore.getPlayers()) {
        if(player->getTreasureIndex() == TREASURES_TO_FIND_AT_2_PLAYERS) {
            demand_screen_change = VICTORYSCREEN;
        }
    }


    //GUI events
    if (const auto* mousePressed = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (mousePressed->button == sf::Mouse::Button::Left)
        {
            sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window)); //à remplacer par screen.askMousePosition ! Le Screen est l'Owner du window !

            //Sélection pièce rangée pièce
            for (auto & complete_sprite : list_complete_sprites) {
                if(complete_sprite.name_id == "insertPiece_graybox") {
                    if(complete_sprite.sprite->getGlobalBounds().contains(mousePos)) {
                        std::cout << "graybox selected" << std::endl;
                        sf::Vector2i insert_coord = getInsertCoordinatesFromGrayBoxBonds(complete_sprite);
                        list_commands.add(std::make_unique<InsertPlateCOMMAND>(gamecore,insert_coord.x,insert_coord.y));
                        //mousePos suffit pour deviner lequel c'est
                    }
                }
            }

            //Sélection case plateau
            for (auto & complete_sprite : list_complete_sprites) {
                if(complete_sprite.name_id == "Board_LABYRINTHE") {
                    if(complete_sprite.sprite->getGlobalBounds().contains(mousePos)) {
                        //Recentrage de la souris
                        float mouseX = mousePos.x - complete_sprite.sprite->getPosition().x - 25;
                        float mouseY = mousePos.y - complete_sprite.sprite->getPosition().y - 25;
                        int X = mouseX / PLATE_SIZE ;
                        int Y = mouseY / PLATE_SIZE ;
                        //Enlève le contour du plateau
                        if(mouseX >= 0 && mouseY >= 0 && mouseX < PLATE_SIZE*7 && mouseY < PLATE_SIZE*7) {
                            std::cout << "Zone Cliqué : " << Y << " "<< X << std::endl;
                            list_commands.add(std::make_unique<moveCOMMAND>(Y,X,gamecore));
                            //Attention i->y et j->x !!
                        }
                    }
                }
            }

            //Sélection tourner Masterpiece
            for (auto & complete_sprite : list_complete_sprites) {
                if(complete_sprite.name_id == "masterplate_graybox") {
                    if(complete_sprite.sprite->getGlobalBounds().contains(mousePos)) {
                        list_commands.add(std::make_unique<rotateMasterplateCOMMAND>(gamecore));
                        std::cout << "masterplate_graybox selected" << std::endl;
                    }
                }
            }

        }
    }
}

const std::vector<completeSprite> & GameScreen::getSprites () const {
    return list_complete_sprites;
}
const std::vector<completeText> & GameScreen::getTexts () const {
    return list_complete_texts;
}


//Fonctionne qu'à 2 joueurs !!
void GameScreen::drawablesUpdate() {
    //Erase ALL non-background
    eraseNonBackgroundDrawables();


    //Playground Plates
    for(int i = 0; i < gamecore.getBoard().getPlayground().size(); i++) {
        for(int j = 0; j < gamecore.getBoard().getPlayground()[i].size(); j++) {
            //createAdequateSprite ("I" by default)
            auto& plate = gamecore.getBoard().getPlayground()[i][j]; //On ne s'est pas concerté sur comment indexer le plateau

            //Part1 : Plate Sprite
            if (plate){
                addCompleteSprite(state::AssetsPath::getPlateAssetPath(*plate),
                    sf::Vector2f(GameScreen::convert_PlaygroundPosition_To_SpritePosition(i, j)),
                    {1,1}, false);
            }
            else{ //Should never be the case
                addCompleteSprite("../assets/labyrinth_pieces/|.png",
                                    sf::Vector2f(GameScreen::convert_PlaygroundPosition_To_SpritePosition(i, j)),
                                    {1,1}, false);
            }
            ///Part2 : Plate Treasure Sprite
            if(!plate->hasTreasure(state::Treasure::NONE)) { //hasTreasure est mal codé (dans le sens il est censé être un test à NONE !!)
                addCompleteSprite(state::AssetsPath::getTreasureAssetPath(plate->getTreasure()),
            {GameScreen::convert_PlaygroundPosition_To_SpritePosition(i, j).x+7.f,GameScreen::convert_PlaygroundPosition_To_SpritePosition(i, j).y+7.f},
                {1,1}, false);
            }
        }
    }

    //MasterPlate
    auto masterplate = gamecore.getBoard().getMasterplate();
    addCompleteSprite(state::AssetsPath::getPlateAssetPath(masterplate),
        {575.f, 150.f},{4.f, 4.f},false);
    //MasterPlate treasure
    if(!masterplate.hasTreasure(state::Treasure::NONE)) {
        addCompleteSprite(state::AssetsPath::getTreasureAssetPath(masterplate.getTreasure()),
            {575.f+7.f, 150.f+7.f},{4.f, 4.f},false);
    }

    /* /WARNING/
     * PLAYER IDs ARE BIND TO THE PIECE COLOR !
     * That's why gamecore.getPlayingPiecePlayerID() == i enables us to identify which player it's the turn !!!
     * And that's why static_cast<state::Piece>(i) get us the good Piece !
     */
    std::array<std::shared_ptr<state::Entity>, 2> &players = gamecore.getPlayers(); //To make the code simpler
    for(int i = 0; i < players.size(); i++) {
        //Piece Sprite
        addCompleteSprite(state::AssetsPath::getPieceAssetPath(i),
        sf::Vector2f(convert_PlaygroundPosition_To_SpritePosition(players[i]->getPosition()[0], players[i]->getPosition()[1])),
        {1,1},false);

        //To indicate which is the current player
        if(gamecore.getPlayingPlayerID() == i) {
            //Current player text WITH corresponding piece coloration
            switch (gamecore.getPlayingPlayerID()) {
                case(0) : addCompleteText(sf::Text(ArialFont::font, std::string("Player" + std::to_string(i)), 30),
                    sf::Color::Green,{575.f, 80.f},false); break;
                case(1) : addCompleteText(sf::Text(ArialFont::font, std::string("Player" + std::to_string(i)), 30),
                    sf::Color(255, 0, 255, 255),{575.f, 80.f},false); break; //Violet because Red on Red is not Visible
                //case default : turn_text.setFillColor(sf::Color::White); break;
            }

            //Number of Treasures to find
            addCompleteText(sf::Text(ArialFont::font, std::to_string(TREASURES_TO_FIND_AT_2_PLAYERS - gamecore.getPlayers()[i]->getTreasureIndex()), 50),
                sf::Color::White, {700.f, 425.f}, false);

            //Treasure to obtain
            addCompleteSprite(state::AssetsPath::getTreasureAssetPath(players[i]->getCurrentTreasure()),
                {590.f, 425.f},{2.f, 2.f},false);
        }
    }
}
//Créés par soucis de clarification
sf::Vector2i GameScreen::convert_PlaygroundPosition_To_SpritePosition(int i, int j) {
    //On ne s'est pas concerté sur quel index signifiait quoi - donc me voici inverser x et y ....
    return sf::Vector2i(PLAYGROUND_POSITION.x + j*PLATE_SIZE,PLAYGROUND_POSITION.y + i*PLATE_SIZE);
}

sf::Vector2i GameScreen::convert_SpritePosition_To_PlaygroundPosition(sf::Vector2f sprite_position) { // on attend un sprite.getPosition
    return sf::Vector2i(0, 0); //PAS FAIT !!
}



sf::Vector2i GameScreen::getInsertCoordinatesFromGrayBoxBonds(completeSprite & graybox) {
    int i = 0;
    int j = 0;
    std::cout << static_cast<int>(graybox.sprite->getPosition().x) << std::endl;
    std::cout << static_cast<int>(graybox.sprite->getPosition().y) << std::endl;

    switch (static_cast<int>(graybox.sprite->getPosition().y)) {
        case 50 : i = 0; break;
        case 175 : i = 1; break;
        case 275 : i = 3; break;
        case 375 : i = 5; break;
        case 500 : i = 6; break;
        default: ;
    }

    switch (static_cast<int>(graybox.sprite->getPosition().x)) {
        case 50 : j = 0; break;
        case 175 : j = 1; break;
        case 275 : j = 3; break;
        case 375 : j = 5; break;
        case 500 : j = 6; break;
        default: ;
    }

    return {i, j};
}

