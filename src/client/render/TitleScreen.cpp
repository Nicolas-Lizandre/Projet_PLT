
#include "TitleScreen.h"
#include "ScreenState.h"
#include <iostream>

#include "ArialFont.h"

render::TitleScreen::TitleScreen(sf::RenderWindow & window, state::Board & board) : window(window), board(board) {
    std::cout << "Created TitleScreen" << std::endl;
    //Mise en place des textures - Ordre à respecter
    // Gradient Jaune <-> Orange du background

    completeSprite cd;
    //sf::Sprite sprite;

    cd.respective_texture = std::make_unique<sf::Texture>("assets/Background_LABYRINTHE.png");
    cd.sprite = std::make_unique<sf::Sprite>(sf::Sprite(*cd.respective_texture)); //0, 0, 800, 600
    cd.sprite->setPosition(sf::Vector2f(0, 0));
    cd.sprite->setScale(sf::Vector2f(1.f, 1.f));
    list_complete_sprites.push_back(std::move(cd));

    // Easter Egg Pokemon
    /*
    cd.respective_texture = std::make_unique<sf::Texture>(
        ScreenState::createTextureObject("C:/Users/nicol/Downloads/image_pokedex-20260911/pokemon/9.png"));
    cd.sprite = std::make_unique<sf::Sprite>(*cd.respective_texture, sf::IntRect()); //0, 0, 800, 600
    cd.sprite->setPosition(sf::Vector2f(0, 256));
    cd.sprite->setScale(sf::Vector2f(1.f, 1.f));
    list_complete_sprites.push_back(std::move(cd));
    */



    // Logo Labyrinthe
    cd.respective_texture = std::make_unique<sf::Texture>("assets/Logo_LABYRINTHE.png");
    cd.sprite = std::make_unique<sf::Sprite>(*cd.respective_texture); //0, 0, 1200, 600
    cd.sprite->setPosition(sf::Vector2f(-80, 0));
    cd.sprite->setScale(sf::Vector2f(0.8f, 0.8f));
    list_complete_sprites.push_back(std::move(cd));

    // Bouton Commencer
    cd.respective_texture = std::make_unique<sf::Texture>("assets/Bouton_Commencer_Labyrinthe.png");
    cd.sprite = std::make_unique<sf::Sprite>(*cd.respective_texture); //0, 0, 150, 66
    cd.sprite->setPosition(sf::Vector2f(240, 400));
    cd.sprite->setScale(sf::Vector2f(2.1f, 1.0f));
    list_complete_sprites.push_back(std::move(cd));



    completeText cdt;


    sf::Text button_commencer_text = sf::Text(ArialFont::font, std::string("Commencer"), 50);
    button_commencer_text.setFillColor(sf::Color::White);
    button_commencer_text.setPosition({260.f, 400.f});
    cdt.text = std::make_unique<sf::Text>(button_commencer_text);
    list_complete_texts.push_back(std::move(cdt));

    sf::Text versionBuild = sf::Text(ArialFont::font, std::string("v0.1"), 20);
    versionBuild.setFillColor(sf::Color::Black);
    versionBuild.setPosition(sf::Vector2f(20, 570));
    cdt.text = std::make_unique<sf::Text>(versionBuild);
    list_complete_texts.push_back(std::move(cdt));

    sf::Text auteur1 = sf::Text(ArialFont::font, std::string("AUTEURS : Faycal BOUIDDOUH, FADE Lizandre,"), 20);
    auteur1.setFillColor(sf::Color::Black);
    auteur1.setPosition(sf::Vector2f(330, 550));
    cdt.text = std::make_unique<sf::Text>(auteur1);
    list_complete_texts.push_back(std::move(cdt));

    sf::Text auteur2 = sf::Text(ArialFont::font, std::string("   Mohammed-amine GHERRAS, Tom PICQUART"), 20);
    auteur2.setFillColor(sf::Color::Black);
    auteur2.setPosition(sf::Vector2f(330, 570));
    cdt.text = std::make_unique<sf::Text>(auteur2);
    list_complete_texts.push_back(std::move(cdt));
}


void render::TitleScreen::handleEvents(sf::Event &event) {
    //screen_state = new TitleScreen(screen); //new permet de générer un pointeur
    if (const auto* mousePressed =
                event.getIf<sf::Event::MouseButtonPressed>())
    {
        if (mousePressed->button == sf::Mouse::Button::Left)
        {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window); //à remplacer par screen.askMousePosition ! Le Screen est l'Owner du window !

            /*if (button.getGlobalBounds().contains(
                    (float)mousePos.x,
                    (float)mousePos.y))
            {*/
            if (mousePos.x >240 && mousePos.y > 400 && mousePos.x < 555 && mousePos.y < 466)
                {
                std::cout << "Zone clique Titlescreen !" << std::endl;
                //screen->set_current_screen_state(std::make_unique<GameModeScreen>(screen));
            }
        }
    }
}

//Le compilateur étant intelligent nous empêche d'accéder à l'attribut si on ne mets pas le 2ème const
//En effet on pourrait modifier l'addr sur un tout autre objet et briser le const
const std::vector<render::completeSprite>& render::TitleScreen::getSprites() const {
    return list_complete_sprites;
}
//Ici & est nécessaire car si on fait la copie de la liste les smrts ptr ne seraient pas contents
const std::vector<render::completeText>& render::TitleScreen::getTexts() const {
    return list_complete_texts;
}
