//
// Created by Michal Bodzianowski on 3/1/18.
//

#include "BShipGame.h"

using namespace std;

BShipGame::BShipGame() {

    //I/o instanciation
    inp = &cin;
    finp = nullptr; //uh oh
    outp = &cout;

    //Grids instanciation
    auto playerOneGrid = new BShipGrid();
    auto playerTwoGrid = new BShipGrid();

    //Create Controllers
    BShipController *playerOne = new UserController(playerOneGrid, playerTwoGrid, &cin);
    BShipController *playerTwo = new CPUController(playerTwoGrid, playerOneGrid, 0);

}

BShipGame::BShipGame(istream* _inp, ifstream* _finp, ostream* _outp = &cout, int _gridSize = 10, int _difficulty = 0) {

    //I/o instanciation
    inp = _inp;
    finp = _finp;
    outp = _outp;

    //Grids instanciation
    auto playerOneGrid = new BShipGrid(_gridSize);
    auto playerTwoGrid = new BShipGrid(_gridSize);

    //Create Controllers
    BShipController *playerOne = new UserController(playerOneGrid, playerTwoGrid, _inp);
    BShipController *playerTwo = new CPUController(playerTwoGrid, playerOneGrid, _difficulty);

}

string BShipGame::welcome() {
    return welcomeMessage;
}

string BShipGame::instructions() {
    return instructionMessage;
}

bool BShipGame::run() {
    //Check if game has already been set up.
    if(!gameSetUp){
        setup();
    }
    if(!gameRunning){
        doTurn();
    }
    if(!gameFinished){
        return false;
    }
    return true;
}

bool BShipGame::setup() {
    //Check if game has already been set up
    if(!gameSetUp){

        //SETUP PLAYER GRID FROM FIlE

        //Check if there is file input
        if(finp){
            //Read from file, pass responsibility to grid class
            try{
                playerOneGrid->file_populate(finp);
            }catch(...){
                *outp << "An unknown error occured during the file reading stage. Please check your file and try again. Randomly populating instead." << endl;
                int gSize = playerOneGrid->getSize();
                delete playerOneGrid;
                auto playerOneGrid = new BShipGrid(gSize);
                playerOneGrid->rand_populate();
            }
        }else{
            *outp << "No file specified. Randomly populating your grid instead." << endl;
            playerOneGrid->rand_populate();
        }

        //SETUP CPU GRID
        playerTwoGrid->rand_populate();

        //DISPLAY GRIDS
        *outp << "-CPU's Grid:-" << endl;
        *outp << playerTwoGrid->displayGridNoShips() << endl;
        *outp << "-Your Grid:-" << endl;
        *outp << playerOneGrid->displayFullGrid() << endl;
        
    }
}