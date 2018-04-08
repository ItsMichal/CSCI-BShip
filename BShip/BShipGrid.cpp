//
// Created by Michal Bodzianowski on 3/1/18.
//

#include "BShipGrid.h"

using namespace std;

BShipGrid::BShipGrid(int _size) {
    //set size
    size = _size;

    //Create Grid
    for(int i = 0; i < size; i++){
        vector<BShipGridSpot> tempGSV;
        vectorGrid.push_back(tempGSV);
        for(int j = 0; j < size; j++){
            BShipGridSpot tempGS ;
            vectorGrid[i].push_back(tempGS);
        }
    }


}




void BShipGrid::file_populate(ifstream *finp) {
    //Size Key
    map<string, int> namekey;
    namekey["Destroyer"] = 2;
    namekey["Submarine"] = 3;
    namekey["Cruiser"] = 3;
    namekey["Battleship"] = 4;
    namekey["Carrier"] = 5;

    //Helper vars
    string iline; //init line
    int cntr = 0; //line counter

    //IDEA FROM https://stackoverflow.com/a/37957126
    if(finp->is_open()) {
        while (getline(*finp, iline)) { //while there are still lines
            if(cntr != 0 && cntr <= 5) { //skip first line

                //temp BShip vars
                string tempname;
                int tempsize;
                vector<int> tempcoords(2,0);
                bool temphorizontal;

                stringstream line(iline);
                string cell;
                int subcntr = 0;
                while (getline(line, cell, ',')) {

                    switch(subcntr){
                        case 0: //name/size
                            if(areSame(cell, "Carrier"))
                            {
                                tempname = "Carrier";
                                tempsize = namekey.at("Carrier");

                            }else if(areSame(cell, "Battleship"))
                            {
                                tempname = "Battleship";
                                tempsize = namekey.at("Battleship");

                            }else if(areSame(cell, "Cruiser"))
                            {
                                tempname = "Cruiser";
                                tempsize = namekey.at("Cruiser");

                            }else if(areSame(cell, "Submarine"))
                            {
                                tempname = "Submarine";
                                tempsize = namekey.at("Submarine");

                            }else if(areSame(cell, "Destroyer"))
                            {
                                tempname = "Destroyer";
                                tempsize = namekey.at("Destroyer");
                            }else{
                                throw new string("Invalid Value - Invalid Entry at Line " + to_string(cntr+1) + ", Cell " + to_string(subcntr+1));
                            }
                            break;
                        case 1: //coordinates
                            //preliminary input okay check
                            if(cell.size() == 2 && isnumber(cell[1]) && isalpha(cell[0])){
                                //accept input and check if in bounds
                                int x = coordFromLetter(cell[0]);
                                if(x == -1) throw new string("Letter Value Out of Bounds - Invalid Entry at Line " + to_string(cntr+1) + ", Cell " + to_string(subcntr+1));

                                int y = cell[1] - 49;
                                if(y < 0 || y > size-1) throw new string("Number Value Out Of Bounds - Invalid Entry at Line " + to_string(cntr+1) + ", Cell " + to_string(subcntr+1));

                                tempcoords[0] = y; //row
                                tempcoords[1] = x; //col

                            }else{
                                throw new string("Value Out Of Bounds - Invalid Entry at Line " + to_string(cntr+1) + ", Cell " + to_string(subcntr+1));
                            }
                            break;
                        case 2: //allignment
                            if(cell.size() > 1){
                                if(cell[0] == 'h' || cell[0] == 'H'){
                                    temphorizontal = true; // false = v
                                }else if(cell[0] == 'v' || cell[0] == 'V'){
                                    temphorizontal = false;
                                }else{
                                    throw new string("Bad Value - Invalid Entry at Line " + to_string(cntr+1) + ", Cell " + to_string(subcntr+1));
                                }
                            }else{
                                throw new string("Bad Value - Invalid Entry at Line " + to_string(cntr+1) + ", Cell " + to_string(subcntr+1));
                            }
                            break;
                        default:
                            throw new string("Too Many Values on Row " + to_string(cntr+1));
                            break;
                    }
                    subcntr++;
                }

                //CREATE BSHIP HERE
                cout << to_string(cntr) << ": " << endl;
                cout << tempname << endl;
                cout << to_string(tempsize) << endl;
                cout << (temphorizontal ? "Horizontal" : "Vertical") << endl;
                cout << to_string(tempcoords[0]) << "," << to_string(tempcoords[1]) << endl;
                cout << "---" << endl;



                cntr++;
            }else{
                if(cntr > 5){
                    throw new string("Too Many Rows in File");
                }
                cntr++; //skip first line
            }

        }
    }else{
        throw new string("Generic File Error - Did Not Open");
    }
}

//func that compares strings regardless of case
bool BShipGrid::areSame(string x, string y) {
    if(x.length() != y.length()){
        return false;
    }
    for(int i = 0; i < x.length(); i++){
        if(!(isnumber(x[i]))) { //if NaN
            char xc = toupper(x[i]);
            char yc = toupper(y[i]);

            if(xc != yc){
                return false;
            }
        }else{
            if(x[i] != y[i]){
                return false;
            }
        }
    }
    return true;
}

int BShipGrid::coordFromLetter(char x) {
    //make lowercase if upper
    if (x >= 97) {
        x -= 32;
    }

    //validity check (0-10), must modify this with size
    if (x < 65 || x > (size-1)) {
        return x-65;
    }else{
        return -1;
    }
}