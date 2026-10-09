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
    Plate plate= L();
    plate.turnPlate();
    plate.showPlate();
    plate.turnPlate();
    plate.showPlate();
    Plate plate2= T();
    plate2.showPlate();
    Plate plate3= I();
    plate3.showPlate();
    plate3.turnPlate();
    plate3.showPlate();

    cout << "It does not work !" << endl;

    return 0;
}

// LCOV_EXCL_END
