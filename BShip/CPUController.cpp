//
// Created by Michal Bodzianowski on 3/1/18.
//

#include "CPUController.h"

using namespace std;
//"Default" Constructor
CPUController::CPUController(BShipGrid *_myGrid, BShipGrid *_enemyGrid, int _difficulty) : BShipController(_myGrid, _enemyGrid) {
    difficulty = _difficulty;
    srand(time(nullptr)); //set random seed
}

//Returns the current difficulty of the game.
int CPUController::getDifficulty() {
    return difficulty;
}

//Returns false on invalid input, thereby also ignoring it.
bool CPUController::setDifficulty(int d) {
    if(d > 0 && d < 6){
        difficulty = d;
        return true;
    }else{
        return false;
    }
}

virtual vector<int> CPUController::getNextCoordinates() final {
    if(difficulty == 0 || difficulty == 2){
        if(rand() % 2 == 0){
            return getRandomCoordinates();
        }else{
            return getSmartCoordinates();
        }
    }else if(difficulty == 1){
        return getRandomCoordinates();
    }else if(difficulty == 3){
        return getSmartCoordinates();
    }else if(difficulty == 4){
        if(rand() % 4 == 0){
            return getCheaterCoordinates();
        }else{
            return getSmartCoordinates();
        }
    }else{
        return getCheaterCoordinates();
    }
}

vector<int> CPUController::getRandomCoordinates() {
    vector<int> tcoords(2,0);

    bool valid = false;
    while(!valid){
        tcoords[0] = rand() % enemyGrid.getSize()-1;
        tcoords[1] = rand() % enemyGrid.getSize()-1;

        if(!enemyGrid){
            valid = true;
        }
    }

    return tcoords;
}