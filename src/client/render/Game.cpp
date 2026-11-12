#include <SFML/Window/Event.hpp>
#include "Game.h"

#include <iostream>

#include "render/TitleScreen.h"
#include <memory>

#include "ArialFont.h"
#include "GameModeScreen.h"
#include "GameScreen.h"
#include "render/completeSprite.h"
#include "render/completeText.h"


render::Game::Game () : list_commands(ListCommands()){ //La liste d'init est bien car elle permet d'éviter les copies
    try {ArialFont::font = sf::Font("../assets/arial.ttf");} //Revoir décla arial.ttf
    catch (...) {std::cout << "Error loading arial.ttf" << std::endl;
        throw std::runtime_error("Error loading arial.ttf");}

    window = sf::RenderWindow(sf::VideoMode(sf::Vector2u(800, 600)), "MEILLEUR JEU",sf::Style::Default,
    sf::State::Windowed);
    //Je vais devoir push et demander aux autres de tester
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);
    current_screen_state = std::make_unique<TitleScreen>(window);
    board = state::Board();
    board.createPlayground();
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
        seekDemandNewScreen();
        execQueriedCommands();
    }
}

void render::Game::manageGUI_Event (sf::Event &event) {
    current_screen_state->handleEvents(event);
}
void render::Game::manageDraw() {
    current_screen_state->drawablesUpdate();  //Peut se mettre dans le run ? - Mettre une condition pour optimiser
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
void render::Game::seekDemandNewScreen () {
    if(current_screen_state->getDemandScreenChange() != NO_QUERY) {
        if(current_screen_state->getDemandScreenChange() == TITLESCREEN) {
            current_screen_state = std::make_unique<TitleScreen>(window);
        }
        else if(current_screen_state->getDemandScreenChange() == GAMEMODESCREEN) {
            current_screen_state = std::make_unique<GameModeScreen>(window);
        }
        else if(current_screen_state->getDemandScreenChange() == GAMESCREEN) {
            current_screen_state = std::make_unique<GameScreen>(window,board,list_commands);
        }

    }

}

void render::Game::execQueriedCommands() {
    list_commands.exeAll();
}
