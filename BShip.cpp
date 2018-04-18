//
// Created by Michal Bodzianowski on 3/1/18.
//

#include "BShip.h"

//Only constructor as all fields ARE required.
BShip::BShip(string name, int _size, bool horizontal, vector<int> coords) {
    myName = name;
    size = _size;
    this->horizontal = horizontal;
    this->coords = coords;
}

//Manually sinks the ship.
void BShip::sink() {
    sunk = true;
}

//Manually log a hit on the ship. Location is arbitrary in
//determining whether it has sunk, and is handled by BShipGrid instead
void BShip::hit() {
    hits+=1;
    if(hits >= size){
        sunk = true;
    }
}

//Get the name of the ship.
string BShip::getName() {
    return myName;
}

//Get whether the ship is sunk.
bool BShip::isSunk() {
    return sunk;
}

//Get whether the ship is horizontal
bool BShip::isHorizontal() {
    return horizontal;
}

//Get the amount of hits on the ship.
int BShip::getHits() {
    return hits;
}

//Get the ships (lead) coordinates on the grid
vector<int> BShip::getCoords() {
    return coords;
}

//Get the row the ship is on (int form)
int BShip::getRow() {
    return coords[0];
}

//Get the col the ship is on (int form)
int BShip::getCol() {
    return coords[1];
}

//Get the ships sisze/length
int BShip::getSize() {
    return size;
}