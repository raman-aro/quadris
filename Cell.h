#ifndef QUADRIS_CELL_H
#define QUADRIS_CELL_H

#include <memory>
#include <string>
#include "Block.h"

class Cell {
    std::shared_ptr<Block> bptr;
    int row;
    int col;
    bool hint;
    std::string letter;
public:
    Cell(): bptr(nullptr) {
        hint = false;
        letter = "";
    }
    int getRow();
    int getCol();
    std::shared_ptr<Block> getBptr();
    void setCoordinates(int r, int c);
    void changePtr(std::shared_ptr<Block> b);
    bool checkEmpty();
    bool getHint();
    bool changeHint();
    std::string getLetter();
    void changeLetter(std::string newletter);
    void notify(int newrow, int newcol, std::shared_ptr<Cell> c);
    void nullify();
};


#endif //QUADRIS_CELL_H




