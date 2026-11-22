//
// Created by nicol on 05/11/2026.
//
#include "GameModeScreen.h"

#include "GameModeScreen.h"

#include <iostream>

#include "ArialFont.h"

using namespace render;


GameModeScreen::GameModeScreen (sf::RenderWindow & window) : ScreenState(window) {
    completeText cdt;


    sf::Text button_commencer_text = sf::Text(ArialFont::font, std::string("Commencer"), 50);
    button_commencer_text.setFillColor(sf::Color::White);
    button_commencer_text.setPosition({260.f, 400.f});
    cdt.text = std::make_unique<sf::Text>(button_commencer_text);
    list_complete_texts.push_back(std::move(cdt));

}
void GameModeScreen::handleEvents (sf::Event & event) {
    if (const auto* mousePressed = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (mousePressed->button == sf::Mouse::Button::Left)
        {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window); //à remplacer par screen.askMousePosition ! Le Screen est l'Owner du window !

            /*if (button.getGlobalBounds().contains(
                    (float)mousePos.x,
                    (float)mousePos.y))
            {*/
            if (mousePos.x >240 && mousePos.y > 400 && mousePos.x < 555 && mousePos.y < 466)
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

}
