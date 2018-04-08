//
// Created by Michal Bodzianowski on 3/1/18.
//

#ifndef BSHIP_BSHIPCONTROLLER_H
#define BSHIP_BSHIPCONTROLLER_H

#include <vector>
#include "BShipGrid.h"

using namespace std;

class BShipController {
protected:
    vector<int> nextCoordinates;
    BShipGrid* myGrid;
    BShipGrid* enemyGrid;
public:
    //Constructor
    BShipController(BShipGrid* _myGrid, BShipGrid* _enemyGrid); //No empty constructor- both grids required.

    //Logic
    virtual vector<int> getNextCoordinates() = 0;
};


#endif //BSHIP_BSHIPCONTROLLER_H

