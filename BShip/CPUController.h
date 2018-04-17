//
// Created by Michal Bodzianowski on 3/1/18.
//

#ifndef BSHIP_CPUCONTROLLER_H
#define BSHIP_CPUCONTROLLER_H

#include <iostream>
#include <random>
#include <ctime>
#include "BShipController.h"

//Gives the CPU control...well I say CPU but it could be considered a very dumb AI I guess. ...not really.
class CPUController : public BShipController {
private:
    int difficulty = 0; //0 = normal (default), 1 = Easy (100% random), 2 = Normal (50% random, 50% smart), 3 = Hard (100% smart), 4 = Semi-Pro (75% smart, 25% cheater), 5 = Pro (66.6% smart, 33.3% cheater), 6 = World Champion (50% smart, 50% cheater), 7 = Cheater (100% cheater)
public:
    CPUController(BShipGrid* _myGrid, BShipGrid* _enemyGrid, int _difficulty); //Constructor
    virtual vector<int> getNextCoordinates() final; //get the next move

    vector<int> getRandomCoordinates(); //gets a random pair of coordinates
    vector<int> getSmartCoordinates(); //gets a somewhat less random pair of coordinates
    vector<int> getCheaterCoordinates(); //gets a blatantly unfair random pair of coordinates

    //getters/setters...probably the only class here with a full set.
    int getDifficulty();
    bool setDifficulty(int d);
};


#endif //BSHIP_CPUCONTROLLER_H
