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
    board.turnMasterPlate();
    board.insertPlate(0,5);
    board.showBoard();
    printf("\n");
    board.turnMasterPlate();
    board.insertPlate(6,3);
    board.showBoard();
    printf("\n");
    board.turnMasterPlate();
    board.insertPlate(2,0);
    board.showBoard();
    printf("\n");
    board.turnMasterPlate();
    board.insertPlate(3,6);
    board.showBoard();
    cout << "It just works ! " << endl;

    return 0;
}

// LCOV_EXCL_END
