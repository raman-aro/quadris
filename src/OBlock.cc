#include "OBlock.h"
#include "Cell.h"
using namespace std;

std::vector<int> OBlock::getOldCoordinates() {
    return oldCoordinates;
}
std::vector<int> OBlock::getNewCoordinates() {
    return newCoordinates;
}
void OBlock::changeOldCoordinates(std::vector<int> changed) {
    int size = changed.size();
    for (int i = 0; i < size; i++) {
        oldCoordinates[i] = changed[i];
    }
}

int OBlock::getOrientation() {
    return orientation;
}

std::vector<int> OBlock::getPointers () {
    return newCoordinates;
}

void OBlock::rotateC()  {
    if (orientation ==4) {
        orientation = 1;
    } else {
        ++orientation;
    }
}

void OBlock::rotateCC() {
    if (orientation ==0) {
        orientation = 4;
    } else {
        --orientation;
    }
}

// nullifies all cell pointers in block
void OBlock::nullify() {
    vector<int> temp;
    brdptr->notify(newCoordinates, temp, nullptr );
}

bool OBlock::down() {
    //uses cellptr1 for reference
    int x , y;
    x = newCoordinates[0];
    y = newCoordinates[1];

    //creates vector of old coordinates
    std::vector<int> old = newCoordinates;

    if ((x + 2) <= 17 &&
        brdptr->cellCheck((x + 2), y) &&
        brdptr->cellCheck(x + 2, (y + 1))) {
        //create vector of new positions
        std::vector<int> newvec{x + 1, y, x + 1, y + 1, x + 2, y, x + 2, y + 1};
        //notify observers
        brdptr->notify(old, newvec, make_shared<OBlock>(*this));
        //change CellPtrs to new positions
        changeCellPTRS(newvec);
        newCoordinates = newvec;
        return true;
    }
    return false;
}

void OBlock::right() {
    //uses cellptr1 for reference
    int x , y;
    x = newCoordinates[0];
    y = newCoordinates[1];

    //creates vector of old coordinates
    std::vector<int> old = newCoordinates;

    if ((y + 2) <= 10 &&
        brdptr->cellCheck(x, y + 2) &&
        brdptr->cellCheck(x + 1, (y + 2))) {
        //create vector of new positions
        std::vector<int> newvec{x, y + 1, x, y + 2, x + 1, y + 1, x + 1, y + 2};
        //notify observers
        brdptr->notify(old, newvec, make_shared<OBlock>(*this));
        //change CellPtrs to new positions
        changeCellPTRS(newvec);
        newCoordinates = newvec;
    }
}

void OBlock::left() {
    //uses cellptr1 for reference
    int x , y;
    x = newCoordinates[0];
    y = newCoordinates[1];

    //creates vector of old coordinates
    std::vector<int> old = newCoordinates;

    if ((y - 1) >= 0 &&
        brdptr->cellCheck(x, y - 1) &&
        brdptr->cellCheck(x + 1, (y - 1))) {
        //create vector of new positions
        std::vector<int> newvec{x, y - 1, x, y, x + 1, y - 1, x + 1, y};
        //notify observers
        brdptr->notify(old, newvec, make_shared<OBlock>(*this));
        //change CellPtrs to new positions
        changeCellPTRS(newvec);
        newCoordinates = newvec;
    }
}

void OBlock::drop() {
    while (down()) {}
    brdptr->printGraphicsDisplay(make_shared<OBlock>(*this));
}

int OBlock::getLevel() {
    return level;
}

void OBlock::changeLevel(int new_level) {
    level = new_level;
}

int OBlock::getActiveCells() {
    return *activeCells;
}

void OBlock::changeActiveCells(int destroyed) {
    *activeCells -= destroyed;
}

string OBlock::getLetter() {
    return letter;
}

void OBlock::changeLetter(string l) {
    letter = l;
}

void OBlock::changeCellPTRS(std::vector<int> vec) {
    newCoordinates = vec;
}

std::vector<int> OBlock::getBottomLeft() {
    int x, y;
    y = newCoordinates[1];
    x = newCoordinates[0];
    std::vector<int> bottomLeft;
    bottomLeft.emplace_back(x + 1);
    bottomLeft.emplace_back(y);
    return bottomLeft;
}


