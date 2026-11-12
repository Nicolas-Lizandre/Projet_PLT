#include <iostream>

// The following lines are here to check that SFML is installed and working
#include <render/Game.h>
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

int main()
{

    client::Game game= client::Game();
    game.run();

    return 0;
}

// LCOV_EXCL_END