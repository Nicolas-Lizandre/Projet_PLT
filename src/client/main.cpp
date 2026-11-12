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
    //render::Game game; //Morceau de code Lizandre
    //game.run();


    Board board;
    Player joueur;
    //board.createPlayground();
    board.display();
    board.save("test.json");
    
    vector<array<int, 2>> atteignables = board.searchPath(0, 0);
    /*
    vector<array<int, 2>> atteignables2 = board.searchPath(2, 0);
    cout << "Cases atteignables depuis (1,4) : ";
    for (const auto& c : atteignables) {
        cout << "(" << c[0] << "," << c[1] << ") ";
    }
    cout << endl;
    */
    cout << "Cases atteignables depuis (0,0) : ";
    for (const auto& c : atteignables) {
        cout << "(" << c[0] << "," << c[1] << ") ";
    }
    cout << endl;
    cout << "It just works ! " << endl;
    board.insertPlate(0,1);
    board.display();
    cout << endl;
    cout << "Loading :  " << endl;
    board.load("test.json");
    board.display();
    /*
    client::Game game1= client::Game();
    game1.run();
    */

    return 0;
}

// LCOV_EXCL_END