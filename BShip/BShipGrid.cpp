//
// Created by Michal Bodzianowski on 3/1/18.
//

#include "BShipGrid.h"

using namespace std;

BShipGrid::BShipGrid(int _size) : ships(0){
    //set size
    size = _size;
    if(size > 25){
        throw new string("Grid size is too large. Valid grid sizes are from 5 to 25.");
    }else if(size < 5){
        throw new string("Grid size is too small. Valid grid sizes are from 5 to 25.");
    }

    //Create Grid
    for(int i = 0; i < size; i++){
        vector<BShipGridSpot> tempGSV;
        grid.push_back(tempGSV);
        for(int j = 0; j < size; j++){
            BShipGridSpot tempGS ;
            grid[i].push_back(tempGS);
        }
    }





    //Fill Ships
//    for(int i = 0; i < 5; i++){
//        vector<int> hecc (2,-1);
//        BShip ahoy("",0,false, hecc);
//        ships.push_back(ahoy);
//    }


}




void BShipGrid::file_populate(ifstream *finp) {
    //Size Key
    map<string, int> namekey;
    namekey["Tug Boat"] = 1;
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
                    //Scrub newline

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
                            }else if(areSame(cell, "Tug Boat")){
                                tempname = "Tug Boat";
                                tempsize = namekey.at("Tug Boat");
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
                            if(cell.size() >= 1){
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
//                cout << to_string(cntr) << ": " << endl;
//                cout << tempname << endl;
//                cout << to_string(tempsize) << endl;
//                cout << (temphorizontal ? "Horizontal" : "Vertical") << endl;
//                cout << to_string(tempcoords[1]) << "," << to_string(tempcoords[0]) << endl;
//                cout << "---" << endl;

                BShip* temp = new BShip(tempname, tempsize, temphorizontal, tempcoords);

                if(validate(temp)){
                    addShipToGrid(temp);
                }else{
                    throw new string("Ship Conflicts/Goes Out of Bounds on Row " + to_string(cntr+1));
                }

                //cout << displayFullGrid() << endl;

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

bool BShipGrid::validate(BShip* s) {

    bool tempAlign = s->isHorizontal();
    int tempX = s->getCol();
    int tempY = s->getRow();
    int tempLen = s->getSize();
    BShip tempVehicle = *s;

    //THE FOLLOWING CODE WAS REUSED FROM HW3

    bool valid = true;
    //cout << "SANITY CHECK 1" << endl;
    //check OoB first
    if (tempAlign) {
        if (tempX + tempLen > size)
            valid = false;
    } else {
        if (tempY + tempLen > size)
            valid = false;
    }
    //cout << "SANITY CHECK 2" << endl;
    //if (!valid) {
    //    cout
    //            << "Sorry, but the ship you specified goes out of bounds. Make sure that the ship fits on the 10x10 grid and try again."
    //            << endl;
    //}

    //Validate part 2 (collision)
    bool valid2 = true;

    int ssize;




    for (int j = 0; j < ships.size(); j++) {
        BShip* other = ships[j];

        //parallel
        if (other->isHorizontal() == tempAlign) {
            if (tempVehicle.isHorizontal()) { //vertical
                if (tempY == other->getRow()) {  //on the same row
                    if (tempX <= other->getCol() + other->getSize() - 1 &&
                        tempX + tempLen - 1 >= other->getCol()) { //overlaping
                        valid2 = false;
                    }
                }
            } else { //vertical
                if (tempX == other->getCol()) {  //on the same column
                    if (tempY <= other->getRow() + other->getSize() - 1 && tempY + tempLen - 1 >= other->getRow()) {//|| ( < other.getY()+other.getLength() && tempY > other.getY())){//tempY < other.getY() && (tempY+tempLen) > other.getY()){ //overlapping
                        valid2 = false;
                    }
                }
            }
        } else { //horizontal
            //dumb check
            for (int ii = 0; ii < tempLen; ii++) {
                for (int jj = 0; jj < other->getSize(); jj++) {
                    if (tempVehicle.isHorizontal()) {
                        if (tempX + ii == other->getCol() && tempY == other->getRow() + jj) {
                            valid2 = false;
                        }
                    } else {
                        if (tempX == other->getCol() + jj && tempY + ii == other->getRow()) {
                            valid2 = false;
                        }
                    }
                }
            }
        }
    }

    if (!valid || !valid2) {
        return false;
    } else {
        return true;
    }
}

void BShipGrid::addShipToGrid(BShip* s) {

    ships.push_back(s);

    //cout << "leng" << to_string(v.getLength()) << endl;
    for(int i = 0; i < s->getSize(); i++){

        if(s->isHorizontal()){
            grid[s->getRow()][s->getCol()+i].empty = false;
            grid[s->getRow()][s->getCol()+i].motherShip = s;
        }else{
            grid[s->getRow()+i][s->getCol()].empty =  false;
            grid[s->getRow()+i][s->getCol()].motherShip = s;
        }
    }
}

string BShipGrid::displayFullGrid() {
    string finstr;
    string finstr2;

    finstr += "X |";
    finstr2+= "____";
    for(int i = 0; i < size; i++){

        finstr += " ";
        finstr += i + 'A';
        finstr += " |";
        finstr2 += "____";
    }
    finstr += "\n";


    finstr += (finstr2 + "\n");
    for(int i = 0; i < grid.size(); i++){
        finstr += (i>=9) ? (to_string(i+1) + "| ") : (to_string(i+1) + " | ");
        for(int j = 0; j < grid[0].size(); j++){
            if(i == 5 && j == 7){
                cout << "";
            }
            if(!grid[i][j].empty && !grid[i][j].hit) {
                finstr +=  grid[i][j].motherShip->getName().at(0);
                finstr +=  grid[i][j].motherShip->getName().at(1);
                finstr += "  ";
                //eventually replace with chars
            }else if(grid[i][j].hit && grid[i][j].empty) {
                finstr += "0   "; //eventually replace with chars
            }else if(!grid[i][j].hit){
                finstr += "~   ";
            }else{
                finstr +=  "X   "; //eventually replace with chars
            }
        }
        finstr += "\n";
    }
    finstr += (finstr2 + "\n");

    return finstr;
}

string BShipGrid::displayGridNoShips(){
    string finstr;
    string finstr2;

    finstr += "X |";
    finstr2+= "____";

    for(int i = 0; i < size; i++){

        finstr += " ";
        finstr += i + 'A';
        finstr += " |";
        finstr2 += "____";
    }
    finstr += "\n";


    finstr += (finstr2 + "\n");
    for(int i = 0; i < grid.size(); i++){
        finstr += (i>=9) ? (to_string(i+1) + "| ") : (to_string(i+1) + " | ");
        for(int j = 0; j < grid[0].size(); j++){
            if(i == 5 && j == 7){
                cout << "";
            }
            if(!grid[i][j].hit) {
                finstr += "~   ";
                //eventually replace with chars
            }else if(grid[i][j].hit && grid[i][j].empty) {
                finstr += "0   "; //if hit but a miss (bc empty)
            }else{
                finstr +=  "X   "; //eventually replace with chars
            }
        }
        finstr += "\n";
    }
    finstr += (finstr2 + "\n");

    return finstr;
}

void BShipGrid::rand_populate() {
    srand(time(nullptr)); //set seed

    const int max_count = 90000; //protection against infinite loops.
    int count = 0;
    int sizes[5] = {5,4,3,3,2};
    string names[5] = {"Carrier", "Battleship", "Submarine", "Cruiser", "Destroyer"};

    for(int i = 0; i < 5; i++){
        bool valid = false;
        while(!valid){
            bool thorizontal = rand() % 2 == 0; //set a random horizon val
            int trow; //temp row
            int tcol; //temp col
            vector<int> tcoord(2,0);

            if(thorizontal){
                //smart assign trow and and tcol, so it doesn't go OoB
                trow = rand() % (size-1);
                tcol = rand() % ((size-1)-sizes[i]);
            }else{
                tcol = rand() % (size-1);
                trow = rand() % ((size-1)-sizes[i]);
            }

            //assign
            tcoord[0] = trow;
            tcoord[1] = tcol;

            //create temp object
            BShip* temp = new BShip(names[i], sizes[i], thorizontal, tcoord);

            //check if valid?
            if(validate(temp)){
                valid=true;
                addShipToGrid(temp);
            }
            //otherwise repeat.

            //safety catch
            count++;
            if(count > max_count){
                throw new string("Random Fill Took Too Long To Complete, Please Try Again");
            }
        }
    }
}

int BShipGrid::getSize() {
    return size;
}

bool BShipGrid::hit(vector<int> coords) {

    //check if coords are inbounds
    if(coords[0] >= 0 && coords[0] < size && coords[1] >= 0 && coords[1] < size) {
        grid[coords[0]][coords[1]].hit = true;

        //check if coords hit a ship
        if (!grid[coords[0]][coords[1]].empty && grid[coords[0]][coords[1]].motherShip != nullptr) {
               grid[coords[0]][coords[1]].motherShip->hit();

        }
        return true;
    }else{
        return false;
    }
}

bool BShipGrid::areAllSunk() {
    for(int i = 0; i < ships.size(); i++){
        if(!ships[i]->isSunk()){
            return false;
        }
    }
    return true;
}

//CAREFUL: Returns nullptr if no ship found.
BShip* BShipGrid::getShipAtCoords(vector<int> coords) {
    //check if coords are inbounds
    if(coords[0] >= 0 && coords[0] < size && coords[1] >= 0 && coords[1] < size) {
        if (!grid[coords[0]][coords[1]].empty && grid[coords[0]][coords[1]].motherShip != nullptr) {
            return grid[coords[0]][coords[1]].motherShip;
        }else{
            return nullptr;
        }
    }else{
        throw new string("Error - Coords Out Of Bounds - Please Try Again");
    }
}

BShipGridSpot BShipGrid::getSpotAtCoords(vector<int> coords) {
    //check if coords are inbounds
    if(coords[0] >= 0 && coords[0] < size && coords[1] >= 0 && coords[1] < size) {
        return grid[coords[0]][coords[1]];
    }else{
        throw new string("Error - Coords Out Of Bounds - Please Try Again");
    }
}