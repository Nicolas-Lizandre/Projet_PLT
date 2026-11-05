#include "ListCommands.h"

#include <iostream>

render::ListCommands::ListCommands() {
    rules = RulesAPI();
}

render::ListCommands::~ListCommands() {
    std::cout <<"ListCommands destroyed"<< std::endl;

}

void render::ListCommands::add(std::string command) {
    std::cout << command << " added" << std::endl;
}

void render::ListCommands::exeAll () {

}


