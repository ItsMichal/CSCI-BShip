//
// Created by Michal Bodzianowski on 4/7/18.
//

#ifndef BSHIP_BSHIPGRIDSPOT_H
#define BSHIP_BSHIPGRIDSPOT_H
#include "BShip.h"

class BShipGridSpot {
public:
    bool empty = true;
    BShip* motherShip;
    bool hit = false;
    BShipGridSpot() {};
};


#endif //BSHIP_BSHIPGRIDSPOT_H
