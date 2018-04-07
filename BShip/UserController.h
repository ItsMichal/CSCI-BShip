//
// Created by Michal Bodzianowski on 3/1/18.
//

#ifndef BSHIP_USERCONTROLLER_H
#define BSHIP_USERCONTROLLER_H

#include <iostream>
#include "BShipController.h"

class UserController : public BShipController {
private:
    istream inp; //input to parse from user
public:
    UserController(BShipGrid _myGrid, BShipGrid _enemyGrid, istream _inp); //Constructor
    vector<int> getNextMove(); //get the next move
};


#endif //BSHIP_USERCONTROLLER_H
