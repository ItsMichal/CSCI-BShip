//
// Created by Michal Bodzianowski on 4/7/18.
//

#ifndef BSHIP_BSHIPGRIDSPOT_H
#define BSHIP_BSHIPGRIDSPOT_H
#include "BShip.h"

//The class that should have been a struct,
//but wasn't because structs are objectively useless.
class BShipGridSpot {
public:
    bool empty = true; //is the spot empty- its easier to check this than to check if motherShip actually has a ship.
    BShip* motherShip; //the ship that takes up said spot. is NULL until filled. this is why we have bool empty.
    bool hit = false; //checks if the spot is hit. pretty much the point of the game really.
    BShipGridSpot() {}; //a very beautiful empty default constructor...really no point of it being here...
};


#endif //BSHIP_BSHIPGRIDSPOT_H
