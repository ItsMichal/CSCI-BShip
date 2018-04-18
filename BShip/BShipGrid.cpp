//
// Created by Michal Bodzianowski on 3/1/18.
//

#include "BShipGrid.h"

using namespace std;

//Constructor. Can be empty since the default size is 10
BShipGrid::BShipGrid(int _size, int _shipsize) : ships(0){ //the ships vector constructor is called to handle potential memory errors from an empty pointer.
    //Set size
    size = _size;
    if(size > MAX_SIZE){
        throw new string("Grid size is too large. Valid grid sizes are from " + to_string(MIN_SIZE)+ " to "+to_string(MAX_SIZE)+".");
    }else if(size < MIN_SIZE){
        throw new string("Grid size is too small. Valid grid sizes are from " + to_string(MIN_SIZE)+ " to "+to_string(MAX_SIZE)+".");
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

    //set Ship count/size
    shipSize = _shipsize;
    if(shipSize > MAX_SHIP_SIZE){
        throw new string("Ship count is too large. Valid grid sizes are from " + to_string(MIN_SHIP_SIZE)+ " to "+to_string(MAX_SHIP_SIZE)+".");
    }else if(shipSize < MIN_SHIP_SIZE){
        throw new string("Ship count is too small. Valid grid sizes are from " + to_string(MIN_SHIP_SIZE)+ " to "+to_string(MAX_SHIP_SIZE)+".");
    }
}

//Fills the grid from an ifstream. Contains many catches and throws.
//Like every other exception, they are in string format. Is adjustable
//by way of key and switch, but I'd like to make it *truly* modular.
//This is one of the only components that use static definititions.
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

    //FINPUT IDEA FROM https://stackoverflow.com/a/37957126- just the way of splitting up the file.
    if(finp->is_open()) {

        while (getline(*finp, iline)) { //while there are still lines

            if(cntr != 0 && cntr <= shipSize) { //skip first line

                //temp BShip vars
                string tempname;
                int tempsize;
                vector<int> tempcoords(2,0);
                bool temphorizontal;

                stringstream line(iline); // stream for the line- splits into cells
                string cell; // holds cell string
                int subcntr = 0; //counts cell numbers
                while (getline(line, cell, ',')) {
                    //Do something different depending on which cell we are handling.
                    switch(subcntr){
                        case 0: //name/size get

                            //This could be replaced by a for loop, which looks up names in namekey.
                            //this component also is what prevents this from being fully, config.cfg style, modular.
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
                        case 1: //coordinates get

                            //preliminary input okay check
                            if(cell.size() >= 2 && stoi(cell.substr(1)) && isalpha(cell[0])){
                                //accept input and check if in bounds
                                int x = coordFromLetter(cell[0]);
                                if(x == -1) throw new string("Letter Value Out of Bounds - Invalid Entry at Line " + to_string(cntr+1) + ", Cell " + to_string(subcntr+1));

                                int y = stoi(cell.substr(1))-1;
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
                            throw new string("File Format Error - Too Many Values on Row " + to_string(cntr+1));
                            break;
                    }
                    subcntr++;
                }

                BShip* temp = new BShip(tempname, tempsize, temphorizontal, tempcoords); //create a temp BShip to validate

                //validate the ship- check func for more details
                if(validate(temp)){
                    addShipToGrid(temp); //add it to the grid if valid
                }else{
                    throw new string("Bad Value - Ship Conflicts/Goes Out of Bounds on Row " + to_string(cntr+1)); //throw error if not
                }

                cntr++; //increment counter
            }else{ //This is only (supposed to be) called on the first line, to skip processing headers

                //The only other case this is called when there are more than 5 ships specified.
                //Ship count can easily be made modular by replacing this with a variable. Everything
                //would still probably work minus some hiccups.
                if(cntr > 5){
                    throw new string("File Format Error - Too Many Rows in File");
                }
                cntr++; //skip first line
            }

        }
    }else{
        throw new string("File Error - Did Not Open/Did Not Find File");
    }

    //check to see if file has sufficient size for all ships
    if(cntr < shipSize){
        throw new string("File Format Error - Not enough values in file. Consider changing Ship Count in the menu.");
    }
}

//Utility func that compares strings regardless of case.
bool BShipGrid::areSame(string x, string y) {
    //If not the same length, simply return false, done and dusted.
    if(x.length() != y.length()){
        return false;
    }

    //Simple compare by char, seperates case sensitive chars (alpha) from caseless chars (think symbols, nums)
    for(int i = 0; i < x.length(); i++){
        if(!(isdigit(x[i]))) { //if NaN
            char xc = toupper(x[i]);
            char yc = toupper(y[i]);

            if(xc != yc){
                return false; //return false
            }
        }else{
            if(x[i] != y[i]){
                return false;
            }
        }
    }
    return true;
}

//Utility function to get a coordinate (or int) from a letter. Now works with other sizes.
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


//Most of this was frankensteined from my HW3. It works here, and works alright,
//and saved me time, so I've decided to keep it for now, but possibly one of the
//points to redo later on if I have time. Returns true on success, false on fail.
bool BShipGrid::validate(BShip* s) {

    //bootstrap the BShip to the vars used by the old function
    bool tempAlign = s->isHorizontal();
    int tempX = s->getCol();
    int tempY = s->getRow();
    int tempLen = s->getSize();
    BShip tempVehicle = *s;

    //THE FOLLOWING CODE WAS REUSED FROM HW3

    bool valid = true;

    //check OoB first
    if (tempAlign) {
        if (tempX + tempLen > size)
            valid = false;
    } else {
        if (tempY + tempLen > size)
            valid = false;
    }

    //Validate part 2 (collision)
    bool valid2 = true;

    //check collision against all other ship
    for (int j = 0; j < ships.size(); j++) {

        BShip* other = ships[j]; //the other ship being checked for

        //if parallel
        if (other->isHorizontal() == tempAlign) {
            if (tempVehicle.isHorizontal()) { //horizontal
                if (tempY == other->getRow()) {  //on the same row
                    if (tempX <= other->getCol() + other->getSize() - 1 &&
                        tempX + tempLen - 1 >= other->getCol()) { //and overlaping
                        valid2 = false; //that means they are colliding
                    }
                }
            } else { //vertical
                if (tempX == other->getCol()) {  //on the same column
                    if (tempY <= other->getRow() + other->getSize() - 1 && tempY + tempLen - 1 >= other->getRow()) { //and overlapping  //  OLD LOGIC || ( < other.getY()+other.getLength() && tempY > other.getY())){//tempY < other.getY() && (tempY+tempLen) > other.getY()){ //overlapping
                        valid2 = false; //then they are colliding
                    }
                }
            }
        } else { //if not parallel

            //dumb check- checks every position for conflict.
            //invalidates on first occasion. This is O(n^2) function
            //is in need of a rewrite for efficiency, but works for now.
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

    //if one or the other is not valid, then return false,
    //as they are conflicting.
    if (!valid || !valid2) {
        return false;
    } else {
        return true;
    }
}

//Adds a ship to the grid.
void BShipGrid::addShipToGrid(BShip* s) {

    //add ship to the ship vector first
    ships.push_back(s);

    //then just simply go through the ship and add it piece by piece to the grid.
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

//Displays the full grid, making ships visible.
string BShipGrid::displayFullGrid() {

    //Helper/builder strings
    string finstr;
    string finstr2;

    //Create top row key
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

    //Add in the main body with the side key.
    for(int i = 0; i < grid.size(); i++){

        //side key, with proper indentation for double digit values
        finstr += (i>=9) ? (to_string(i+1) + "| ") : (to_string(i+1) + " | ");


        for(int j = 0; j < grid[0].size(); j++){ //adds the row
            if(!grid[i][j].empty && !grid[i][j].hit) { //display the ship part if not hit and not empty
                finstr +=  grid[i][j].motherShip->getName().at(0);
                finstr +=  grid[i][j].motherShip->getName().at(1);
                finstr += "  ";
            }else if(grid[i][j].hit && grid[i][j].empty) { //display a miss marker if gridspot is hit but empty
                finstr += "0   ";
            }else if(!grid[i][j].hit){ //display water if not hit
                finstr += "~   ";
            }else{ //or finally display a hit marker since being hit and being empty is the only condition left.
                finstr +=  "X   ";
            }
        }
        finstr += "\n";
    }

    //adds the bottom line
    finstr += (finstr2 + "\n");

    //return the final string.
    return finstr;
}


//This is the same as above, with slightly different logic
//that hides the ships, so as not to give away their position.
//Just imagine the beautiful comments from up top are here as well.
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


//Randomly populate the grid. Can be customized by editing the values here directly.
//Another thing to relegate to member variables instead if I chose to do the modification
//to a full, truly modular application, for whatever reason.
void BShipGrid::rand_populate() {

    srand(time(nullptr)); //set seed

    //---CONFIG---
    const int max_count = 900000; //protection against infinite loops.
    int count = 1;
    int sizes[5] = {5,4,3,3,2};
    string names[5] = {"Carrier", "Battleship", "Submarine", "Cruiser", "Destroyer"};
    //------------

    vector<BShip*> holder;

    for(int i = 0; i < shipSize; i++){
        bool valid = false;
        while(!valid){
            bool thorizontal = rand() % 2 == 0; //set a random horizon val
            int trow; //temp row
            int tcol; //temp col
            vector<int> tcoord(2,0); //temp coords

            //smart assign trow and and tcol, so it doesn't go OoB
            if(thorizontal){
                trow = rand() % (size);
                tcol = rand() % ((size)-sizes[i%5]+1);
            }else{
                tcol = rand() % (size);
                trow = rand() % ((size)-sizes[i%5]+1);
            }

            //assign
            tcoord[0] = trow;
            tcoord[1] = tcol;

            //create temp object
            BShip* temp = new BShip(names[i%5], sizes[i%5], thorizontal, tcoord);

            //check if valid?
            if(validate(temp)){
                valid=true;
                addShipToGrid(temp);
            }
            //otherwise repeat.

            //safety catch
            count++;
            if(count > max_count){
                throw new string("Program Error - Random Fill Took Too Long To Complete, Please Try Again");
            }
        }
    }
}

//Gets the size. Not sure why it's all the way down here though.
int BShipGrid::getSize() {
    return size;
}

//Hits the gridspot at the coordinates. Returns true if successful, regardless
//of whether it actually hit a ship or not. If it does hit a ship, it passes that
//hit along to the ship class as well, which is handy for, you know, making the game progress.
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

//Checks if all ships are sunk. Useful utility function
//for BShipGame class, to check if there is a victory condition.
bool BShipGrid::areAllSunk() {
    for(int i = 0; i < ships.size(); i++){
        if(!ships[i]->isSunk()){
            return false;
        }
    }
    return true;
}


//Gets the ship object at the specified coordinates. Throws an error accordingly. Pretty simple.
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
        throw new string("Function Call Error [getShipAtCoords] - Coords Out Of Bounds - Please Try Again");
    }
}

//Gets the spot object at coordinates...wait a sec, I just realized
//it should PROBABLY be a pass by reference...oh well, it works well
//enough without it, why invite more bugs by changing it? Throws an error accordingly.
BShipGridSpot BShipGrid::getSpotAtCoords(vector<int> coords) {
    //check if coords are inbounds
    if(coords[0] >= 0 && coords[0] < size && coords[1] >= 0 && coords[1] < size) {
        return grid[coords[0]][coords[1]];
    }else{
        throw new string("Function Call Error [getSpotAtCoords] - Coords Out Of Bounds - Please Try Again");
    }
}