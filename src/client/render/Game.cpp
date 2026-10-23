#include <SFML/Window/Event.hpp>
#include "Game.h"

#include <iostream>

#include "render/TitleScreen.h"
#include <memory>

#include "ArialFont.h"
#include "render/completeSprite.h"
#include "render/completeText.h"


render::Game::Game () {
    try {ArialFont::font = sf::Font("assets/arial.ttf");} //Revoir décla arial.ttf
    catch (...) {std::cout << "Error loading arial.ttf" << std::endl;
        throw std::runtime_error("Error loading arial.ttf");}

    window = sf::RenderWindow(sf::VideoMode(sf::Vector2u(800, 600)), "MEILLEUR JEU",sf::Style::Default,
    sf::State::Windowed);
    //Je vais devoir push et demander aux autres de tester
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);
    current_screen_state = std::make_unique<TitleScreen>(window,board);
    board = state::Board();
    list_commands = ListCommands();
}

render::Game::~Game() {
    std::cout << std::endl << "Game destroyed" << std::endl;
}

void render::Game::run() {
    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            manageGUI_Event(*event);
        }

        if (!window.isOpen())
            break;

        manageDraw();
    }
}

void render::Game::manageGUI_Event (sf::Event &event) {
    current_screen_state->handleEvents(event);
}
void render::Game::manageDraw() {
    window.clear();
    const std::vector<completeSprite> & sprites = current_screen_state->getSprites();
    for(int i=0;i<sprites.size();i++) {
        if(sprites.at(i).visible == true)
            window.draw(*(sprites.at(i).sprite));
    }

    for(const completeText & complete_text : current_screen_state->getTexts()){
        if(complete_text.visible == true)
            window.draw(*complete_text.text);
    }
    window.display();
}
/// lecture du champ de current_State de New ScreenStateQuerried
//void render::Game::setNewScreenState ();