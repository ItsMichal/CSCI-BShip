//
// Created by Michal Bodzianowski on 3/1/18.
//

#ifndef BSHIP_BSHIP_H
#define BSHIP_BSHIP_H

#include <string>
#include <vector>
#include "BShipGrid.h"

using namespace std;

class BShip {
private:
    //Mother grid object
    BShipGrid grid;

    //Is sunk?
    bool sunk = false;

    //size (min = 2, max = 5)
    int size;

    //is it horizontally aligned? (if not, then it is vertical)
    bool horizontal;

    //starting coordinates in the grid
    vector<int> coords;

    //vector of ship parts
    vector<BShipGridSpot> shipLine;

    //name
    string myName;

    //name database
    //const string nameDB[5] = {"Destroyer", "Submarine", "Cruiser", "Battleship", "Carrier"};

public:
    //Constructor
    BShip(BShipGrid _grid, int name, int _size, bool horizontal, vector<int> coords);

    //Setters
    void sink();

    //Getters
    bool isSunk();
    bool isHorizontal();
    vector<BShipGridSpot> getGridSpots();
};


#endif //BSHIP_BSHIP_H
