//
// Created by Michal Bodzianowski on 3/1/18.
//

#include "BShipGame.h"

using namespace std;

BShipGame::BShipGame() {

    //I/o instanciation
    inp = &cin;
    finp = nullptr; //uh oh
    outp = &cout;

    //Grids instanciation
    BShipGrid playerOneGrid(*this);
    BShipGrid playerTwoGrid(*this);
}