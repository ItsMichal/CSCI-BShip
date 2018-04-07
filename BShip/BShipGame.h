//
// Created by Michal Bodzianowski on 3/1/18.
//

#ifndef BSHIP_BSHIPGAME_H
#define BSHIP_BSHIPGAME_H

#include <iostream>
#include <fstream>
#include <string>
#include "BShipController.h"
#include "BShipGrid.h"
#include "BShipFacts.h"

using namespace std;

class BShipGame {
private:
    //I/O (Required)
    istream *inp;  //user input stream
    ifstream *finp; //file input stream
    ostream *outp; //output stream

    //Grids
    BShipGrid playerOneGrid;
    BShipGrid playerTwoGrid;

    //Controllers
    BShipController playerOne;
    BShipController playerTwo;

    //Game Facts
    BShipFacts gameFacts;

    //Game Logic (Private)
    void setup(); //run setup

    //Game Info
    int turnNumber = 0;
    int gridSize = 10;
    bool gameFinished = false;
    const string welcomeMessage = "Welcome to Michal's BShip Game!";
    const string instructionMessage = "-Press Q at any time to quit the game."
            "\n-X = Miss, O = Hit."
            "\n-When it's your turn, enter coordinates in the format '(Letter)(Number)', i.e. 'A1'"
            "\n-Game ends when one or the other ships are sunk!";

public:

    //Constructors
    BShipGame(); //Empty constructor -- always throws invalid file error at runtime, since no input file is specified
    BShipGame(istream _finp); //Minimum safe constructor
    BShipGame(istream _inp, istream _finp, ostream _outp);
    BShipGame(istream _inp, istream _finp, ostream _outp, int _turnNumber, int _gridSize); //Full Constructor

    //Game Logic
    string welcome(); //display welcome message
    string instructions(); //display instructions message

    void run(); //Have this class run the game.
};


#endif //BSHIP_BSHIPGAME_H
