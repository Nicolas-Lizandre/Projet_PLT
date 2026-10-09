#include <iostream>

// The following lines are here to check that SFML is installed and working
#include <SFML/Graphics.hpp>
// LCOV_EXCL_START
void testSFML() {
    sf::Texture texture;
}
// end of test SFML

#include <state.h>

using namespace std;
using namespace state;

int main()
{
    Board board;
    board.createPlayground();
    board.showBoard();
    printf("\n");
    board.insertPlate(0,5);
    board.insertPlate(0,5);
    board.showBoard();
    cout << "It does not work !" << endl;

    return 0;
}

// LCOV_EXCL_END
