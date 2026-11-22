#include "ScreenState.h"

#include <iostream>

using namespace render;

render::ScreenState::ScreenState(sf::RenderWindow & window) : window(window) {

}

render::ScreenState::~ScreenState() = default;

void ScreenState::addCompleteSprite(const std::string &filename, sf::Vector2f position, sf::Vector2f scale, bool is_background, const std::string & name_id) {
    completeSprite cd;
    cd.respective_texture = std::make_unique<sf::Texture>(filename);
    cd.sprite = std::make_unique<sf::Sprite>(sf::Sprite(*cd.respective_texture)); //0, 0, 800, 600
    cd.name_id = name_id;
    cd.sprite->setPosition(position);
    cd.sprite->setScale(scale);
    cd.is_background = is_background;
    list_complete_sprites.push_back(std::move(cd));
}


void ScreenState::addCompleteText(sf::Text text, sf::Color color, sf::Vector2f position, bool is_background) {
    completeText cdt;
    text.setFillColor(color);
    text.setPosition(position);
    cdt.text = std::make_unique<sf::Text>(text);
    cdt.is_background = is_background;
    list_complete_texts.push_back(std::move(cdt));
}

void ScreenState::eraseNonBackgroundDrawables () {
    //Sprites
    for (auto it = list_complete_sprites.begin(); it != list_complete_sprites.end(); ) {
        if (!it->is_background)
            it = list_complete_sprites.erase(it);
        else
            ++it;
    }

    //Texts
    for (auto it = list_complete_texts.begin(); it != list_complete_texts.end(); ) {
        if (!it->is_background)
            it = list_complete_texts.erase(it);
        else
            ++it;

    }
}
void ScreenState::eraseAllDrawables () {
    //Sprites
    for (auto it = list_complete_sprites.begin(); it != list_complete_sprites.end();) {
        list_complete_sprites.erase(it);
    }

    //Texts
    for (auto it = list_complete_texts.begin(); it != list_complete_texts.end();) {
        list_complete_texts.erase(it);
    }
}

