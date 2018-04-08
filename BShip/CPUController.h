//
// Created by Michal Bodzianowski on 3/1/18.
//

#ifndef BSHIP_CPUCONTROLLER_H
#define BSHIP_CPUCONTROLLER_H

#include <iostream>
#include <random>
#include <ctime>
#include "BShipController.h"

class CPUController : public BShipController {
private:
    int difficulty = 0; //0 = normal (default), 1 = Easy (100% random), 2 = Normal (50% random, 50% smart), 3 = hard (100% smart), 4 = Pro (75% smart, 25% cheater), 5 = Cheater (100% cheater)
public:
    CPUController(BShipGrid* _myGrid, BShipGrid* _enemyGrid, int _difficulty); //Constructor
    virtual vector<int> getNextCoordinates() final; //get the next move

    vector<int> getRandomCoordinates();
    vector<int> getSmartCoordinates();
    vector<int> getCheaterCoordinates();

    int getDifficulty();
    bool setDifficulty(int d);
};


#endif //BSHIP_CPUCONTROLLER_H
