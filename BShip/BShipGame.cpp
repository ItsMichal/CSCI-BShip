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
    playerOneGrid = new BShipGrid(gridSize);
    playerTwoGrid = new BShipGrid(gridSize);

    //Create Controllers
    playerOne = new  CPUController(playerOneGrid, playerTwoGrid, 0);
    playerTwo = new CPUController(playerTwoGrid, playerOneGrid, 0);

}

BShipGame::BShipGame(istream* _inp, ifstream* _finp, ostream* _outp, int _gridSize, int _difficulty) {

    //I/o instanciation
    inp = _inp;
    //ifstream hecc("ship_placement.csv");
    finp = _finp;
    outp = _outp;

    //Grids instantiation
    playerOneGrid = new BShipGrid(_gridSize);
    playerTwoGrid = new BShipGrid(_gridSize);

    //Create Controllers
    playerOne = new UserController(playerOneGrid, playerTwoGrid, inp, outp);
    playerTwo = new CPUController(playerTwoGrid, playerOneGrid, 4);

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

        //GET INITIAL USER SETTINGS

        *outp << welcome() << endl;


        bool inputDone = false;
        while(!inputDone){
            *outp << displayMenu() << endl;
            *outp << "Enter a #: " << endl;
            int option = getValidInput(5);
            switch(option){
                case 1 : {
                    *outp << "---Instructions---" << endl;
                    *outp << instructions() << endl;
                    *outp << "------------------" << endl << endl;
                    break;
                }
                case 2 : {
                    *outp << "-----Difficulties-----" << endl;
                    *outp << " 0 - Default (Normal) " << endl;
                    *outp << " 1 - Easy / 2 - Normal" << endl;
                    *outp << " 3 - Hard / 4 - Semi-Pro" << endl;
                    *outp << " 5 - Pro / 6 - World Champ" << endl;
                    *outp << "   7 - c h e a t e r    " << endl;
                    *outp << "----------------------" << endl;

                    *outp << "Enter a #: " << endl;
                    int select = getValidInput(7, 0);
                    if(select == -1){
                        throw new string("User has quit, exiting...");
                    }
                    playerTwo = new CPUController(playerTwoGrid, playerOneGrid, select);
                    *outp << "Difficulty successfully set to " << to_string(select) << "."<<endl<<endl;
                    break;
                }
                case 3 : {
                    setNewFileFromInput();
                    break;
                }
                case 4 : {
                    inputDone = true;
                    *outp << "Initializing game..." << endl;
                    break;
                }
                case 5 : {
                    throw new string("User has quit, exiting...");
                    break;
                }
                default : {
                    throw new string("User has quit, exiting...");
                    break;
                }
            }
        }


        //SETUP PLAYER GRID FROM FIlE

        //Check if there is file input
        if(finp){
            //Read from file, pass responsibility to grid class
            try{
                playerOneGrid->file_populate(finp);
            } catch (exception const* e){
                cout << e->what() << endl;
            }catch(string const* e){
                //*outp << "An unknown error occured during the file reading stage. Please check your file and try again. Randomly populating instead." << endl;
                cout << endl << "Exception - " << *e << endl;
                cout << "Loading random grid into player 1 instead..." << endl;

                playerOneGrid = new BShipGrid(gridSize);
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
        vector<int> p1coords(playerOne->getNextCoordinates());
        vector<int> p2coords(playerTwo->getNextCoordinates());



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
        //this_thread::sleep_for(chrono::seconds(1));
        //cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << endl;
        //cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << endl;
    }
    return true;
}

string BShipGame::displayMenu(){
    string fin;

    fin+= "---Menu (Enter # to Select)---\n";
    for(int i=0; i < 5; i++){
        fin+= (to_string(i+1)+": "+menuStrings[i] + "\n");
    }

    return fin;
}

//Returns -1 if user quits.
int BShipGame::getValidInput(int max, int min) {
    string input;
    while(true){
        try{
            getline(*inp,input);
            if(input[0] == 'q' || input[0] == 'Q'){
                return -1;
            }
            if(input.size() > 1 || !isnumber(input[0]) || ((input[0] - '0') > max || (input[0] - '0') < min)){
                throw 1337;
            }else{
                *outp << endl;
                return (input[0] - '0');
            }
        }catch(...){
            *outp << "Invalid input, please try again: " << endl;
        }
    }
}

void BShipGame::setNewFileFromInput() {
    *outp << "Format: /path/to/file.csv" << endl;
    *outp << "Please enter a filepath: " << endl;
    bool valid = false;
    string fpath;
    while(!valid){
        if (getline(*inp, fpath)){
            if(fpath.find(".csv") != string::npos && fpath.find(".csv") > fpath.size()-4){
                ifstream oof(fpath);
                if(oof.is_open() && !oof.fail()){
                    valid = true;
                }
            }
        }
        if(!valid){
            *outp << "Filepath not valid. File must end in .csv." << endl;
            *outp << "Keep in mind the filepath is relative to your PWD." << endl;
            *outp << "Please enter a filepath: " << endl;
        }
    }
    finp = new ifstream(fpath);
}