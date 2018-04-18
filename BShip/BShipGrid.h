//
// Created by Michal Bodzianowski on 3/1/18.
//

#ifndef BSHIP_BSHIPGRID_H
#define BSHIP_BSHIPGRID_H

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <ctime>
#include <random>
//that's quite a bit of imports up there.

#include "BShipGridSpot.h"
#include "BShip.h"

//Handles the grid aspect of the game.
class BShipGrid {
private:

    //Config vars
    int size; //side length of grid, maxes out at 20, minimum is 6, default is 10
    int shipSize; //how many ships there should be on the grid


    //2D Vector to be used as grid
    vector<vector<BShipGridSpot>> grid; //the grid itself
    vector<BShip*> ships; //vector of ships useful in keeping track of them.


    //Class-specific utility funcs
    bool validate(BShip* s); //Checks if a ship would be valid if placed on the grid.
    bool areSame(string x, string y); //Checks if two strings are the same, regardless of case.
    int coordFromLetter(char x); //Gets a coordinate (int) from a letter (char)
    void addShipToGrid(BShip* s); //Adds a ship to the grid vector and ship vector.

public:

    //upper and lower bounds for config vars- variablized so they can be changed at will
    //depending on stability, but I don't have time to test them all. static for use in BShipGame
    static const int MAX_SIZE = 25;
    static const int MIN_SIZE = 5;
    static const int MAX_SHIP_SIZE = 100;
    static const int MIN_SHIP_SIZE = 1;

    //Constructor, also doubles as the default one. Useful.
    BShipGrid(int _size = 10, int _shipsize = 5);


    void file_populate(ifstream* finp);
    void rand_populate();

                        //Please pay respects to these functions which never really made it into the program, because, well, they didn't need to
                        //bool isValid(); <--- although this one kinda did just up there
                        //bool isCoordinateInBounds(vector<int> coord);
                        //bool isShipInBounds(vector<int> coord, int size, bool isHorizontal);

    //Some functions
    string displayFullGrid(); //self-explanatory- but returns a string.
    string displayGridNoShips(); //^^^
    bool areAllSunk(); //check if all ships are sunk.

    bool hit(vector<int> coords); //hits the spot at the coordinates, assumes they are correct but accounts if they aren't
    BShip* getShipAtCoords(vector<int> coords); //same as above but instead of hitting, it returns the BShip
    BShipGridSpot getSpotAtCoords(vector<int> coords); //same again, but returns the BShipGridSpot

    //A simple way to add more functionality would be to add more
    //accessors/mutators. But the requirements don't require it,
    //and I'm really out of time, so they'll have to wait.
    int getSize();

};

//Include struct for GridSpot here <-- this is an outdated comment. GridSpot is now it's own class. How they have grown.


#endif //BSHIP_BSHIPGRID_H
