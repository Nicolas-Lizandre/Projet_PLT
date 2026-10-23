#include "render/RulesAPI.h"

#include <iostream>

render::RulesAPI::RulesAPI () {

}

render::RulesAPI::~RulesAPI () {
    std::cout <<"RulesAPI destroyed"<< std::endl;
}
void verify_command_validity (std::string command);
