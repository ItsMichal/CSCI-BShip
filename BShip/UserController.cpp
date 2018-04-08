//
// Created by Michal Bodzianowski on 3/1/18.
//

#include "UserController.h"

using namespace std;

UserController::UserController(BShipGrid *_myGrid, BShipGrid *_enemyGrid, istream *_inp, ostream *_outp) : BShipController(_myGrid, _enemyGrid) {
    inp = _inp;
    outp = _outp;
}

vector<int> UserController::getNextCoordinates() {
    bool valid = false;
    vector<int> coordinates(2,-1);
    while(!valid) {
        *outp << "Please enter a coordinate pair to hit (A-J)(1-10): " << endl;
        string input;
        int col, row;
        int gSize = enemyGrid->getSize();
        if (getline(*inp, input)) {
            if(input.size() > 0 && input.size() <= 3 ){
                if(isalpha(input[0]) && isnumber(input[1]) && (input.size() <= 2 || isnumber(input[2]))){
                    string num = input.substr(1);
                    try{
                        row = stoi(num)-1;
                        if(row > gSize || row <= 0){
                            col = coordFromLetter(input[0]);
                            if(col > gSize || col <= 0){
                                coordinates[0] = row;
                                coordinates[1] = col;
                                if(!enemyGrid->getSpotAtCoords(coordinates).hit){
                                    return coordinates;
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