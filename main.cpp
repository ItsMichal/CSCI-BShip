#include <fstream>
#include <iostream>
#include <exception>
#include "BShip/BShipGame.h"
using namespace std;
//This Main.cpp is 20 lines of code, including these two comments.
//This is to show how compact and modular my solution is. Enjoy.
int main() {
    ifstream csvfile ("test/ship_placement.csv"); //The ship placement file. Can be specified during runtime for ease of use
    //ifstream testcase("test/test_two"); //uncomment this to run unit tests from files! I have included three tests.
    //ofstream testoutput("test/output.txt"); //uncomment this to output to a text file instead of the console
    try {
        BShipGame* game = new BShipGame(&cin/*&testcase /* <-- also uncomment this too*/, &csvfile, &cout/*&testoutput /* <--- and this too */, 10); //Construct a game.
        game->runForever(); //Run the game forever, or well, till the end.
    }catch (string const* e){
        cout << endl << "Exception - " << *e << endl; //Catch those errors and display them.
        return 1; //Return of 1 means error.
    }
    return 0; //Return of 0 means all good.
}