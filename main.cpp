#include <fstream>
#include <iostream>
#include <exception>
#include "BShip/BShipGame.h"
using namespace std;
int main() {
    //std::cout << "Hello, World!" << std::endl;


    ifstream hecc ("ship_placement.csv");
    BShipGame* game = new BShipGame(&cin, &hecc, &cout);
    try {
        game->runForever();
    }catch (string const* e){
        cout << endl << "Exception - " << *e << endl;
        return 1;
    }

    //BShipGrid* grid = new BShipGrid();
    //grid->file_populate(&hecc);
    //cout << grid->displayFullGrid() << endl;
//    try {
//        game->runForever();
//    }catch (const exception e){
//        cout << e.what() << endl;
//    }catch (string const* e){
//        cout << *e << endl;
//        cout << "Fatal Error, exiting." << endl;
//        return 0;
//    }catch (...) {
//        cout << "huh" << endl;
//    }

    //cout << bs->displayFullGrid() << endl;

    return 0;
}