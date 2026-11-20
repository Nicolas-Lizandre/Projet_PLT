#include <iostream>

// The following lines are here to check that SFML is installed and working
#include <thread>
#include <client/GameWithRender.h>
#include <SFML/Graphics.hpp>
// LCOV_EXCL_START
void testSFML() {
    sf::Texture texture;
}
// end of test SFML

#include <state.h>
#include <client.h>
using namespace std;
using namespace state;
using namespace sf;
using namespace render;
using namespace client;

int main()
{
    // //Morceau de code Lizandre
    // GameWithRender game;
    // game.run();

    //Morceau de code de Fayçal
    client::Game game1= client::Game();
    game1.run();

    return 0;

}

// LCOV_EXCL_END