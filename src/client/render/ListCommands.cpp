#include "ListCommands.h"
#include "Command.h"
#include <iostream>
#include <shared_mutex>

using namespace render;

ListCommands::ListCommands(std::mutex & mutex) : mutex(mutex) {
    //rules = RulesAPI();
}

ListCommands::~ListCommands() {
    std::cout <<"ListCommands destroyed"<< std::endl;

}

const std::vector<std::unique_ptr<Command>> & ListCommands::getListCommands()  {
    return list_commands;
}

void ListCommands::exeAll () {
    for (auto & command : list_commands) {
        command->exec();
    }
    list_commands.clear(); //On vide les commandes exécutées
}

void ListCommands::add (std::unique_ptr<Command> command) {
    list_commands.push_back(std::move(command));
}


