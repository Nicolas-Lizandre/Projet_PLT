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
    render::Game game; //Morceau de code Lizandre
    game.run();


    Board board;
    Player joueur;
    board.createPlayground();

    vector<array<int, 2>> atteignables = board.searchPath(1, 4);
    vector<array<int, 2>> atteignables2 = board.searchPath(2, 0);
    cout << "Cases atteignables depuis (1,4) : ";
    for (const auto& c : atteignables) {
        cout << "(" << c[0] << "," << c[1] << ") ";
    }
    cout << endl;
    cout << "Cases atteignables depuis (2,0) : ";
    for (const auto& c : atteignables2) {
        cout << "(" << c[0] << "," << c[1] << ") ";
    }
    cout << endl;
    cout << "It just works ! " << endl;
    client::Game game1= client::Game();
    game1.run();

    return 0;
}

// LCOV_EXCL_END