//
// Created by Michal Bodzianowski on 3/1/18.
//

#ifndef BSHIP_BSHIPGAME_H
#define BSHIP_BSHIPGAME_H

#include <iostream>
#include <fstream>
#include <string>

#include "BShipGrid.h"
#include "BShipController.h"
#include "UserController.h"
#include "CPUController.h"
#include "BShipFacts.h"

using namespace std;

class BShipGame {
private:
    //I/O (Required)
    istream *inp;  //user input stream
    ifstream *finp; //file input stream
    ostream *outp; //output stream

    //Grids
    BShipGrid* playerOneGrid;
    BShipGrid* playerTwoGrid;

    //Controllers
    BShipController* playerOne;
    BShipController* playerTwo;

    //Game Facts
    //BShipFacts gameFacts;

    //Game Logic (Private)
    void doTurn();

    //Game Info
    int turnNumber = 0;
    int difficulty = 0;
    int gridSize = 10;
    bool gameSetUp = false;
    bool gameRunning = false;
    bool gameFinished = false;
    const string welcomeMessage = "Welcome to Michal's BShip Game!";
    const string instructionMessage = "-Enter Q at any time to quit the game."
            "\n-0 = Miss, X = Hit."
            "\n-When it's your turn, enter coordinates in the format '(Letter)(Number)', i.e. 'A1'"
            "\n-Game ends when one or the other ships are sunk!";
    const string menuStrings[5] = {
            "View Instructions",
            "Set Difficulty",
            "Set new Ship File",
            "Play",
            "Quit"
    };


public:

    //Constructors
    BShipGame(); //Empty constructor -- always throws invalid file error at runtime, since no input file is specified
    //BShipGame(istream* _inp); //Minimum safe constructor
    BShipGame(istream* _inp, ifstream* _finp, ostream* _outp = &cout, int _gridSize = 10, int _difficulty = 0); //Full Constructor

    //Game Logic
    string welcome(); //display welcome message
    string instructions(); //display instructions message
    string displayMenu(); //display the menu

    int getValidInput(int max, int min =1); //returns a valid menu option
    void setNewFileFromInput(); //sets a new finp from inp

    bool setup(); //run setup
    bool run(); //Have this class run the game.
    bool runForever(); //f o r e v e r
};


#endif //BSHIP_BSHIPGAME_H
