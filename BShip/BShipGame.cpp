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
    BShipGrid* playerOneGrid = new BShipGrid(gridSize);
    BShipGrid* playerTwoGrid = new BShipGrid(gridSize);

    //Create Controllers
    CPUController user(playerOneGrid, playerTwoGrid, 0);
    CPUController cpu(playerTwoGrid, playerOneGrid, 0);
    BShipController *playerOne = &user;
    BShipController *playerTwo = &cpu;

}

BShipGame::BShipGame(istream* _inp, ifstream* _finp, ostream* _outp, int _gridSize, int _difficulty) {

    //I/o instanciation
    inp = _inp;
    ifstream hecc("ship_placement.csv");
    finp = &hecc;
    outp = _outp;

    //Grids instanciation
    BShipGrid* playerOneGrid = new BShipGrid(_gridSize);
    BShipGrid* playerTwoGrid = new BShipGrid(_gridSize);

    //Create Controllers
    CPUController user(playerOneGrid, playerTwoGrid, 5);
    CPUController cpu(playerTwoGrid, playerOneGrid, 1);
    BShipController *playerOne = &user;
    BShipController *playerTwo = &cpu;

    gridSize = _gridSize;
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
    if(!gameFinished){
        doTurn();
    }else{
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
            } catch (exception e){
                cout << e.what() << endl;
            }catch(string const* e){
                //*outp << "An unknown error occured during the file reading stage. Please check your file and try again. Randomly populating instead." << endl;

                *outp << *e << endl;
                int gSize = playerOneGrid->getSize();
                delete playerOneGrid;
                BShipGrid* playerOneGrid = new BShipGrid(gSize);
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

        //SETUP COMPLETE
        gameSetUp = true;

        return true;
    }
    return false;
}

void BShipGame::doTurn() {
    if(!gameFinished){
        //Increment turn counter
        turnNumber++;

        //Context switches for announcements at end
        bool p1sunkship = false, p2sunkship = false, p1hitship = false, p2hitship = false;

        //Get next coordinates of both players
        vector<int> p1coords(2,0);
        vector<int> p2coords(2,0);

        p1coords = playerOne->getNextCoordinates();
        p2coords = playerTwo->getNextCoordinates();

        //Hit corresponding grids
        playerTwoGrid->hit(p1coords);
        BShip* p1ShipTarget = playerTwoGrid->getShipAtCoords(p1coords);

        //check if not nullptr
        if(p1ShipTarget){
            //set context switches
            if(p1ShipTarget->isSunk()){
                p1sunkship = true;
            }else{
                p1hitship = true;
            }
        }

        playerOneGrid->hit(p2coords);
        BShip* p2ShipTarget = playerOneGrid->getShipAtCoords(p2coords);

        //check if not nullptr
        if(p2ShipTarget){
            //set context switches
            if(p2ShipTarget->isSunk()){
                p2sunkship = true;
            }else{
                p2hitship = true;
            }
        }

        //display grids
        *outp << "-CPU's Grid:-" << endl;
        *outp << playerTwoGrid->displayGridNoShips() << endl;
        *outp << "-Your Grid:-" << endl;
        *outp << playerOneGrid->displayFullGrid() << endl;

        //display contextual info
        if(p1sunkship){
            *outp << "You sunk a " << p1ShipTarget->getName() << "!" << endl;
        }else if(p1hitship){
            *outp << "You hit an enemy ship!" << endl; //dont display ship name as it can give away size.
        }

        if(p2sunkship){
            *outp << "The CPU sunk your " << p2ShipTarget->getName() << "!" << endl;
        }else if(p2hitship){
            *outp << "The CPU hit your " << p2ShipTarget->getName() << "!" << endl; //dont display ship name as it can give away size.
        }

        //check for winner
        if(playerOneGrid->areAllSunk()){
            gameFinished = true;
            *outp << "CPU Wins!" << endl;
        }else if(playerTwoGrid->areAllSunk()){
            gameFinished = true;
            *outp << "You win!" << endl;
        }

    }
}

bool BShipGame::runForever() {
    if(gameFinished)
        return false;
    while(!gameFinished){
        this->run();
    }
    return true;
}