
#include "TBlock.h"
#include "Cell.h"
using namespace std;

std::vector<int> TBlock::getOldCoordinates() {
    return oldCoordinates;
}
std::vector<int> TBlock::getNewCoordinates() {
    return newCoordinates;
}
void TBlock::changeOldCoordinates(std::vector<int> changed) {
    int size = changed.size();
    for (int i = 0; i < size; i++) {
        oldCoordinates[i] = changed[i];
    }
}

int TBlock::getOrientation() {
    return orientation;
}

std::vector<int> TBlock::getPointers () {
    return newCoordinates;
}

// nullifies all cell pointers in block
void TBlock::nullify() {
    vector<int> temp;
    brdptr->notify(newCoordinates, temp, nullptr );
}

void TBlock::rotateC() {
    //uses cellptr1 for reference
    int x , y;
    x = newCoordinates[0];
    y = newCoordinates[1];

    //creates vector of old coordinates
    std::vector<int> old = newCoordinates;
    // checking orientation
    if (orientation == 1) {
        //checking that rotation does not go off the board and
        //  that potential spaces are empty
        if (brdptr->cellCheck((x - 2), y)) {
            //create vector of new positions
            std::vector<int> newvec{(x - 1), y - 1, (x - 2), y, (x - 1), (y), x, y};
            //notify observers
            brdptr->notify(old, newvec, make_shared<TBlock>(*this));
            //change CellPtrs to new positions
            changeCellPTRS(newvec);
            newCoordinates = newvec;
            orientation = 2;
        }
    } else if (orientation == 2) {
        // checking that rotation does not go off the board and
        //  that potential spaces are empty
        if ((y + 2) <= 10
                && brdptr->cellCheck((x + 1), y)
                && brdptr->cellCheck((x + 1), (y + 2))) {
            //create vector of new positions
            std::vector<int> newvec{x, y + 1, x + 1, y + 2, x + 1, y + 1, x + 1, y};
            //notify observers
            brdptr->notify(old, newvec, make_shared<TBlock>(*this));
            //change CellPtrs to new positions
            changeCellPTRS(newvec);
            newCoordinates = newvec;
            orientation = 3;
        }
    } else if (orientation == 3) {
        // checking that rotation does not go off the board and
        //  that potential spaces are empty
        if (brdptr->cellCheck(x, (y - 1))
                && brdptr->cellCheck((x - 1), (y - 1))) {
            //create vector of new positions
            std::vector<int> newvec{x, y, x + 1, y - 1, x, y - 1, x - 1, y - 1};
            //notify observers
            brdptr->notify(old, newvec, make_shared<TBlock>(*this));
            //change CellPtrs to new positions
            changeCellPTRS(newvec);
            newCoordinates = newvec;
            orientation = 4;
        }
    }
    else {
        if ((y + 1) <= 10
                && brdptr->cellCheck(x + 1, y)
                && brdptr->cellCheck(x, y + 1)) {
            //create vector of new positions
            std::vector<int> newvec{x + 1, y, x, y - 1, x, y, x, y + 1};
            //notify observers
            brdptr->notify(old, newvec, make_shared<TBlock>(*this));
            //change CellPtrs to new positions
            changeCellPTRS(newvec);
            newCoordinates = newvec;
            orientation = 1;
        }
    }
}

void TBlock::rotateCC() {
    //uses cellptr1 for reference
    int x , y;
    x = newCoordinates[0];
    y = newCoordinates[1];

    //creates vector of old coordinates
    std::vector<int> old = newCoordinates;
    // checking orientation
    if (orientation == 1) {
        //checking that rotation does not go off the board and
        //  that potential spaces are empty
        if (brdptr->cellCheck(x, (y - 1))
                && brdptr->cellCheck((x - 2), (y - 1))) {
            //create vector of new positions
            std::vector<int> newvec{x - 1, y, x, y - 1, x - 1, y - 1, x - 2, y - 1};
            //notify observers
            brdptr->notify(old, newvec, make_shared<TBlock>(*this));
            //change CellPtrs to new positions
            changeCellPTRS(newvec);
            newCoordinates = newvec;
            orientation = 4;
        }
    } else if (orientation == 2) {
        // checking that rotation does not go off the board and
        //  that potential spaces are empty
        if ((y + 2) <= 10
                && brdptr->cellCheck(x, y + 2)) {
            //create vector of new positions
            std::vector<int> newvec{x + 1, y + 1, x, y, x, y + 1, x, y + 2};
            //notify observers
            brdptr->notify(old, newvec, make_shared<TBlock>(*this));
            //change CellPtrs to new positions
            changeCellPTRS(newvec);
            newCoordinates = newvec;
            orientation = 1;
        }
    } else if (orientation == 3) {
        // checking that rotation does not go off the board and
        //  that potential spaces are empty
        if (brdptr->cellCheck(x, (y - 1))
                && brdptr->cellCheck((x - 1), y)) {
            //create vector of new positions
            std::vector<int> newvec{x, y - 1, x - 1, y, x, y, x + 1, y};
            //notify observers
            brdptr->notify(old, newvec, make_shared<TBlock>(*this));
            //change CellPtrs to new positions
            changeCellPTRS(newvec);
            newCoordinates = newvec;
            orientation = 2;
        }
    }
    else {
        if ((y + 1) <= 10
                && brdptr->cellCheck(x + 1, y)
                && brdptr->cellCheck(x + 1, y + 1)) {
            //create vector of new positions
            std::vector<int> newvec{x, y, x + 1, y + 1, x + 1, y, x + 1, y - 1};
            //notify observers
            brdptr->notify(old, newvec, make_shared<TBlock>(*this));
            //change CellPtrs to new positions
            changeCellPTRS(newvec);
            newCoordinates = newvec;
            orientation = 3;
        }
    }
}

bool TBlock::down() {
    //uses cellptr1 for reference
    int x , y;
    x = newCoordinates[0];
    y = newCoordinates[1];

    //creates vector of old coordinates
    std::vector<int> old = newCoordinates;

    if (orientation == 1) {
        // check if cells right are empty so block can be moved right
        if ((x + 1) <= 17 &&
                brdptr->cellCheck(x + 1, y) &&
                brdptr->cellCheck(x, (y - 1)) &&
                brdptr->cellCheck(x, y + 1))  {
            //create vector of new positions
            std::vector<int> newvec {x + 1, y, x, y - 1, x, y, x, y + 1};
            //notify observers
            brdptr->notify(old, newvec, make_shared<TBlock>(*this));
            //change CellPtrs to new positions
            changeCellPTRS(newvec);
            newCoordinates = newvec;
            return true;
        }
    }
    else if (orientation == 2) {
        if ((x + 2) <= 17 &&
                brdptr->cellCheck(x + 1, y) &&
                brdptr->cellCheck((x + 2), y + 1)) {
            //create vector of new positions
            std::vector<int> newvec {x + 1, y, x, y + 1, x + 1, y + 1, x + 2, y + 1};
            //notify observers
            brdptr->notify(old, newvec, make_shared<TBlock>(*this));
            //change CellPtrs to new positions
            changeCellPTRS(newvec);
            newCoordinates = newvec;
            return true;
        }
    }
    else if (orientation == 3) {
        if ((x + 2) <= 17 &&
                brdptr->cellCheck(x + 2, y) &&
                brdptr->cellCheck(x + 2, y + 1) &&
                brdptr->cellCheck(x + 2, y - 1)) {
            //create vector of new positions
            std::vector<int> newvec {x + 1, y, x + 2, y + 1, x + 2, y, x + 2, y - 1};
            //notify observers
            brdptr->notify(old, newvec, make_shared<TBlock>(*this));
            //change CellPtrs to new positions
            changeCellPTRS(newvec);
            newCoordinates = newvec;
            return true;
        }
    }
    else {
        if ((x + 2) <= 17 &&
                brdptr->cellCheck(x + 1, y) &&
                brdptr->cellCheck(x + 2, y - 1)) {
            //create vector of new positions
            std::vector<int> newvec {x + 1, y, x + 2, y - 1, x + 1, y - 1, x, y - 1};
            //notify observers
            brdptr->notify(old, newvec, make_shared<TBlock>(*this));
            //change CellPtrs to new positions
            changeCellPTRS(newvec);
            newCoordinates = newvec;
            return true;
        }
    }
    return false;
}

void TBlock::right() {
    //uses cellptr1 for reference
    int x , y;
    x = newCoordinates[0];
    y = newCoordinates[1];

    //creates vector of old coordinates
    std::vector<int> old = newCoordinates;

    if (orientation == 1) {
        // check if cells right are empty so block can be moved right
        if ((y + 2) <= 10 &&
                brdptr->cellCheck(x, (y + 1)) &&
                brdptr->cellCheck((x - 1), (y + 2))) {
            //create vector of new positions
            std::vector<int> newvec {x, y + 1, x - 1, y, x - 1, y + 1, x - 1, y + 2};
            //notify observers
            brdptr->notify(old, newvec, make_shared<TBlock>(*this));
            //change CellPtrs to new positions
            changeCellPTRS(newvec);
            newCoordinates = newvec;
        }
    }
    else if (orientation == 2) {
        if ((y + 2) <= 10 &&
                brdptr->cellCheck(x, y + 2) &&
                brdptr->cellCheck(x - 1, y + 2) &&
                brdptr->cellCheck((x + 1), (y + 2))) {
            //create vector of new positions
            std::vector<int> newvec {x, y + 1, x - 1, y + 2,
                                     x, y + 2, x + 1, y + 2};
            //notify observers
            brdptr->notify(old, newvec, make_shared<TBlock>(*this));
            //change CellPtrs to new positions
            changeCellPTRS(newvec);
            newCoordinates = newvec;
        }
    }
    else if (orientation == 3) {
        if ((y + 2) <= 10 &&
                brdptr->cellCheck(x, y + 1) &&
                brdptr->cellCheck(x + 1, y + 2)) {
            //create vector of new positions
            std::vector<int> newvec {x, y + 1, x + 1, y + 2, x + 1, y + 1, x + 1, y};
            //notify observers
            brdptr->notify(old, newvec, make_shared<TBlock>(*this));
            //change CellPtrs to new positions
            changeCellPTRS(newvec);
            newCoordinates = newvec;
        }
    }
    else {
        if ((y + 1) <= 10 &&
                brdptr->cellCheck(x, y + 1) &&
                brdptr->cellCheck(x - 1, y) &&
                brdptr->cellCheck(x + 1, y)) {
            //create vector of new positions
            std::vector<int> newvec {x, y + 1, x + 1, y, x, y, x - 1, y};
            //notify observers
            brdptr->notify(old, newvec, make_shared<TBlock>(*this));
            //change CellPtrs to new positions
            changeCellPTRS(newvec);
            newCoordinates = newvec;
        }
    }
}

void TBlock::left() {
    //uses cellptr1 for reference
    int x , y;
    x = newCoordinates[0];
    y = newCoordinates[1];

    //creates vector of old coordinates
    std::vector<int> old = newCoordinates;

    if (orientation == 1) {
        // check if cells right are empty so block can be moved right
        if ((y - 2) >= 0 &&
                brdptr->cellCheck(x, (y - 1)) &&
                brdptr->cellCheck((x - 1), (y - 2))) {
            //create vector of new positions
            std::vector<int> newvec {x, y - 1, x - 1, y - 2, x - 1, y - 1, x - 1, y};
            //notify observers
            brdptr->notify(old, newvec, make_shared<TBlock>(*this));
            //change CellPtrs to new positions
            changeCellPTRS(newvec);
            newCoordinates = newvec;
        }
    }
    else if (orientation == 2) {
        if ((y - 1) >= 0 &&
                brdptr->cellCheck(x, y - 1) &&
                brdptr->cellCheck(x - 1, y) &&
                brdptr->cellCheck((x + 1), (y))) {
            //create vector of new positions
            std::vector<int> newvec {x, y - 1, x - 1, y, x, y, x + 1, y};
            //notify observers
            brdptr->notify(old, newvec, make_shared<TBlock>(*this));
            //change CellPtrs to new positions
            changeCellPTRS(newvec);
            newCoordinates = newvec;
        }
    }
    else if (orientation == 3) {
        if ((y - 2) >= 0 &&
                brdptr->cellCheck(x, y - 1) &&
                brdptr->cellCheck(x + 1, y - 2)) {
            //create vector of new positions
            std::vector<int> newvec {x, y - 1, x + 1, y,
                                     x + 1, y - 1, x + 1, y - 2};
            //notify observers
            brdptr->notify(old, newvec, make_shared<TBlock>(*this));
            //change CellPtrs to new positions
            changeCellPTRS(newvec);
            newCoordinates = newvec;
        }
    }
    else {
        if ((y - 2) >= 0 &&
                brdptr->cellCheck(x, y - 2) &&
                brdptr->cellCheck(x - 1, y - 2) &&
                brdptr->cellCheck(x + 1, y - 2)) {
            //create vector of new positions
            std::vector<int> newvec {x, y - 1, x + 1, y - 2, x, y - 2, x - 1, y - 2};
            //notify observers
            brdptr->notify(old, newvec, make_shared<TBlock>(*this));
            //change CellPtrs to new positions
            changeCellPTRS(newvec);
            newCoordinates = newvec;
        }
    }
}

void TBlock::drop() {
    while (down()) {}
    brdptr->printGraphicsDisplay(make_shared<TBlock>(*this));
}

int TBlock::getLevel() {
    return level;
}

void TBlock::changeLevel(int new_level) {
    level = new_level;
}

int TBlock::getActiveCells() {
    return activeCells;
}

void TBlock::changeActiveCells(int destroyed) {
    activeCells -= destroyed;
}

string TBlock::getLetter() {
    return letter;
}

void TBlock::changeLetter(string l) {
    letter = l;
}

void TBlock::changeCellPTRS(std::vector<int> vec) {
    newCoordinates = vec;
}

std::vector<int> TBlock::getBottomLeft() {
    int x, y;
    y = newCoordinates[1];
    x = newCoordinates[0];
    std::vector<int> bottomLeft;
    if (orientation == 1) {
        bottomLeft.emplace_back(x);
        bottomLeft.emplace_back(y - 1);
    }
    else if (orientation == 2) {
        bottomLeft.emplace_back(x + 1);
        bottomLeft.emplace_back(y);
    }
    else if (orientation == 3) {
        bottomLeft.emplace_back(x + 1);
        bottomLeft.emplace_back(y - 1);
    }
    else {
        bottomLeft.emplace_back(x + 1);
        bottomLeft.emplace_back(y - 1);
    }
    return bottomLeft;
}


