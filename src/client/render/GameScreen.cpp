//
// Created by nicol on 05/11/2026.
//
#include "GameScreen.h"

#include <iostream>
#include <state/Board.h>
#include <state/I.h>
#include <state/Plate.h>
#include <state/T.h>

#include "ArialFont.h"
#include "InsertPlateCOMMAND.h"
#include "ListCommands.h"
#include "rotateMasterplateCOMMAND.h"

using namespace render;

#define INSERT_0_1_BOUNDS sf::FloatRect({100.f,100.f},{50.f,50.f})   //Les 2 coins d'un rectangles
#define PLAYGROUND_POSITION sf::Vector2f(125, 125)
#define PLATE_SIZE 50
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
GameScreen::GameScreen (sf::RenderWindow & window, state::Board & board, ListCommands & list_commands)
: ScreenState(window), board(board), list_commands(list_commands) {
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
    list_complete_texts.push_back(std::move(cdt));

    //
    sf::Text counter_text = sf::Text(ArialFont::font, std::string("Reste :"), 25);
    counter_text.setFillColor(sf::Color::White);
    counter_text.setPosition({700.f, 375.f});
    cdt.text = std::make_unique<sf::Text>(counter_text);
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
                        list_commands.add(std::make_unique<InsertPlateCOMMAND>(board,insert_coord.x,insert_coord.y));
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
                            std::cout << "Zone Cliqué : " << X << " "<< Y << std::endl;
                        }
                    }
                }
            }

            //Sélection tourner Masterpiece
            for (auto & complete_sprite : list_complete_sprites) {
                if(complete_sprite.name_id == "masterplate_graybox") {
                    if(complete_sprite.sprite->getGlobalBounds().contains(mousePos)) {
                        list_commands.add(std::make_unique<rotateMasterplateCOMMAND>(board));
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

void GameScreen::drawablesUpdate() {
    //
    completeSprite cd;
    cd.is_background = false;
    completeText cdt;
    cdt.is_background = false;

    //erasure of all non-background element (chatgpt)
    for (auto it = list_complete_sprites.begin();
     it != list_complete_sprites.end(); )
    {
        if (!it->is_background)
            it = list_complete_sprites.erase(it);
        else
            ++it;
    }
    //playground Plates
    for(int i = 0; i < board.getPlayground().size(); i++) {
        for(int j = 0; j < board.getPlayground()[i].size(); j++) {
            //std::cout << board.getPlayground()[i].size() << std::endl;
            //createAdequateSprite ("I" by default)
            auto& plate = board.getPlayground()[i][j];
            if (plate){
                cd.respective_texture =std::make_unique<sf::Texture>(selectCorrespondingPlate(*plate));
            }
            else{ //La Plate n'existe pas (jamais censé arriver)
                cd.respective_texture =std::make_unique<sf::Texture>("../assets/labyrinth_pieces/|.png");
            }

            cd.sprite = std::make_unique<sf::Sprite>(sf::Sprite(*cd.respective_texture)); //0, 0, 800, 600
            cd.sprite->setPosition(sf::Vector2f(GameScreen::convert_PlaygroundPosition_To_SpritePosition(i, j)));
            cd.sprite->setScale(sf::Vector2f(1.f, 1.f));
            cd.is_background = false;
            list_complete_sprites.push_back(std::move(cd));
            GameScreen::convert_PlaygroundPosition_To_SpritePosition(i,j);
        }
    }

    //MasterPlate
    cd.respective_texture =std::make_unique<sf::Texture>(selectCorrespondingPlate(board.getMasterplate()));
    cd.sprite = std::make_unique<sf::Sprite>(sf::Sprite(*cd.respective_texture)); //0, 0, 800, 600
    cd.sprite->setPosition(sf::Vector2f(575.f, 150.f)); //Pareil que masterplate_graybox (un code plus propre l'aurait cherché puis appliqué)
    cd.sprite->setScale(sf::Vector2f(4.f, 4.f));
    cd.is_background = false;
    list_complete_sprites.push_back(std::move(cd));

}
//Créés par soucis de clarification
sf::Vector2i GameScreen::convert_PlaygroundPosition_To_SpritePosition(int i, int j) {
    return sf::Vector2i(PLAYGROUND_POSITION.x + i*PLATE_SIZE,PLAYGROUND_POSITION.y + j*PLATE_SIZE);
}

sf::Vector2i GameScreen::convert_SpritePosition_To_PlaygroundPosition(sf::Vector2f sprite_position) { // on attend un sprite.getPosition
    return sf::Vector2i(0, 0); //PAS FAIT !!
}


std::string GameScreen::selectCorrespondingPlate(state::Plate plate) { //Rotation TRIGO
    std::string plate_path = "../assets/labyrinth_pieces/";
    plate_path = plate_path +  plate.getPlateSymbolFromAcesses()+".png";
    return plate_path;
}

sf::Vector2i GameScreen::getInsertCoordinatesFromGrayBoxBonds(completeSprite & graybox) {
    int i = 0;
    int j = 0;
    std::cout << static_cast<int>(graybox.sprite->getPosition().x) << std::endl;
    std::cout << static_cast<int>(graybox.sprite->getPosition().y) << std::endl;

    switch (static_cast<int>(graybox.sprite->getPosition().x)) {
        case 50 : i = 0; break;
        case 175 : i = 1; break;
        case 275 : i = 3; break;
        case 375 : i = 5; break;
        case 500 : i = 6; break;
        default: ;
    }

    switch (static_cast<int>(graybox.sprite->getPosition().y)) {
        case 50 : j = 0; break;
        case 175 : j = 1; break;
        case 275 : j = 3; break;
        case 375 : j = 5; break;
        case 500 : j = 6; break;
        default: ;
    }

    return {i, j};
}

