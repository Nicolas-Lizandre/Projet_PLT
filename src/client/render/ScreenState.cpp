#include "ScreenState.h"

#include <iostream>

render::ScreenState::ScreenState()=default;

render::ScreenState::~ScreenState() = default;

/*sf::Texture render::ScreenState::createTextureObject (const char * str){
    auto texture =sf::Texture();
    if (!texture.loadFromFile(str)) {
        std::cout << "Error loading texture" << std::endl;
        throw std::runtime_error("Error loading texture");
    }
    return texture;
}*/
