//
// Created by Michal Bodzianowski on 3/1/18.
//

#include "BShip.h"

BShip::BShip(string name, int _size, bool horizontal, vector<int> coords) {
    myName = name;
    size = _size;
    this->horizontal = horizontal;
    this->coords = coords;
}

void BShip::sink() {
    sunk = true;
}

void BShip::hit() {
    hits+=1;
    if(hits >= size){
        sunk = true;
    }
}

string BShip::getName() {
    return myName;
}

bool BShip::isSunk() {
    return sunk;
}

bool BShip::isHorizontal() {
    return horizontal;
}

int BShip::getHits() {
    return hits;
}

vector<int> BShip::getCoords() {
    return coords;
}

int BShip::getRow() {
    return coords[0];
}

int BShip::getCol() {
    return coords[1];
}

int BShip::getSize() {
    return size;
}