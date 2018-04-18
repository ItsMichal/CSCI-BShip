//
// Created by Michal Bodzianowski on 3/1/18.
//

#include "UserController.h"

using namespace std;

UserController::UserController(BShipGrid *_myGrid, BShipGrid *_enemyGrid, istream *_inp, ostream *_outp) : BShipController(_myGrid, _enemyGrid) {
    inp = _inp;
    outp = _outp;
}

//Very meaty and robust literal block of code that is meant to anticipate
//nearly all user inputs, and only allow the very finest in. Sorry for discriminating,
//but "adsih123h19io" isn't exactly a coordinate pair that the game requires.
vector<int> UserController::getNextCoordinates() {
    //Variables that are used throughout the functions,
    //which are put at the highest scope because of that.
    bool valid = false;
    vector<int> coordinates(2,-1);

    //While our pair is still invalid
    while(!valid) {
        //Display directions.
        *outp << "Please enter a coordinate pair to hit (A-J)(1-10): " << endl;

        //Deal with input.
        string input;

        //col/row helper vars for readability, same with gSize
        int col, row;
        int gSize = enemyGrid->getSize();


        if (getline(*inp, input)) { //first failsafe- getline returns false if it encounters an error

            if(input.size() > 0 && input.size() <= 3 ){ //second failsafe- check the size of the input

                if(isalpha(input[0]) && isdigit(input[1]) && (input.size() <= 2 || isdigit(input[2]))){ //third failsafe- check content type of input

                    //try block here in case things go wrong with stoi. just in case.
                    try{
                        //get row info from the input string
                        string num = input.substr(1);
                        row = stoi(num)-1;

                        if(row < gSize && row >= 0){ //fourth failsafe- make sure row input is valid

                            //get the column from the letter- function
                            //copy pasted from BShipGrid, as its valid here too.
                            col = coordFromLetter(input[0]);

                            if(col < gSize && col >= 0){ //fifth failsafe- ensure col input is valid

                                //and after those 5 essential failsafes we (hopefully) have a good input...but
                                coordinates[0] = row;
                                coordinates[1] = col;

                                if(!enemyGrid->getSpotAtCoords(coordinates).hit){ //sixth failsafe- make sure you haven't already used it!
                                    return coordinates; //ah, finally. we're done.

                                //And now for a whole lot of error messages.
                                }else{
                                    *outp << "Invalid input, you've already hit that spot!" << endl;
                                }

                            }else{
                                *outp << "Invalid input, make sure the coordinate is in bounds." << endl;
                            }
                        }else{
                            *outp << "Invalid input, make sure the coordinate is in bounds." << endl;
                        }

                    }catch(...){
                        *outp << "Invalid input, make sure the coordinate has a number." << endl;
                    }
                }else{
                    //Sneaky little insert that catches a quit input ;)
                    if(input.size() == 1 && (input[0] == 'q' || input[0] == 'Q')){
                        throw new string("User has quit, exiting...");
                    }
                    *outp << "Invalid input, make sure you use the correct format." << endl;
                }
            }else{
                *outp << "Invalid input, make sure you use only 2 or 3 characters!" << endl;
            }
        } else {
            *outp << "Invalid input, please try again." << endl;
        }
    }
}

//Coord from letter function copied because its
//easier to do so than setting up some weird
//static nonsense.
int UserController::coordFromLetter(char x) {
    //make lowercase if upper
    if (x >= 97) {
        x -= 32;
    }

    //validity check (0-10), must modify this with size
    if (x < 65 || x > (enemyGrid->getSize()-1)) {
        return x-65;
    }else{
        return -1;
    }
}