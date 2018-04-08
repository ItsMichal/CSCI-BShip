//
// Created by Michal Bodzianowski on 3/1/18.
//

#ifndef BSHIP_BSHIPGRID_H
#define BSHIP_BSHIPGRID_H

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
//#include "BShip.h"
#include "BShipGridSpot.h"


class BShipGrid {
private:

    //The Game
    //BShipGame myController;

    //2D Vector to be used as grid
    int size; //side length of grid, maxes out at 20, minimum is 6, default is 10
    vector<vector<BShipGridSpot>> vectorGrid;
    vector<BShip> ships;

    bool checkCollision();
    bool areSame(string x, string y);
    int coordFromLetter(char x);

public:
    BShipGrid(int _size = 10);

    void file_populate(ifstream* finp);
    void rand_populate();
    bool isValid();
    bool isCoordinateInBounds(vector<int> coord);
    bool isShipInBounds(vector<int> coord, int size, bool isHorizontal);
    string displayFullGrid();
    string displayGridNoShips();
    bool areAllSunk();

    //BShip* hit(vector<int> coords);

    int getSize();
};

//Include struct for GridSpot here


#endif //BSHIP_BSHIPGRID_H
