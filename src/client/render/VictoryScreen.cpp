//
// Created by nicol on 21/11/2026.
//

#include "VictoryScreen.h"
#include "ScreenState.h"
#include <iostream>
#include <state/Player.h>
#include <state/State.h>

#include "ArialFont.h"
#include "GameModeScreen.h"

using namespace render;

#define TREASURES_TO_FIND_AT_2_PLAYERS 12


VictoryScreen::VictoryScreen(sf::RenderWindow & window, state::State & gamecore) : ScreenState(window), gamecore(gamecore) {
    std::cout << "Created VictoryScreen" << std::endl;
    /*All the Sprite are for the background so no need to erase them in drawablesUpdate
    *The following assets could be regrouped into 1*/

    //Background (red-yellow gradient)
    addCompleteSprite("../assets/Background_LABYRINTHE.png",
        {0, 0},{1.f, 1.f},true);
    //OkButtonSprite == StartButtonSprite
    addCompleteSprite("../assets/StartButtonSprite.png",
        {240, 400},{2.1f, 1.0f},true);


    //Texts
    //Winner Displaying
    int winner_player_id=-1;
    for(int i = 0; i < gamecore.getPlayers().size(); i++) {
        if(gamecore.getPlayers()[i]->getTreasureIndex() == TREASURES_TO_FIND_AT_2_PLAYERS) {
            std::cout << "Winner : " << gamecore.getPlayers()[i]->getTreasureIndex() << std::endl;
            winner_player_id = i;
        }
    }
    switch (winner_player_id) {
        case(0) : addCompleteText(sf::Text(ArialFont::font, std::string("Joueur0"), 100),
            sf::Color::Green, {225.f, 100.f}, true); break;
        case(1) : addCompleteText(sf::Text(ArialFont::font, std::string("Joueur1"), 100),
            sf::Color(255, 0, 255, 255), {225.f, 100.f}, true); break;
    }
    //Others
    addCompleteText(sf::Text(ArialFont::font, std::string("est vainqueur !"), 100),
        sf::Color::White, {75.f, 200.f}, true);
    addCompleteText(sf::Text(ArialFont::font, std::string("OK"), 50),
        sf::Color::White, {360.f, 400.f}, true);

}


void VictoryScreen::handleEvents(sf::Event &event) {
    if (const auto* mousePressed = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (mousePressed->button == sf::Mouse::Button::Left)  {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window); //à remplacer par screen.askMousePosition ! Le Screen est l'Owner du window !

            /*if (button.getGlobalBounds().contains(
                    (float)mousePos.x,
                    (float)mousePos.y))
            {*/
            if (mousePos.x >240 && mousePos.y > 400 && mousePos.x < 555 && mousePos.y < 466)
            {
                demand_screen_change = TITLESCREEN; //cet objet n'est pas utilisé
                //screen->set_current_screen_state(std::make_unique<GameModeScreen>(screen));
            }
        }
    }
}

//Le compilateur étant intelligent nous empêche d'accéder à l'attribut si on ne mets pas le 2ème const
//En effet on pourrait modifier l'addr sur un tout autre objet et briser le const
const std::vector<completeSprite>& VictoryScreen::getSprites() const {
    return list_complete_sprites;
}
//Ici & est nécessaire car si on fait la copie de la liste les smrts ptr ne seraient pas contents
const std::vector<completeText>& VictoryScreen::getTexts() const {
    return list_complete_texts;
}

ScreenStateQUERIED VictoryScreen::getDemandScreenChange () {
    return demand_screen_change;
}

void VictoryScreen::drawablesUpdate() {}


///0.1 Window fonctionnel
///0.2 Début de jeu intéractif
///0.3 Jeu jouable (mais en tournant sur un seul PC sans CPU)
///0.4 Écran de victoire/ sélection de gamemode (système de sauvegarde)
///1.0 VS_CPU (le jeu est "délivrable")
///2.0 Jouable en ligne (le jeu peut ici être considéré comme étant fini)