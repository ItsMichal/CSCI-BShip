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
#include <ctime>
#include <random>

#include "BShipGridSpot.h"
#include "BShip.h"

class BShipGrid {
private:

    //The Game
    //BShipGame myController;

    //2D Vector to be used as grid
    int size; //side length of grid, maxes out at 20, minimum is 6, default is 10
    vector<vector<BShipGridSpot>> grid;
    vector<BShip> ships;

    bool validate(BShip* s);
    bool areSame(string x, string y);
    int coordFromLetter(char x);
    void addShipToGrid(BShip* s);

public:
    BShipGrid(int _size = 10);

    void file_populate(ifstream* finp);
    void rand_populate();
//    bool isValid();
//    bool isCoordinateInBounds(vector<int> coord);
//    bool isShipInBounds(vector<int> coord, int size, bool isHorizontal);
    string displayFullGrid();
    string displayGridNoShips();
    bool areAllSunk();

    bool hit(vector<int> coords);
    BShip* getShipAtCoords(vector<int> coords);
    BShipGridSpot getSpotAtCoords(vector<int> coords);

    int getSize();
};

//Include struct for GridSpot here


#endif //BSHIP_BSHIPGRID_H
