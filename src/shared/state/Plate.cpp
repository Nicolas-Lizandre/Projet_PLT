//
// Created by tompi on 08/10/2026.
//

#include "Plate.h"
#include <iostream>
state::Plate::Plate(bool n, bool e, bool s, bool w): North(n), East(e), South(s), West(w) {

}

void state::Plate::turnPlate() {
    bool temp= North;
    North= West;
    West= South;
    South= East;
    East= temp;
    if (rotation ==3){
    rotation=0;}
    else {
        rotation+=1;
    }
};


void state::Plate::showPlate()
{
    const char* symbol = " ";

    if (North && South && East) {
        symbol = "├";
    }
    else if (North && South && West) {
        symbol = "┤";
    }
    else if (East && South && West) {
        symbol = "┬";
    }
    else if (North && East && West) {
        symbol = "┴";
    }
    else if (North && East) {
        symbol = "└";
    }
    else if (North && West) {
        symbol = "┘";
    }
    else if (South && East) {
        symbol = "┌";
    }
    else if (South && West) {
        symbol = "┐";
    }
    else if (North && South) {
        symbol = "|";
    }
    else if (East && West) {
        symbol = "─";
    }

    std::cout << symbol;
}
