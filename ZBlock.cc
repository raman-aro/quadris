
#include "ZBlock.h"
#include "Cell.h"
using namespace std;

std::vector<int> ZBlock::getOldCoordinates() {
    return oldCoordinates;
}
std::vector<int> ZBlock::getNewCoordinates() {
    return newCoordinates;
}
void ZBlock::changeOldCoordinates(std::vector<int> changed) {
    int size = changed.size();
    for (int i = 0; i < size; i++) {
        oldCoordinates[i] = changed[i];
    }
}


void ZBlock::nullify() {
    vector<int> temp;
    brdptr->notify(newCoordinates, temp, nullptr );
}

int ZBlock::getOrientation() {
    return orientation;
}

std::vector<int> ZBlock::getPointers () {
    return newCoordinates;
}

void ZBlock::rotateC()  {
    //uses cellptr1 for reference
    int x , y;
    x = newCoordinates[0];
    y = newCoordinates[1];

    //creates vector of old coordinates
    std::vector<int> old = newCoordinates;
    // checking orientation
    if (orientation == 1 || orientation == 3) {
        //checking that rotation does not go off the board and that
        //    potential spaces are empty
        if ((y + 1) <= 10 &&
                brdptr->cellCheck(x + 1, y) &&
                brdptr->cellCheck(x - 1, y + 1)) {
            //create vector of new positions
            std::vector<int> newvec {(x - 1), y + 1, (x), y + 1, x, y, x + 1, y};
            //notify observers
            brdptr->notify(old, newvec, make_shared<ZBlock>(*this));
            //change CellPtrs to new positions
            changeCellPTRS(newvec);
            newCoordinates = newvec;
            //increment orientation
            if (orientation == 4) {
                orientation = 1;
            } else {
                ++orientation;
            }
        }
    }
    else {
        // checking that rotation does not go off the board and
        //      that potential spaces are empty
        if ((y + 1) <= 10 &&
                brdptr->cellCheck(x + 2, y) &&
                brdptr->cellCheck(x + 2, y + 1)) {
            //create vector of new positions
            std::vector<int> newvec {(x + 1), y - 1, (x + 1), (y), (x + 2), (y), (x + 2), (y + 1)};
            //notify observers
            brdptr->notify(old, newvec, make_shared<ZBlock>(*this));
            //change CellPtrs to new positions
            changeCellPTRS(newvec);
            newCoordinates = newvec;
            //increment orientation
            if (orientation == 4) {
                orientation = 1;
            } else {
                ++orientation;
            }
        }
    }

}

void ZBlock::rotateCC() {
    int orientationsuccess = orientation;
    rotateC();
    if (orientationsuccess != orientation) {
        //decrement orientation
        if (orientation == 1) {
            orientation = 3;
        } else if (orientation == 2) {
            orientation = 4;
        } else {
            orientation -= 2;
        }
    }
}
void ZBlock::changeCellPTRS(std::vector<int> vec) {
    newCoordinates = vec;
}

bool ZBlock::down() {
    //uses cellptr1 for reference
    int x , y;
    x = newCoordinates[0];
    y = newCoordinates[1];

    //creates vector of old coordinates
    std::vector<int> old = newCoordinates;

    if (orientation == 1) {
        // check if cells below are empty so block can be moved down
        if ((x + 2) <= 17 &&
                brdptr->cellCheck(x + 1, y) &&
                brdptr->cellCheck(x + 2, y + 1) &&
                brdptr->cellCheck(x + 2, y + 2)) {
            //create vector of new positions
            std::vector<int> newvec {(x + 1), y, (x + 1), (y + 1), x + 2, (y + 1), x + 2, (y + 2)};
            //notify observers
            brdptr->notify(old, newvec, make_shared<ZBlock>(*this));
            //change CellPtrs to new positions
            changeCellPTRS(newvec);
            newCoordinates = newvec;
            return true;
        }
    }
    else {
        if ((x + 3) <= 17 &&
                brdptr->cellCheck(x + 2, y) &&
                brdptr->cellCheck(x + 3, y - 1)) {
            //create vector of new positions
            std::vector<int> newvec {(x + 1), y, (x + 2), y, (x + 2), (y - 1), (x + 3), (y - 1)};
            //notify observers
            brdptr->notify(old, newvec, make_shared<ZBlock>(*this));
            //change CellPtrs to new positions
            changeCellPTRS(newvec);
            newCoordinates = newvec;
            return true;
        }
    }
    return false;
}

void ZBlock::right() {
    //uses cellptr1 for reference
    int x , y;
    x = newCoordinates[0];
    y = newCoordinates[1];

    //creates vector of old coordinates
    std::vector<int> old = newCoordinates;

    if (orientation == 1) {
        // check if cells to the right are empty so block can be moved right
        if ((y + 3) <= 10 &&
                brdptr->cellCheck(x, y + 2) &&
                brdptr->cellCheck(x + 1, y + 3)) {
            //create vector of new positions
            std::vector<int> newvec {x, y + 1, x, y + 2, x + 1, y + 2, x + 1, (y + 3)};
            //notify observers
            brdptr->notify(old, newvec, make_shared<ZBlock>(*this));
            //change CellPtrs to new positions
            changeCellPTRS(newvec);
            newCoordinates = newvec;
        }
    }
    else {
        if ((y + 1) <= 10 &&
                brdptr->cellCheck(x, y + 1) &&
                brdptr->cellCheck(x + 1, y + 1) &&
                brdptr->cellCheck(x + 2, y)) {
            //create vector of new positions
            std::vector<int> newvec {x, y + 1, x + 1, y + 1, x + 1, y, x + 2, (y)};
            //notify observers
            brdptr->notify(old, newvec, make_shared<ZBlock>(*this));
            //change CellPtrs to new positions
            changeCellPTRS(newvec);
            newCoordinates = newvec;
        }
    }
}

void ZBlock::left() {
    //uses cellptr1 for reference
    int x , y;
    x = newCoordinates[0];
    y = newCoordinates[1];

    //creates vector of old coordinates
    std::vector<int> old = newCoordinates;

    if (orientation == 1) {
        // check if cells to the left are empty so block can be moved left
        if ((y - 1) >= 0 &&
                brdptr->cellCheck(x, y - 1) &&
                brdptr->cellCheck(x + 1, y)) {
            //create vector of new positions
            std::vector<int> newvec {x, y - 1, x, y, x + 1, y, x + 1, (y + 1)};
            //notify observers
            brdptr->notify(old, newvec, make_shared<ZBlock>(*this));
            //change CellPtrs to new positions
            changeCellPTRS(newvec);
            newCoordinates = newvec;
        }
    }
    else {
        if ((y - 2) >= 0 &&
                brdptr->cellCheck(x, y - 1) &&
                brdptr->cellCheck(x + 1, y - 2) &&
                brdptr->cellCheck(x + 2, y - 2)) {
            //create vector of new positions
            std::vector<int> newvec {x, y - 1, x + 1, y - 1, x + 1, y - 2, x + 2, (y - 2)};
            //notify observers
            brdptr->notify(old, newvec, make_shared<ZBlock>(*this));
            //change CellPtrs to new positions
            changeCellPTRS(newvec);
            newCoordinates = newvec;
        }
    }
}

void ZBlock::drop() {
    while (down()) {}
    brdptr->printGraphicsDisplay(make_shared<ZBlock>(*this));
}
int ZBlock::getLevel() {
    return level;
}

void ZBlock::changeLevel(int new_level) {
    level = new_level;
}

int ZBlock::getActiveCells() {
    return activeCells;
}

void ZBlock::changeActiveCells(int destroyed) {
    activeCells -= destroyed;
}

string ZBlock::getLetter() {
    return letter;
}

void ZBlock::changeLetter(string l) {
    letter = l;
}

std::vector<int> ZBlock::getBottomLeft() {

    int x, y;

    y = newCoordinates[1];
    x = newCoordinates[0];

    std::vector<int> bottomLeft;

    if (orientation == 1) {
        bottomLeft.emplace_back(x + 1);
        bottomLeft.emplace_back(y);
    }
    else {
        bottomLeft.emplace_back(x + 2);
        bottomLeft.emplace_back(y - 1);
    }

    return bottomLeft;
}
