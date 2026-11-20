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

#define INSERT_0_1_BOUNDS sf::FloatRect({100.f,100.f},{50.f,50.f})   //Les 2 coins d'un rectangles
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

    //Les assets suivants seront générés à chaque appels de draw donc on peut directement
    //les mettre dans list_complete_sprites et list_complete_text
    //Remarque : Par soucis de consision on pourrait juste mettre sur le même sprite (pas fait ici)


    completeSprite cd;
    // Bouton Commencer
    cd.respective_texture = std::make_unique<sf::Texture>("../assets/Background_LABYRINTHE.png");
    cd.sprite = std::make_unique<sf::Sprite>(sf::Sprite(*cd.respective_texture)); //0, 0, 800, 600
    cd.sprite->setPosition(sf::Vector2f(0, 0));
    cd.sprite->setScale(sf::Vector2f(1.f, 1.f));
    cd.is_background = true;
    list_complete_sprites.push_back(std::move(cd));

    cd.respective_texture = std::make_unique<sf::Texture>("../assets/Board_LABYRINTHE.png");
    cd.sprite = std::make_unique<sf::Sprite>(sf::Sprite(*cd.respective_texture)); //0, 0, 800, 600
    cd.sprite->setPosition(sf::Vector2f(100, 100));
    cd.sprite->setScale(sf::Vector2f(1.f, 1.f));
    cd.name_id = "Board_LABYRINTHE";
    cd.is_background = true;
    list_complete_sprites.push_back(std::move(cd));

    for(int i = 0; i < respective_graybox_position.size(); i++) {
        cd.respective_texture = std::make_unique<sf::Texture>("../assets/insertPiece_graybox.png"); //Taille 50 50
        cd.sprite = std::make_unique<sf::Sprite>(sf::Sprite(*cd.respective_texture));
        cd.sprite->setPosition(respective_graybox_position[i]);
        cd.sprite->setScale(sf::Vector2f(1.f, 1.f));
        cd.name_id = "insertPiece_graybox";
        cd.is_background = true;
        list_complete_sprites.push_back(std::move(cd));
    }

    cd.respective_texture = std::make_unique<sf::Texture>("../assets/masterplate_graybox.png");
    cd.sprite = std::make_unique<sf::Sprite>(sf::Sprite(*cd.respective_texture)); //0, 0, 800, 600
    cd.sprite->setPosition(sf::Vector2f(575.f, 150.f));
    cd.sprite->setScale(sf::Vector2f(4.f, 4.f));
    cd.name_id = "masterplate_graybox";
    cd.is_background = true;
    //cd.sprite->rotate(sf::degrees(90.f)); //les rotations se font centrées sur setPosition
    list_complete_sprites.push_back(std::move(cd));


    //Combi Trésor + Carte
    //LA CARTE
    cd.respective_texture = std::make_unique<sf::Texture>("../assets/Carte_LABYRINTHE.png");
    cd.sprite = std::make_unique<sf::Sprite>(sf::Sprite(*cd.respective_texture)); //0, 0, 800, 600
    cd.sprite->setPosition(sf::Vector2f(560.f, 375.f));
    cd.sprite->setScale(sf::Vector2f(0.25, 0.25));
    cd.is_background = true;
    list_complete_sprites.push_back(std::move(cd));



    completeText cdt;

    sf::Text turn_text = sf::Text(ArialFont::font, std::string("TOUR :"), 50);
    turn_text.setFillColor(sf::Color::White);
    turn_text.setPosition({575.f, 20.f});
    cdt.text = std::make_unique<sf::Text>(turn_text);
    cdt.is_background = true;
    list_complete_texts.push_back(std::move(cdt));

    //
    sf::Text counter_text = sf::Text(ArialFont::font, std::string("Reste :"), 25);
    counter_text.setFillColor(sf::Color::White);
    counter_text.setPosition({700.f, 375.f});
    cdt.text = std::make_unique<sf::Text>(counter_text);
    cdt.is_background = true;
    list_complete_texts.push_back(std::move(cdt));

}

void GameScreen::handleEvents (sf::Event & event) {
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
    completeSprite cd;
    cd.is_background = false;
    completeText cdt;
    cdt.is_background = false;


    //erasure of all non-background element [sprites]
    for (auto it = list_complete_sprites.begin();
     it != list_complete_sprites.end(); )
    {
        if (!it->is_background)
            it = list_complete_sprites.erase(it);
        else
            ++it;
    }

    //erasure of all non-background element [texts]
    for (auto it = list_complete_texts.begin();
     it != list_complete_texts.end(); )
    {
        if (!it->is_background)
            it = list_complete_texts.erase(it);
        else
            ++it;
    }


    //playground Plates
    for(int i = 0; i < gamecore.getBoard().getPlayground().size(); i++) {
        for(int j = 0; j < gamecore.getBoard().getPlayground()[i].size(); j++) {
            //std::cout << board.getPlayground()[i].size() << std::endl;
            //createAdequateSprite ("I" by default)
            auto& plate = gamecore.getBoard().getPlayground()[i][j]; //On ne s'est pas concerté sur comment indexer le plateau

            //Partie 1 : Sprite de la pièce//
            if (plate){
                cd.respective_texture =std::make_unique<sf::Texture>(state::AssetsPath::getPlateAssetPath(*plate)); //aeff getPlateFromAcessPath
            }
            else{ //La Plate n'existe pas (jamais censé arriver)
                cd.respective_texture =std::make_unique<sf::Texture>("../assets/labyrinth_pieces/|.png");
            }

            cd.sprite = std::make_unique<sf::Sprite>(sf::Sprite(*cd.respective_texture)); //0, 0, 800, 600
            cd.sprite->setPosition(sf::Vector2f(GameScreen::convert_PlaygroundPosition_To_SpritePosition(i, j)));
            cd.sprite->setScale(sf::Vector2f(1.f, 1.f));
            list_complete_sprites.push_back(std::move(cd));
            //GameScreen::convert_PlaygroundPosition_To_SpritePosition(i,j);

            //Partie 2 : Le Trésor//
            if(!plate->hasTreasure(state::Treasure::NONE)) { //hasTreasure est mal codé (dans le sens il est censé être un test à NONE !!)
                cd.respective_texture = std::make_unique<sf::Texture>(state::AssetsPath::getTreasureAssetPath(plate->getTreasure())); //aeff plate->getPlateTreasureAsset()

                cd.sprite = std::make_unique<sf::Sprite>(sf::Sprite(*cd.respective_texture));
                cd.sprite->setPosition(sf::Vector2f(
                    GameScreen::convert_PlaygroundPosition_To_SpritePosition(i, j).x+7.f,
                    GameScreen::convert_PlaygroundPosition_To_SpritePosition(i, j).y+7.f)); //ajout offset
                cd.sprite->setScale(sf::Vector2f(1.f, 1.f));       
                list_complete_sprites.push_back(std::move(cd));
                //GameScreen::convert_PlaygroundPosition_To_SpritePosition(i,j);
            }

        }
    }

    //MasterPlate
    auto masterplate = gamecore.getBoard().getMasterplate();
    cd.respective_texture =std::make_unique<sf::Texture>(state::AssetsPath::getPlateAssetPath(masterplate));
    cd.sprite = std::make_unique<sf::Sprite>(sf::Sprite(*cd.respective_texture)); //0, 0, 800, 600
    cd.sprite->setPosition(sf::Vector2f(575.f, 150.f)); //Pareil que masterplate_graybox (un code plus propre l'aurait cherché puis appliqué)
    cd.sprite->setScale(sf::Vector2f(4.f, 4.f));
    list_complete_sprites.push_back(std::move(cd));
    if(!masterplate.hasTreasure(state::Treasure::NONE)) {
        cd.respective_texture = std::make_unique<sf::Texture>(state::AssetsPath::getTreasureAssetPath(masterplate.getTreasure()));
        cd.sprite = std::make_unique<sf::Sprite>(sf::Sprite(*cd.respective_texture));
        cd.sprite->setPosition(sf::Vector2f(575.f+7.f, 150.f+7.f)); //ajout offset
        cd.sprite->setScale(sf::Vector2f(4.f, 4.f));
        list_complete_sprites.push_back(std::move(cd));
        //GameScreen::convert_PlaygroundPosition_To_SpritePosition(i,j);
    }

    //Pion == Joueur ID
    //Joueurs respectifs

    //À réécrire
    std::array<state::Player, 2> players = gamecore.getPlayers(); //allège code
    for(int i = 0; i < players.size(); i++) { //cette ligne sera à modif
        // Le pion
        switch (i) {
            case(0) : cd.respective_texture =std::make_unique<sf::Texture>("../assets/Player0_GREEN_PIECE.png"); break;
            case(1) : cd.respective_texture =std::make_unique<sf::Texture>("../assets/Player1_RED_PIECE.png");  break;
            //case default : turn_text.setFillColor(sf::Color::White); break;
        }
        cd.sprite = std::make_unique<sf::Sprite>(sf::Sprite(*cd.respective_texture)); //0, 0, 800, 600
        //std::cout << "Test GameScreen :" << players[i].getPosition()[0] << players[i].getPosition()[1] << std::endl;
        cd.sprite->setPosition(sf::Vector2f(convert_PlaygroundPosition_To_SpritePosition(
            players[i].getPosition()[0],players[i].getPosition()[1]))); //Pareil que masterplate_graybox (un code plus propre l'aurait cherché puis appliqué)
        cd.sprite->setScale(sf::Vector2f(1.f, 1.f));
        list_complete_sprites.push_back(std::move(cd));


        // Le joueur peut faire des actions si c'est celui demandé
        if(gamecore.getPlayingPiecePlayerID() == i) {   //Pion == Joueur ID

            //Joueur en cours
            sf::Text turn_text = sf::Text(ArialFont::font, std::string("Player" + std::to_string(i)), 30);

            //Choix couleur du joueur
            switch (gamecore.getPlayingPiece()) {
                case(state::Piece::GREEN_PIECE) : turn_text.setFillColor(sf::Color::Green); break;
                case(state::Piece::RED_PIECE) : turn_text.setFillColor(sf::Color(255, 0, 255, 255)); break; //Violet car Rouge sur fond Rouge pas Visible
                //case default : turn_text.setFillColor(sf::Color::White); break;
            }

            turn_text.setPosition({575.f, 80.f});
            cdt.text = std::make_unique<sf::Text>(turn_text);
            list_complete_texts.push_back(std::move(cdt));

            //Le nombre de trésors restant
            sf::Text counter_text = sf::Text(ArialFont::font, std::to_string(TREASURES_TO_FIND_AT_2_PLAYERS - gamecore.getPlayers()[i].getTreasureIndex()), 50);
            counter_text.setFillColor(sf::Color::White);
            counter_text.setPosition({700.f, 425.f});
            cdt.text = std::make_unique<sf::Text>(counter_text);
            list_complete_texts.push_back(std::move(cdt));

            //Le trésor affiché
            cd.respective_texture = std::make_unique<sf::Texture>(state::AssetsPath::getTreasureAssetPath(players[i].getCurrentTreasure()));
            cd.sprite = std::make_unique<sf::Sprite>(sf::Sprite(*cd.respective_texture)); //0, 0, 800, 600
            cd.sprite->setPosition(sf::Vector2f(590.f, 425.f));
            cd.sprite->setScale(sf::Vector2f(2.f, 2.f));
            list_complete_sprites.push_back(std::move(cd));
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

