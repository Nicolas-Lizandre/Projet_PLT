//
// Created by nicol on 05/11/2026.
//
#include "GameModeScreen.h"

#include "GameModeScreen.h"

#include <iostream>
#include <state/State.h>

#include "ArialFont.h"

using namespace render;

#define MAX_PLAYERS 4
inline const std::array<sf::Vector2f, 4> toogle_positions =
    {sf::Vector2f(300.f, 100.f),
    sf::Vector2f(300.f, 200.f),
    sf::Vector2f(300.f, 300.f),
    sf::Vector2f(300.f, 400.f)};

GameModeScreen::GameModeScreen (sf::RenderWindow & window, state::State & gamecore) : ScreenState(window), gamecore(gamecore) {
    std::cout << "Created GameModeScreen" << std::endl;

    toogle_list = {NONE,NONE,NONE,NONE};

    //Background (red-yellow gradient)
    addCompleteSprite("../assets/Background_LABYRINTHE.png",
        {0, 0},{1.f, 1.f},true);
    // Start Button Sprite
    addCompleteSprite("../assets/StartButtonSprite.png",
    {240, 500},{2.1f, 1.0f},true);

    //Toogle Player Type (reuse - StartButtonSprite)
    addCompleteSprite("../assets/StartButtonSprite.png",
    {300, 100},{1.5f, 1.0f},true,"Toogle0");
    addCompleteSprite("../assets/StartButtonSprite.png",
    {300, 200},{1.5f, 1.0f},true,"Toogle1");
    addCompleteSprite("../assets/StartButtonSprite.png",
    {300, 300},{1.5f, 1.0f},true,"Toogle2");
    addCompleteSprite("../assets/StartButtonSprite.png",
    {300, 400},{1.5f, 1.0f},true,"Toogle3");


    //Texts
    addCompleteText(sf::Text(ArialFont::font, std::string("Commencer"), 50),
        sf::Color::White, {260.f, 500.f}, true);
    //Player info
    addCompleteText(sf::Text(ArialFont::font, std::string("Joueur 0"), 50),
        sf::Color::Green, {50.f, 100.f}, true);
    addCompleteText(sf::Text(ArialFont::font, std::string("Joueur 1"), 50),
        sf::Color(255, 0, 255, 125), {50.f, 200.f}, true);
    addCompleteText(sf::Text(ArialFont::font, std::string("Joueur 2"), 50),
        sf::Color::Yellow, {50.f, 300.f}, true);
    addCompleteText(sf::Text(ArialFont::font, std::string("Joueur 3"), 50),
        sf::Color::Blue, {50.f, 400.f}, true);
}
void GameModeScreen::handleEvents (sf::Event & event) {
    if (const auto* mousePressed = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (mousePressed->button == sf::Mouse::Button::Left)
        {
            sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window)); //à remplacer par screen.askMousePosition ! Le Screen est l'Owner du window !

            for(completeSprite & complete_sprite : list_complete_sprites) {
                if(complete_sprite.name_id =="Toogle0") {
                    if(complete_sprite.sprite->getGlobalBounds().contains(mousePos)) {
                        tooglePlayer(0);
                    }
                }
                if(complete_sprite.name_id =="Toogle1") {
                    if(complete_sprite.sprite->getGlobalBounds().contains(mousePos)) {
                        tooglePlayer(1);
                    }
                }
                if(complete_sprite.name_id =="Toogle2") {
                    if(complete_sprite.sprite->getGlobalBounds().contains(mousePos)) {
                        tooglePlayer(2);
                    }
                }
                if(complete_sprite.name_id =="Toogle3") {
                    if(complete_sprite.sprite->getGlobalBounds().contains(mousePos)) {
                        tooglePlayer(3);
                    }
                }

            }



            if (mousePos.x >240 && mousePos.y > 500 && mousePos.x < 555 && mousePos.y < 566)
            {

                std::cout << "Zone clique GameModeScreen !" << std::endl;
                demand_screen_change = GAMESCREEN; //cet objet n'est pas utilisé
                //screen->set_current_screen_state(std::make_unique<GameModeScreen>(screen));
            }
        }
    }
}

const std::vector<completeSprite> & GameModeScreen::getSprites () const {
    return list_complete_sprites;
}
const std::vector<completeText> & GameModeScreen::getTexts () const {
    return list_complete_texts;
}

ScreenStateQUERIED GameModeScreen::getDemandScreenChange () {
    return demand_screen_change;
}

void GameModeScreen::drawablesUpdate() {
    eraseNonBackgroundDrawables();
    //Toogle Text
    for(int i = 0; i < MAX_PLAYERS; i++) { //
        switch(toogle_list[i]) {
            case NONE : addCompleteText(sf::Text(ArialFont::font, std::string("NONE"), 30),
                    sf::Color::White,toogle_positions[i],false); break;
            case HUMAN : addCompleteText(sf::Text(ArialFont::font, std::string("HUMAN"), 30),
                    sf::Color::White,toogle_positions[i],false); break;
            case EASY_AI : addCompleteText(sf::Text(ArialFont::font, std::string("EASY_AI"), 30),
                    sf::Color::White,toogle_positions[i],false); break;
            case HEURISTIC_AI : addCompleteText(sf::Text(ArialFont::font, std::string("NORMAL_AI"), 30),
                    sf::Color::White,toogle_positions[i],false); break;
            case HARD_AI : addCompleteText(sf::Text(ArialFont::font, std::string("HARD_AI"), 30),
                    sf::Color::White,toogle_positions[i],false); break;
        }

    }

}

void GameModeScreen::tooglePlayer(int playerID) {
    if(toogle_list[playerID] == NONE) {
        toogle_list[playerID] = HUMAN;
    }
    else if(toogle_list[playerID] == HUMAN) {
        toogle_list[playerID] = EASY_AI;
    }
    else if(toogle_list[playerID] == EASY_AI) {
        toogle_list[playerID] = HEURISTIC_AI;
    }
    else if(toogle_list[playerID] == HEURISTIC_AI) {
        toogle_list[playerID] = HARD_AI;
    }
    else if(toogle_list[playerID] == HARD_AI) {
        toogle_list[playerID] = NONE;
    }
}
