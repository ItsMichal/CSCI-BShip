//
// Created by Michal Bodzianowski on 3/1/18.
//

#ifndef BSHIP_BSHIPGRID_H
#define BSHIP_BSHIPGRID_H

#include <string>
#include <iostream>
#include <vector>
#include "BShipGame.h"

struct BShipGridSpot;

class BShipGrid {
private:

    //The Game
    BShipGame myController;

    //2D Vector to be used as grid
    int size = 10; //side length of grid, maxes out at 20, minimum is 6, default is 10
    vector<vector<BShipGridSpot>> vectorGrid;
    vector<BShip> ships;

public:
    BShipGrid(BShipGame _myGame);
    BShipGrid(BShipGame _myGame, int _size);

    void file_populate(istream inp);
    void rand_populate();
    bool isValid();
    bool isCoordinateInBounds(vector<int> coord);
    bool isShipInBounds(vector<int> coord, int size, bool isHorizontal);
    string displayFullGrid();
    string displayGridNoShips();
    bool areAllSunk();
};

//Include struct for GridSpot here

#include "BShip.h"

struct BShipGridSpot {
    bool empty;
    BShip motherShip;
    bool hit;
};

#endif //BSHIP_BSHIPGRID_H
