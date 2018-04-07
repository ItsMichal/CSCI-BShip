//
// Created by Michal Bodzianowski on 3/1/18.
//

#ifndef BSHIP_CPUCONTROLLER_H
#define BSHIP_CPUCONTROLLER_H

#include <iostream>
#include "BShipController.h"

class CPUController : public BShipController {
private:
    int difficulty = 0; //0 = normal (default), 1 = easy (100% random), 2 = normal (50% random, 50% smart), 3 = hard (100% smart), 4 = cheater (100% on-target)
public:
    CPUController(BShipGrid _myGrid, BShipGrid _enemyGrid, int _difficulty); //Constructor
    vector<int> getNextMove(); //get the next move
};


#endif //BSHIP_CPUCONTROLLER_H
