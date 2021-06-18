#include "IBlock.h"
#include "Cell.h"
using namespace std;

std::vector<int> IBlock::getOldCoordinates() {
    return oldCoordinates;
}
std::vector<int> IBlock::getNewCoordinates() {
    return newCoordinates;
}
void IBlock::changeOldCoordinates(std::vector<int> changed) {
    int size = changed.size();
    for (int i = 0; i < size; i++) {
        oldCoordinates[i] = changed[i];
    }
}

int IBlock::getOrientation() {
    return orientation;
}

std::vector<int> IBlock::getPointers () {
    return newCoordinates;
}

// nullifies all cell pointers in block
void IBlock::nullify() {
    vector<int> temp;
    brdptr->notify(newCoordinates, temp, nullptr );
}

void IBlock::rotateC()  {
    //uses cellptr1 for reference
    int x , y;
    x = newCoordinates[0];
    y = newCoordinates[1];

    //creates vector of old coordinates
    std::vector<int> old = newCoordinates;
    // checking orientation
    if (orientation == 1 || orientation == 3) {
        //checking that rotation does not go off the board and
        //  that potential spaces are empty
        if (brdptr->cellCheck((x - 1), y) &&
            brdptr->cellCheck((x - 2), y) &&
            brdptr->cellCheck((x - 3), y)) {
            //create vector of new positions
            std::vector<int> newvec {(x - 3), y, (x - 2), y, (x - 1), y, x, y};
            //notify observers
            brdptr->notify(old, newvec, make_shared<IBlock>(*this));
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
    } else {
        // checking that rotation does not go off the board and
        //  that potential spaces are empty
        if ((y + 3) <= 10 &&
            brdptr->cellCheck((x + 3), (y + 1)) &&
            brdptr->cellCheck((x + 3), (y + 2)) &&
            brdptr->cellCheck((x + 3), (y + 3))) {
            //create vector of new positions
            std::vector<int> newvec {(x + 3), y, (x + 3), (y + 1),
                                     (x + 3), (y + 2), (x + 3), (y + 3)};
            //notify observers
            brdptr->notify(old, newvec, make_shared<IBlock>(*this));
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

void IBlock::rotateCC() {
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

void IBlock::changeCellPTRS(std::vector<int> vec) {
    newCoordinates = vec;
}

bool IBlock::down() {
    //uses cellptr1 for reference
    int x , y;
    x = newCoordinates[0];
    y = newCoordinates[1];

    //creates vector of old coordinates
    std::vector<int> old = newCoordinates;

    if (orientation == 1 || orientation == 3) {
        // check if cells below are empty so block can be moved down
        // check to see if viable
        if ((x + 1) <= 17 &&
            brdptr->cellCheck((x + 1), y) &&
            brdptr->cellCheck((x + 1), (y + 1)) &&
            brdptr->cellCheck((x + 1), (y + 2)) &&
            brdptr->cellCheck((x + 1), (y + 3))) {
            //create vector of new positions
            std::vector<int> newvec {(x + 1), y, (x + 1), (y + 1),
                                     (x + 1), (y + 2), (x + 1), (y + 3)};
            //notify observers
            brdptr->notify(old, newvec, make_shared<IBlock>(*this));
            //change CellPtrs to new positions
            changeCellPTRS(newvec);
            newCoordinates = newvec;
            return true;
        }
    }
    else {
        // check if cells below are empty so block can be moved down
        if ((x + 4) <= 17 &&
            brdptr->cellCheck((x + 4), y)) {
            //create vector of new positions
            std::vector<int> newvec {(x + 1), y, (x + 2), y,
                                     (x + 3), y, (x + 4), y};
            //notify observers
            brdptr->notify(old, newvec, make_shared<IBlock>(*this));
            //change CellPtrs to new positions
            changeCellPTRS(newvec);
            newCoordinates = newvec;
            return true;
        }
    }
    return false;
}

void IBlock::right() {
    //uses cellptr1 for reference
    int x , y;
    x = newCoordinates[0];
    y = newCoordinates[1];

    //creates vector of old coordinates
    std::vector<int> old = newCoordinates;

    if (orientation == 1 || orientation == 3) {
        // check if cells right are empty so block can be moved right
        if ((y + 4) <= 10 &&
            brdptr->cellCheck(x, (y + 4))) {
            //create vector of new positions
            std::vector<int> newvec {x, (y + 1), x, (y + 2),
                                     x, (y + 3), x, (y + 4)};
            //notify observers
            brdptr->notify(old, newvec, make_shared<IBlock>(*this));
            //change CellPtrs to new positions
            changeCellPTRS(newvec);
            newCoordinates = newvec;
        }
    }
    else {
        if ((y + 1) <= 10 &&
            brdptr->cellCheck(x, (y + 1)) &&
            brdptr->cellCheck((x + 1), (y + 1)) &&
            brdptr->cellCheck((x + 2), (y + 1)) &&
            brdptr->cellCheck((x + 3), (y + 1))) {
            //create vector of new positions
            std::vector<int> newvec {x, (y + 1), (x + 1), (y + 1),
                                     (x + 2), (y + 1), (x + 3), (y + 1)};
            //notify observers
            brdptr->notify(old, newvec, make_shared<IBlock>(*this));
            //change CellPtrs to new positions
            changeCellPTRS(newvec);
            newCoordinates = newvec;
        }
    }
}

void IBlock::left() {
    //uses cellptr1 for reference
    int x , y;
    x = newCoordinates[0];
    y = newCoordinates[1];

    //creates vector of old coordinates
    std::vector<int> old = newCoordinates;

    if (orientation == 1 || orientation == 3) {
        // check if cells right are empty so block can be moved right
        if ((y - 1) >= 0 &&
            brdptr->cellCheck(x, (y - 1))) {
            //create vector of new positions
            std::vector<int> newvec {x, (y - 1), x, y, x, (y + 1), x, (y + 2)};
            //notify observers
            brdptr->notify(old, newvec, make_shared<IBlock>(*this));
            //change CellPtrs to new positions
            changeCellPTRS(newvec);
            newCoordinates = newvec;
        }
    }
    else {
        if ((y - 1) >= 0 &&
            brdptr->cellCheck(x, (y - 1)) &&
            brdptr->cellCheck((x + 1), (y - 1)) &&
            brdptr->cellCheck((x + 2), (y - 1)) &&
            brdptr->cellCheck((x + 3), (y - 1))) {
            //create vector of new positions
            std::vector<int> newvec {x, (y - 1), (x + 1), (y - 1),
                                     (x + 2), (y - 1), (x + 3), (y - 1)};
            //notify observers
            brdptr->notify(old, newvec, make_shared<IBlock>(*this));
            //change CellPtrs to new positions
            changeCellPTRS(newvec);
            newCoordinates = newvec;
        }
    }
}

void IBlock::drop() {
    while (down()) {}
    brdptr->printGraphicsDisplay(make_shared<IBlock>(*this));
}

int IBlock::getLevel() {
    return level;
}

void IBlock::changeLevel(int new_level) {
    level = new_level;
}

int IBlock::getActiveCells() {
    return *activeCells;
}

void IBlock::changeActiveCells(int destroyed) {
    *activeCells -= destroyed;
}

string IBlock::getLetter() {
    return letter;
}

void IBlock::changeLetter(string l) {
    letter = l;
}
std::vector<int> IBlock::getBottomLeft() {
	int x, y;
	y = newCoordinates[1];
	x = newCoordinates[0];
	std::vector<int> bottomLeft;
	if (orientation == 1 || orientation == 3) {
		bottomLeft.emplace_back(x);
		bottomLeft.emplace_back(y);
	}
	else {
		bottomLeft.emplace_back(x + 4);
		bottomLeft.emplace_back(y);
	}
	return bottomLeft;
}






