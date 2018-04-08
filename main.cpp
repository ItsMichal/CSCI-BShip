#include <fstream>
#include <iostream>
#include <exception>
#include "BShip/BShipGame.h"
using namespace std;
int main() {
    //Create file
    ifstream hecc ("ship_placement.csv");
    try {
        BShipGame* game = new BShipGame(&cin, &hecc, &cout, 5);
        game->runForever();
    }catch (string const* e){
        cout << endl << "Exception - " << *e << endl;
        return 1;
    }
    return 0;
}