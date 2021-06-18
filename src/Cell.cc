#include "Cell.h"

using namespace std;

void Cell::setCoordinates(int r, int c) {
    row = r;
    col = c;
}

int Cell::getRow() {
    return row;
}

int Cell::getCol() {
    return col;
}

std::shared_ptr<Block> Cell::getBptr() {
    return bptr;
}

//changes the block pointer of the cell to new block pointer b
void Cell::changePtr(shared_ptr<Block> b) {
    bptr = b;
}

bool Cell::checkEmpty() {
    if (bptr) {
        return false;
    }
    return true;
}
bool Cell::getHint() {
    return true;
}

bool Cell::changeHint() {
    return true;
}

string Cell::getLetter() {
    return letter;
}

void Cell::changeLetter(string newletter) {
    letter = newletter;
}

void Cell::nullify() {
    letter = "";
    bptr = nullptr;
}

void Cell::notify(int newrow, int newcol, std::shared_ptr<Cell> c) {}





