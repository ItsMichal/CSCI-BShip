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

/*
 *
 * Main class for the game. Handles every other class, and is the main
 * interface for the end-user. Contains many helpful functions.
 *
 */

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

    //Game Facts (Scrapped idea)
    //BShipFacts gameFacts;

    //Game Logic (Private)
    void doTurn();

    //Game Info
    int turnNumber = 0;
    int difficulty = 0;
    int gridSize = 10;
    int shipCount = 5;
    bool gameSetUp = false;
    bool gameRunning = false; //to be used a later date
    bool gameFinished = false;

    const string welcomeMessage = "Welcome to Michal's BShip Game!";
    const string instructionMessage = "-Enter Q at any time to quit the game."
            "\n-0 = Miss, X = Hit."
            "\n-When it's your turn, enter coordinates in the format '(Letter)(Number)', i.e. 'A1'"
            "\n-Game ends when all of one or the others ships are sunk!";

    static const int menuItems = 7; //why does it have to be static if its already const...? how can a const change? it's probably something to do with it being needed at compile time
    const string menuStrings[menuItems] = {
            "View Instructions",
            "Set Difficulty (BONUS!)",
            "Set New Ship File",
            "Set Grid Size (BONUS!)",
            "Set Ship Count (BONUS!)",
            "Play",
            "Quit"
    };


public:

    //Constructors
    BShipGame(); //Empty constructor -- always throws invalid file error at runtime, since no input file is specified
    //BShipGame(istream* _inp); //Minimum safe constructor
    BShipGame(istream* _inp, ifstream* _finp, ostream* _outp = &cout, int _gridSize = 10, int _difficulty = 0, int _shipCount = 5); //Full Constructor

    //Game Logic
    string welcome(); //display welcome message
    string instructions(); //display instructions message
    string displayMenu(); //display the menu
    string displayGameGrids(); //display hidden CPU grid and full User grid
    string displayFullGrids(); //display both full grids for end of game.

    int getValidInput(int max, int min =1); //returns a valid menu option
    void setNewFileFromInput(); //sets a new finp from inp

    bool setup(); //run setup
    bool run(); //Have this class run the game.
    bool runForever(); //f o r e v e r
};


#endif //BSHIP_BSHIPGAME_H
