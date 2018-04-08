#include <fstream>
#include <iostream>
#include <exception>
#include "BShip/BShipGrid.h"
using namespace std;
int main() {
    //std::cout << "Hello, World!" << std::endl;

    BShipGrid* bs = new BShipGrid(10);
    ifstream hecc ("ship_placement.csv");
    try {
        bs->file_populate(&hecc);
    }catch (const exception e){
        cout << e.what() << endl;
    }catch (string const* e){
        cout << *e << endl;
        cout << "Fatal Error, exiting." << endl;
    }catch (...) {
        cout << "huh" << endl;
    }

    return 0;
}