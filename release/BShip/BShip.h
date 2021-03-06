//
// Created by Michal Bodzianowski on 3/1/18.
//

#ifndef BSHIP_BSHIP_H
#define BSHIP_BSHIP_H

#include <string>
#include <vector>


using namespace std;

class BShip {
private:
    //Is sunk?
    bool sunk = false;

    //size (min = 2, max = 5)
    int size;

    //is it horizontally aligned? (if not, then it is vertical)
    bool horizontal;

    //starting coordinates in the grid
    vector<int> coords;

    //tracks how many times its been hit
    int hits=0;

    //name
    string myName;


public:
    //Constructor
    BShip(string name, int _size, bool horizontal, vector<int> coords);
    BShip() : BShip("", 0, false, (vector<int>(2,-1))){};

    //Setters
    void sink();
    void hit();

    //Getters
    string getName();
    bool isSunk();
    bool isHorizontal();
    int getHits();
    vector<int> getCoords();
    int getRow();
    int getCol();
    int getSize();
};


#endif //BSHIP_BSHIP_H
