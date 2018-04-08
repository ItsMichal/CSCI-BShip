//
// Created by Michal Bodzianowski on 3/1/18.
//

#include "BShipController.h"

//Simple setup for BShipController abstractish class
BShipController::BShipController(BShipGrid *_myGrid, BShipGrid *_enemyGrid) {
    myGrid = _myGrid;
    enemyGrid = _enemyGrid;
    nextCoordinates(2,0);
}