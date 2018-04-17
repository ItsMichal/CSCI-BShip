//
// Created by Michal Bodzianowski on 3/1/18.
//

#ifndef BSHIP_USERCONTROLLER_H
#define BSHIP_USERCONTROLLER_H

#include <iostream>
#include <string>
#include "BShipController.h"

//Gives the user control. What a concept.
class UserController : public BShipController {
private:
    istream* inp; //input to parse from user
    ostream* outp; //input to parse from user
    int coordFromLetter(char x);
public:
    UserController(BShipGrid* _myGrid, BShipGrid* _enemyGrid, istream* _inp = &cin, ostream* _outp = &cout); //Constructor
    virtual vector<int> getNextCoordinates() final; //get the next move
};


#endif //BSHIP_USERCONTROLLER_H
