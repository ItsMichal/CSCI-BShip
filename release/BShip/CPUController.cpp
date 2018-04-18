//
// Created by Michal Bodzianowski on 3/1/18.
//

#include "CPUController.h"

using namespace std;

//"Default" Constructor
CPUController::CPUController(BShipGrid *_myGrid, BShipGrid *_enemyGrid, int _difficulty) : BShipController(_myGrid, _enemyGrid) {
    difficulty = _difficulty; //remember difficulty
    srand(time(nullptr)); //set random seed
}

//Returns the current difficulty of the game.
int CPUController::getDifficulty() {
    return difficulty;
}

//Returns false on invalid input, thereby also ignoring it.
bool CPUController::setDifficulty(int d) {
    if(d >= 0 && d < 8){
        difficulty = d;
        return true;
    }else{
        return false;
    }
}

//Gets the next coordinates, required by parent.
vector<int> CPUController::getNextCoordinates() {

    //Difficulty switch, that well, should've been a switch
    if(difficulty == 0 || difficulty == 2){ //Normal
        if(rand() % 2 == 0){
            return getRandomCoordinates();
        }else{
            return getSmartCoordinates();
        }
    }else if(difficulty == 1){ //Easy
        return getRandomCoordinates();
    }else if(difficulty == 3){ //Hard
        return getSmartCoordinates();
    }else if(difficulty == 4){ //Semi-Pro
        if(rand() % 4 == 0){
            return getCheaterCoordinates();
        }else{
            return getSmartCoordinates();
        }
    }else if(difficulty == 5){ //Pro
        if(rand() % 3 == 0){
            return getCheaterCoordinates();
        }else{
            return getSmartCoordinates();
        }
    }else if(difficulty = 6){ //World Champ
        if(rand() % 2 == 0){
            return getCheaterCoordinates();
        }else{
            return getSmartCoordinates();
        }
    }else{ //Cheater
        return getCheaterCoordinates();
    }
}

//Gets 2 random coordinates, rather randomly.
//Should be rewritten to avoid long lockups
//when only a few spots are left...actually let me
//do that real quick...

//Alright did it. Now starts at a random point in the grid,
//and then iterates through the rest of it until it reaches
//an empty spot. Still random, but does not get hooked up.
vector<int> CPUController::getRandomCoordinates() {
    vector<int> tcoords(2,0);
    vector<int> fcoords(2,-1);
    //Get a random starting point.
    int startx = (rand() % (enemyGrid->getSize()));
    int starty = (rand() % (enemyGrid->getSize()));

    int gSize = enemyGrid->getSize();
    bool valid = false;
    for(int i = startx; i < gSize; i++){
        tcoords[0] = i;
        for(int j = starty; j < gSize; j++){
            tcoords[1] = j;
            if(!(enemyGrid->getSpotAtCoords(tcoords).hit)){
                fcoords[0] = i;
                fcoords[1] = j;
                return fcoords;
            }

            if(j == gSize-1){
                j = -1;
            }
            if(j == starty-1) {
                j = gSize;
            }

        }
        if(i == gSize-1){
            i = -1;
        }
        if(i == startx-1) {
            i = gSize;
        }
    }


    //OLD DUMB CODE FOR YOUR PLEASURE
    /*bool valid = false;
    while(!valid){
        tcoords[0] = (rand() % (enemyGrid->getSize()))+1;
        tcoords[1] = (rand() % (enemyGrid->getSize()))+1;

        if(!enemyGrid->getSpotAtCoords(tcoords).hit){
            valid = true;
        }
    }
    */
    return fcoords;
}


//By basic logic, if you have hit but not sunken a ship, that must mean one of the adjacent tiles
//must contain another part of said ship. This code establishes that logic which allows the CPU
//to use that tactic. If there are no "half-sunken" ships, it will randomly fire until it achieves
//a hit.
vector<int> CPUController::getSmartCoordinates() {
    vector<int> tcoords(2,0); //temp coords
    const int gsize = enemyGrid->getSize(); //grid size

    bool smart = false; //did it do the smart thing?

    vector<int> lcoords(2,0); //probably not necessary, but oh well (lookup coords)

    for(int i = 0; i < gsize; i++){
        lcoords[0] = i;
        for(int j = 0; j < gsize; j++){
            lcoords[1] = j;

            //If the CPU has previously hit, not missed, and the ship is still alive then...

            if(enemyGrid->getSpotAtCoords(lcoords).hit && !enemyGrid->getSpotAtCoords(lcoords).empty && !enemyGrid->getShipAtCoords(lcoords)->isSunk()){
                for(int g = 0; g < 4; g++){
                    int alty = (g == 0) ? i+1 : (g == 1) ? i-1 : i;
                    int altx = (g == 2) ? j+1 : (g == 3) ? j-1 : j;
                    tcoords[0] = alty;
                    tcoords[1] = altx;
                    if (altx >= 0 && altx < gsize && alty >= 0 && alty < gsize){ //make sure its inbounds

                        if(!enemyGrid->getSpotAtCoords(tcoords).hit){
                            //lets do it!
                            smart = true;
                            return tcoords;
                        }
                    }

                }
            }

        }
    }


    return getRandomCoordinates();

}

//Blatantly looks up the other players board and picks a guaranteed target
vector<int> CPUController::getCheaterCoordinates() {
    vector<int> tcoords(2,0); //temp coords
    const int gsize = enemyGrid->getSize(); //grid size

    for(int i = 0; i < gsize; i++){
        tcoords[0] = i;
        for(int j = 0; j < gsize; j++){
            tcoords[1] = j;
            try {
                bool hex = enemyGrid->getSpotAtCoords(tcoords).empty;
                bool hex2 = enemyGrid->getSpotAtCoords(tcoords).hit;
            }catch (...){
                cout << "hmmm" << endl;
            }
            //Not empty? Isn't already hit? EZPZ.
            if(!(enemyGrid->getSpotAtCoords(tcoords).empty) && !(enemyGrid->getSpotAtCoords(tcoords).hit)){
                return tcoords;
            }
        }
    }

    throw new string("Out of...moves?");
}