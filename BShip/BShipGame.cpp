//
// Created by Michal Bodzianowski on 3/1/18.
//

#include "BShipGame.h"

using namespace std;


//Default Constructor for quick games
BShipGame::BShipGame() {

    //I/o instanciation
    inp = &cin;
    finp = nullptr; //uh oh
    outp = &cout;

    //Grids instanciation
    playerOneGrid = new BShipGrid(gridSize,shipCount);
    playerTwoGrid = new BShipGrid(gridSize,shipCount);

    //Create Controllers
    playerOne = new  CPUController(playerOneGrid, playerTwoGrid, 0);
    playerTwo = new CPUController(playerTwoGrid, playerOneGrid, 0);

    gridSize = 10;
    difficulty = 0;

}

//Full Constructor for more customization and utility
BShipGame::BShipGame(istream* _inp, ifstream* _finp, ostream* _outp, int _gridSize, int _difficulty, int _shipCount) {

    //I/o instanciation
    inp = _inp;
    finp = _finp;
    outp = _outp;

    //Grids instantiation
    playerOneGrid = new BShipGrid(_gridSize, _shipCount);
    playerTwoGrid = new BShipGrid(_gridSize, _shipCount);

    //Create Controllers
    playerOne = new UserController(playerOneGrid, playerTwoGrid, inp, outp);
    playerTwo = new CPUController(playerTwoGrid, playerOneGrid, difficulty);

    //Set some options for reference
    gridSize = _gridSize;
    difficulty = _difficulty;
    shipCount = _shipCount;
}

//Return the welcome message
string BShipGame::welcome() {
    return welcomeMessage;
}

//Return the instruction message
string BShipGame::instructions() {
    return instructionMessage;
}

//Step option for allowing the game to progress,
//allows the program to do aditional logic in
//between turns in the program. Adds a bool return
//so the parent program can decide what to do if
//it is impossible to run.
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

//Setup the game, must be run before the game starts,
//cannot be run more than once due to its nature.
bool BShipGame::setup() {
    //Check if game has already been set up
    if(!gameSetUp){

        //GET INITIAL USER SETTINGS

        *outp << welcome() << endl;


        bool inputDone = false;
        while(!inputDone){
            *outp << displayMenu() << endl;
            *outp << "Enter a #: " << endl;
            int option = getValidInput(menuItems);
            switch(option){
                case 1 : { //Display instructions
                    *outp << "---Instructions---" << endl;
                    *outp << instructions() << endl;
                    *outp << "------------------" << endl << endl;
                    break;
                }
                case 2 : { //Set difficulty
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
                    difficulty = select;
                    *outp << "Difficulty successfully set to " << to_string(select) << "."<<endl<<endl;
                    break;
                }
                case 3 : { //Load new file
                    setNewFileFromInput();
                    *outp << endl << "New file successfully loaded." << endl << endl;
                    break;
                }
                case 4 : { //Set grid size

                    //uinput
                    *outp << "Enter a valid grid size ("<< to_string(BShipGrid::MIN_SIZE) <<"-"<< to_string(BShipGrid::MAX_SIZE) << "): " << endl;
                    gridSize = getValidInput(BShipGrid::MAX_SIZE, BShipGrid::MIN_SIZE);

                    //Grids instantiation
                    playerOneGrid = new BShipGrid(gridSize, shipCount);
                    playerTwoGrid = new BShipGrid(gridSize, shipCount);

                    //Create Controllers
                    playerOne = new UserController(playerOneGrid, playerTwoGrid, inp, outp);
                    playerTwo = new CPUController(playerTwoGrid, playerOneGrid, difficulty);
                    *outp << "Successfully set grid to " << gridSize << "x" << gridSize << "." << endl << endl;
                    break;
                }
                case 5 : { //Set ship count
                    //uinput
                    *outp << "Enter a valid grid size ("<< to_string(BShipGrid::MIN_SHIP_SIZE) <<"-"<< to_string(BShipGrid::MAX_SHIP_SIZE) << "): " << endl;
                    shipCount = getValidInput(BShipGrid::MAX_SHIP_SIZE, BShipGrid::MIN_SHIP_SIZE);

                    //Grids instantiation
                    playerOneGrid = new BShipGrid(gridSize, shipCount);
                    playerTwoGrid = new BShipGrid(gridSize, shipCount);

                    //Create Controllers
                    playerOne = new UserController(playerOneGrid, playerTwoGrid, inp, outp);
                    playerTwo = new CPUController(playerTwoGrid, playerOneGrid, difficulty);
                    *outp << "Successfully set grid to " << gridSize << "x" << gridSize << "." << endl << endl;
                    break;
                }
                case 6 : { //Play
                    inputDone = true;
                    *outp << "Initializing game..." << endl;
                    break;
                }
                case 7 : { //Quit
                    throw new string("User has quit, exiting...");
                    break;
                }
                default : { //on weird
                    throw new string("Unexpected! - User has quit, exiting...");
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

                playerOneGrid = new BShipGrid(gridSize,shipCount);
                playerOneGrid->rand_populate();
                playerTwo = new CPUController(playerTwoGrid, playerOneGrid, difficulty);
            }
        }else{
            *outp << "No file specified. Randomly populating your grid instead." << endl;
            playerOneGrid->rand_populate();
        }

        //SETUP CPU GRID
        playerTwoGrid->rand_populate();

        //display game start
        *outp << endl << "--------------------------" << endl;
        *outp <<         "|          START         | - - - - - - - - - - - - - - > START" << endl;
        *outp <<         "--------------------------" << endl;

        //DISPLAY GRIDS
        *outp <<  endl << displayGameGrids() << endl;

        //SETUP COMPLETE
        gameSetUp = true;

        return true;
    }
    return false;
}


//Main body and game logic. Calls upon all other
//components and handles the game, including win conditions,
//data display, and other interfacing. Hands off other
//responsibilities to other classes.
void BShipGame::doTurn() {
    //Check if game has not yet finished.
    if(!gameFinished){

        //Increment turn counter
        turnNumber++;

        //Context switches for announcements at end
        bool p1sunkship = false, p2sunkship = false, p1hitship = false, p2hitship = false;

        //Get next coordinates of both players
        vector<int> p1coords;
        try {
            p1coords = (playerOne->getNextCoordinates());
        }catch(...){
            *outp << displayFullGrids() << endl;
            throw new string("User has quit, exiting...");
        }
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

        //player 2
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

        //display turn number
        string turnString = to_string(turnNumber);
        if(turnNumber < 10) turnString+=" ";
        *outp << endl << "--------------------------" << endl;
        *outp << "|         Turn "+ turnString +"        | - - - - - - - - - - - - - - > " << to_string(turnNumber) << endl;
        *outp << "--------------------------" << endl;

        //display grids
        *outp << endl<< displayGameGrids() << endl;

        //display contextual info
        if(p1sunkship){
            *outp << "You sunk a " << p1ShipTarget->getName() << "!" << endl;
        }else if(p1hitship){
            *outp << "You hit an enemy ship!" << endl; //dont display ship name as it can give away size.
        }

        //getting int+char to render as a char is hard...
        char column = p2coords[1] + 'A';
        *outp << "The CPU guessed ";
        *outp << column;
        *outp << p2coords[0] << "." << endl;

        if(p2sunkship){
            *outp << "The CPU sunk your " << p2ShipTarget->getName() << "!" << endl;
        }else if(p2hitship){
            *outp << "The CPU hit your " << p2ShipTarget->getName() << "!" << endl; //dont display ship name as it can give away size.
        }


        //check for winner
        if(playerOneGrid->areAllSunk() && playerTwoGrid->areAllSunk()){
            gameFinished = true;
            *outp << endl << "WOW! It's a tie!" << endl;
        }else if(playerOneGrid->areAllSunk()){
            gameFinished = true;
            *outp << endl << "CPU Wins!" << endl;
        }else if(playerTwoGrid->areAllSunk()){
            gameFinished = true;
            *outp << endl << "You win!" << endl;
        }

        //display full grids
        if(gameFinished){
            *outp << displayFullGrids() << endl;
            *outp << "Good Game!" <<endl;
        }

    }else{
        throw new string("Game has already finished. Please construct a new game class to replay.");
    }
}

//Method that allows easy, painless running of the game.
bool BShipGame::runForever() {
    if(gameFinished)
        return false;
    while(!gameFinished){
        this->run();
    }
    return true;
}

//Displays the menu. (Technically) Useless outside of the setup function.
string BShipGame::displayMenu(){
    string fin;

    fin+= "---Menu (Enter # to Select)---\n";
    for(int i=0; i < menuItems; i++){
        fin+= (to_string(i+1)+": "+menuStrings[i] + "\n");
    }

    return fin;
}

//Returns -1 if user quits. Gets a valid integer input min-max inclusive from inp
int BShipGame::getValidInput(int max, int min) {
    string input;
    while(true){
        try{
            getline(*inp,input);
            if(input[0] == 'q' || input[0] == 'Q'){
                return -1;
            }
            bool valid = true;
            if(!stoi(input) || stoi(input) > max || stoi(input) < min){
                throw 1337;
            }else{
                *outp << endl;
                return stoi(input);
            }
        }catch(...){
            *outp << "Invalid input, please try again: " << endl;
        }
    }
}

//Gets a new file from input. Pretty self-explanatory.
void BShipGame::setNewFileFromInput() {
    *outp << "Format: /path/to/file.csv" << endl;
    *outp << "Please enter a filepath: " << endl;
    bool valid = false;
    string fpath;
    while(!valid){
        if (getline(*inp, fpath)){
            if(fpath.find(*(new string(".csv"))) != string::npos && fpath.find(".csv") > fpath.size()-5){
                ifstream oof(fpath);
                if(oof.is_open() && !oof.fail()){
                    valid = true;
                }else{
                    *outp << "Keep in mind the filepath is relative to your PWD." << endl;
                }
            }
        }
        if(fpath.size() == 1 && (fpath[0] == 'q' || fpath[0] == 'Q')){
            throw new string("User has quit, exiting...");
        }
        if(!valid){

            *outp << "Please enter a filepath: " << endl;
        }
    }
    finp = new ifstream(fpath);
}


//Two utility functions. Simply displays the grids

//This one displays everything on both grids.
string BShipGame::displayFullGrids(){
    stringstream fin;
    fin << endl << "-- Full Grids --" << endl << endl;
    fin << "-CPU's Grid:-" << endl;
    fin << playerTwoGrid->displayFullGrid() << endl;
    fin << "-Your Grid:-" << endl;
    fin << playerOneGrid->displayFullGrid() << endl;
    return fin.str();
}

//This one hides the ships on the enemy grid.
string BShipGame::displayGameGrids(){
    stringstream fin;
    fin << "-CPU's Grid:-" << endl;
    fin << playerTwoGrid->displayGridNoShips() << endl;
    fin << "-Your Grid:-" << endl;
    fin << playerOneGrid->displayFullGrid() << endl;
    return fin.str();
}