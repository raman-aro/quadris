
#include "Board.h"
#include "Block.h"
#include "SBlock.h"
#include "IBlock.h"
#include "JBlock.h"
#include "LBlock.h"
#include "OBlock.h"
#include "TBlock.h"
#include "ZBlock.h"
#include <exception>

using namespace std;

void Board::gethint(std::shared_ptr<Block> n) {
    vector<int> bestCoordinates;
    if (!n) {
        //deletes hint
        tdPtr->hint(bestCoordinates, false);
        gdPtr->hint(hintCoordinates, false);
        return;
    }
    bestCoordinates = n->getPointers();
    bool mostCurrent = false;
    bool mostCurrentright = false;
    vector<int> currentCoordinates = n->getPointers();
    vector<int> newCoordinates;
    vector<int> currentCoordinatesright = n->getPointers();
    vector<int> newCoordinatesright;

//while loop that moves right on the board, one cell at a time
    while (true) {
        //if reached end of the board
        for (auto n : newCoordinatesright) {
            if (n == 10) {
                mostCurrentright = true;
                break;
            }
        }
        //if cant be updated anymore to the right
        if (mostCurrentright || newCoordinatesright == currentCoordinatesright) break;
        //while loop that moves all the way down, one cell at a time
        while (true) {
            for (int q = 0; q < newCoordinates.size(); q += 2) {
                if (newCoordinates[q] > bestCoordinates[q]) {
                    bestCoordinates = newCoordinates;
                    break;
                }
            }
            //if reached end of board
            for (auto n : newCoordinates) {
                if (n == 17) {
                    mostCurrent = true;
                    break;
                }
            }


            //if cant be updated anymore down
            if (mostCurrent || newCoordinates == currentCoordinates) break;
            currentCoordinates = movedownhint(currentCoordinates);
            newCoordinates = movedownhint(currentCoordinates);
            //updates best coordinates if lowest position is achieved

        } mostCurrent = false;
        currentCoordinatesright = moverighthint(currentCoordinatesright);
        currentCoordinates = currentCoordinatesright;
        newCoordinatesright = moverighthint(currentCoordinatesright);

    }
    hintCoordinates = bestCoordinates;
    //updates
    tdPtr->hint(bestCoordinates, true);
    gdPtr->hint(bestCoordinates, true);
}

vector<int> Board::moverighthint(vector<int> oldest) {
    vector<int> old = oldest;

    if (((old[1] != 10) &&
            //empty underneath
            ((board[old[0]][old[1] + 1]->checkEmpty()) ||
             //same underneath and not one below end
             ((board[old[0]][old[1] + 1]->getBptr()->getPointers() == old)
              && ((old[1] + 1) != 10)))) &&
            ((old[3] != 10) &&
             //empty underneath
             (board[old[2]][old[3] + 1]->checkEmpty()) ||
             //same underneath and not one below end
             ((board[old[2]][old[3] + 1]->getBptr()->getPointers() == old) && ((old[3] + 1) != 10))) &&
            ((old[5] != 10) &&
             (board[old[4]][old[5] + 1]->checkEmpty()) ||
             ((board[old[4]][old[5] + 1]->getBptr()->getPointers() == old) && ((old[5] + 1) != 10))) &&
            ((old[7] != 10) &&
             (board[old[6]][old[7] + 1]->checkEmpty()) ||
             ((board[old[6]][old[7] + 1]->getBptr()->getPointers() == old) && ((old[7] + 1) != 10)))) {
        for (int i = 1; i < old.size(); i += 2) {
            if ((old[i] != -1) && (old[i] != 10)) {
                old[i] += 1;
            }
        }
    }
    return old;
}

vector<int> Board::movedownhint(vector<int> oldest) {
    vector<int> old = oldest;

    if (((old[0] != 17) &&
            //empty underneath
            ((board[old[0] + 1][old[1]]->checkEmpty()) ||
             //same underneath and not one below end
             ((board[old[0] + 1][old[1]]->getBptr()->getPointers() == old)
              && ((old[0] + 1) != 17))
            )) &&
            ((old[2] != 17) &&
             //empty underneath
             (board[old[2] + 1][old[3]]->checkEmpty()) ||
             //same underneath and not one below end
             ((board[old[2] + 1][old[3]]->getBptr()->getPointers() == old) && ((old[2] + 1) != 17))) &&
            ((old[4] != 17) &&
             (board[old[4] + 1][old[5]]->checkEmpty()) ||
             ((board[old[4] + 1][old[5]]->getBptr()->getPointers() == old) && ((old[4] + 1) != 17))) &&
            ((old[6] != 17) &&
             (board[old[6] + 1][old[7]]->checkEmpty()) ||
             ((board[old[6] + 1][old[7]]->getBptr()->getPointers() == old) && ((old[6] + 1) != 17)))) {
        for (int i = 0; i < old.size(); i += 2) {
            if ((old[i] != -1) && (old[i] != 17)) {
                old[i] += 1;
            }
        }
    }
    return old;
}

void Board::printTextDisplay() {
    tdPtr->print(after, levelInt, score, highscore);
}

void Board::printNextGraphics(std::shared_ptr<Block> b) {
    if (GraphicsOn) {
        gdPtr->printNext(after);
    }
}

void Board::noGraphicsShowing() {
    GraphicsOn = false;
}

void Board::printGraphicsDisplay(std::shared_ptr<Block> b) {
    std::vector<int> oldCoordinates = b->getOldCoordinates();
    std::vector<int> newCoordinates = b->getNewCoordinates();
    if (GraphicsOn) {
        gdPtr->print(levelInt, score, highscore, oldCoordinates, newCoordinates, b);
    }
    int length = oldCoordinates.size();
    b->changeOldCoordinates(newCoordinates);
}

void Board::notify(std::vector<int> oldCoordinates,
                   std::vector<int> newCoordinates,
                   std::shared_ptr<Block> b) {
    int row, col;
    //nullifies old cells
    for (int i = 0; i < oldCoordinates.size(); i += 2) {
        //checks to ensure not an empty cell
        if (oldCoordinates[i] != -1) {
            row = oldCoordinates[i];
            col = oldCoordinates[i + 1];
            //nullifies the specified cells
            board[row][col]->nullify();
        }
    }

    //updates new cells
    for (int i = 0; i < newCoordinates.size(); i += 2) {
        //checks to ensure not an empty cell
        if (newCoordinates[i] != -1) {
            row = newCoordinates[i];
            col = newCoordinates[i + 1];
            //updates to letter and  block ptr
            string l;
            if (b) {
                l = b->getLetter();
            }
            //undefined behaviour
            else {
                l = "?";
            }
            board[row][col]->changeLetter(l);
            board[row][col]->changePtr(b);
        }
    }
    //updates CellPtrs, if they have not already been changed
    if (b) {
        b->changeCellPTRS(newCoordinates);
    }
    tdPtr->notify(oldCoordinates, newCoordinates, b);
}

//overloaded getBlock function used for swapping blocks
std::shared_ptr<Block> Board::getBlock(std::vector<int> newCoordinates,  std::shared_ptr<Block> b,
                                       std::string letter, int level, int orientation) {
    if (letter == "S") {
        //creates Sblock
        vector<int> old;
        std::vector<int> oldCoordinates = b->getOldCoordinates();

        SBlock sb(make_shared<Board>(*this), newCoordinates, level,
                  orientation);

        shared_ptr<SBlock> sbptr = make_shared<SBlock>(sb);
        notify(old, newCoordinates, sbptr);
        currentBlocks.emplace_back(sbptr);
        if (GraphicsOn) {
            gdPtr->print(level, -1, -1, oldCoordinates, newCoordinates, nullptr);
        }
        return sbptr;
    }
    else if (letter == "Z") {
        //creates Zblock
        vector<int> old;
        std::vector<int> oldCoordinates = b->getOldCoordinates();
        ZBlock sb(make_shared<Board>(*this), newCoordinates, level,
                  orientation);

        shared_ptr<ZBlock> sbptr = make_shared<ZBlock>(sb);
        notify(old, newCoordinates, sbptr);
        currentBlocks.emplace_back(sbptr);
        if (GraphicsOn) {
            gdPtr->print(level, -1, -1, oldCoordinates, newCoordinates, nullptr);
        }
        return sbptr;
    }
    else if (letter == "T") {
        //creates Tblock
        vector<int> old;
        std::vector<int> oldCoordinates = b->getOldCoordinates();
        TBlock sb(make_shared<Board>(*this), newCoordinates, level,
                  orientation);

        shared_ptr<TBlock> sbptr = make_shared<TBlock>(sb);
        notify(old, newCoordinates, sbptr);
        currentBlocks.emplace_back(sbptr);
        if (GraphicsOn) {
            gdPtr->print(level, -1, -1, oldCoordinates, newCoordinates, nullptr);
        }
        return sbptr;
    }
    else if (letter == "O") {
        //creates Oblock
        vector<int> old;
        std::vector<int> oldCoordinates = b->getOldCoordinates();
        OBlock sb(make_shared<Board>(*this), newCoordinates, level,
                  orientation);

        shared_ptr<OBlock> sbptr = make_shared<OBlock>(sb);
        notify(old, newCoordinates, sbptr);
        currentBlocks.emplace_back(sbptr);
        if (GraphicsOn) {
            gdPtr->print(level, -1, -1, oldCoordinates, newCoordinates, nullptr);
        }
        return sbptr;
    }
    else if (letter == "L") {
        //creates Lblock
        vector<int> old;
        std::vector<int> oldCoordinates = b->getOldCoordinates();
        LBlock sb(make_shared<Board>(*this), newCoordinates, level,
                  orientation);

        shared_ptr<LBlock> sbptr = make_shared<LBlock>(sb);
        notify(old, newCoordinates, sbptr);
        currentBlocks.emplace_back(sbptr);
        if (GraphicsOn) {
            gdPtr->print(level, -1, -1, oldCoordinates, newCoordinates, nullptr);
        }
        return sbptr;
    }
    else if (letter == "J") {
        //creates Jblock
        vector<int> old;
        std::vector<int> oldCoordinates = b->getOldCoordinates();
        JBlock sb(make_shared<Board>(*this), newCoordinates, level,
                  orientation);

        shared_ptr<JBlock> sbptr = make_shared<JBlock>(sb);
        notify(old, newCoordinates, sbptr);
        currentBlocks.emplace_back(sbptr);
        if (GraphicsOn) {
            gdPtr->print(level, -1, -1, oldCoordinates, newCoordinates, nullptr);
        }
        return sbptr;
    }
    else {
        //creates Iblock
        vector<int> old;
        std::vector<int> oldCoordinates = b->getOldCoordinates();
        IBlock sb(make_shared<Board>(*this), newCoordinates, level,
                  orientation);

        shared_ptr<IBlock> sbptr = make_shared<IBlock>(sb);
        notify(old, newCoordinates, sbptr);
        currentBlocks.emplace_back(sbptr);
        if (GraphicsOn) {
            gdPtr->print(level, -1, -1, oldCoordinates, newCoordinates, nullptr);
        }
        return sbptr;
    }
}


shared_ptr<Block> Board::getBlock(int levelnumber, string file, bool random, string norandomfile, int seed, bool seedbool) {
    levelInt = levelnumber;
    if (first) {
        blockLetter = level->getBlock(levelInt, file, random, norandomfile, seed, seedbool);
        first = false;
    }
    after = level->getBlock(levelInt, file, random, norandomfile, seed, seedbool);
    temp = blockLetter;
    blockLetter = after;
    if (temp == "S") {
        //checks if starting position is empty
        if (cellCheck(4, 0) && cellCheck(4, 1) && cellCheck(3, 1) && cellCheck(3, 2)) {
            //creates Sblock
            vector<int> newCoordinates = {4, 0, 4, 1, 3, 1, 3, 2};
            vector<int> old;
            //sending a pointer to the board, the starting coordinates, the level,
            //   and the orientation
            SBlock sb(make_shared<Board>(*this), newCoordinates, levelInt, 1);

            shared_ptr<SBlock> sbptr = make_shared<SBlock>(sb);
            notify(old, newCoordinates, sbptr);
            currentBlocks.emplace_back(sbptr);
            return sbptr;
        }
        else {
            //you lose
            gameOn = false;
            return nullptr;
        }
    }
    else if (temp == "O") {
        //checks if starting position is empty
        if (cellCheck(3, 0) && cellCheck(3, 1) && cellCheck(4, 0) && cellCheck(4, 1)) {
            //creates Oblock
            //updates textDisplay
            vector<int> newCoordinates = {3, 0, 3, 1, 4, 0, 4, 1};
            vector<int> old;
            OBlock ob(make_shared<Board>(*this), newCoordinates, levelInt, 1);
            shared_ptr<OBlock> obptr = make_shared<OBlock>(ob);


            notify(old, newCoordinates, obptr);
            currentBlocks.emplace_back(obptr);
            return obptr;
        }
        else {
            //you lose
            gameOn = false;
            return nullptr;
        }
    }
    else if (temp == "T") {
        //checks if starting position is empty
        if (cellCheck(4, 1) && cellCheck(3, 0) && cellCheck(3, 1) && cellCheck(3, 2)) {
            //creates Tblock
            //updates textDisplay
            vector<int> newCoordinates = {4, 1, 3, 0, 3, 1, 3, 2};
            vector<int> old;
            TBlock tb(make_shared<Board>(*this), newCoordinates, levelInt, 1);
            shared_ptr<TBlock> tbptr = make_shared<TBlock>(tb);


            notify(old, newCoordinates, tbptr);
            currentBlocks.emplace_back(tbptr);
            return tbptr;
        }
        else {
            //you lose
            gameOn = false;
            return nullptr;
        }
    }
    else if (temp == "Z") {
        //checks if starting position is empty
        if (cellCheck(3, 0) && cellCheck(3, 1) && cellCheck(4, 1) && cellCheck(4, 2)) {
            //creates Tblock
            //updates textDisplay
            vector<int> newCoordinates = {3, 0, 3, 1, 4, 1, 4, 2};
            vector<int> old;
            ZBlock zb(make_shared<Board>(*this), newCoordinates, levelInt, 1);
            shared_ptr<ZBlock> zbptr = make_shared<ZBlock>(zb);


            notify(old, newCoordinates, zbptr);
            currentBlocks.emplace_back(zbptr);
            return zbptr;
        }
        else {
            //you lose
            gameOn = false;
            return nullptr;
        }
    }
    else if (temp == "L") {
        //checks if starting position is empty
        if (cellCheck(4, 0) && cellCheck(4, 1) && cellCheck(4, 2) && cellCheck(3, 2)) {
            //creates Lblock
            //updates textDisplay
            vector<int> newCoordinates = {4, 0, 4, 1, 4, 2, 3, 2};
            vector<int> old;
            LBlock lb(make_shared<Board>(*this), newCoordinates, levelInt, 1);
            shared_ptr<LBlock> lbptr = make_shared<LBlock>(lb);


            notify(old, newCoordinates, lbptr);
            currentBlocks.emplace_back(lbptr);
            return lbptr;
        }
        else {
            //you lose
            gameOn = false;
            return nullptr;
        }
    }
    else if (temp == "J") {
        //checks if starting position is empty
        if (cellCheck(3, 0) && cellCheck(4, 0) && cellCheck(4, 1) && cellCheck(4, 2)) {
            //creates Jblock
            //updates textDisplay
            vector<int> newCoordinates = {3, 0, 4, 0, 4, 1, 4, 2};
            vector<int> old;

            JBlock jb(make_shared<Board>(*this), newCoordinates, levelInt, 1);
            shared_ptr<JBlock> jbptr = make_shared<JBlock>(jb);


            notify(old, newCoordinates, jbptr);
            currentBlocks.emplace_back(jbptr);
            return jbptr;
        }
        else {
            //you lose
            gameOn = false;
            return nullptr;
        }
    }
    else if (temp == "I") {
        //checks if starting position is empty
        if (cellCheck(3, 0) && cellCheck(3, 1) && cellCheck(3, 2) && cellCheck(3, 3)) {
            //creates Iblock
            vector<int> newCoordinates = {3, 0, 3, 1, 3, 2, 3, 3};
            vector<int> old;
            IBlock ib(make_shared<Board>(*this), newCoordinates, levelInt, 1);
            shared_ptr<IBlock> ibptr = make_shared<IBlock>(ib);


            notify(old, newCoordinates, ibptr);
            currentBlocks.emplace_back(ibptr);
            return ibptr;
        }
        else {
            //you lose
            gameOn = false;
            return nullptr;
        }
    }
    else {
        throw out_of_range("No More Blocks");
    }
}


bool Board::getgameStatus() {
    return gameOn;
}

void Board::changeGameStatus() {
    gameOn = !gameOn;
}

void Board::initialize(Xwindow &w) {
    score = 0;

    //delete previous grid
    board.clear();
    gdPtr = std::make_shared<GraphicsDisplay>(w);
    if (GraphicsOn) {
        gdPtr->updateScore(to_string(score), to_string(highscore));
        gdPtr->updateLevel(to_string(levelInt));
    }
    //make gameOn == true because default is false;
    changeGameStatus();

    //allocate new grid
    board.resize(18);

    for (int r = 0; r < board.size(); r++) {
        //resize each vector contained within board
        board[r].resize(11);
        for (int c = 0; c < board[r].size(); c++) {
            board[r][c] = make_shared<Cell>();
            board[r][c]->setCoordinates(r, c);
        }
    }
}

//done!
std::shared_ptr<Cell> Board::getCellPTR(int row, int col) {
    return board[row][col];
}


//if empty returns true, if not empty returns false
bool Board::cellCheck(int row, int col) {
    return board[row][col]->checkEmpty();
}

bool Board::resetGameChecker() {
    bool restartGame = false;
    for (int i = 0; i <= 10; i++) {
        restartGame = !cellCheck(2, i);
        if (restartGame == true) {
            break;
        }
    }
    return restartGame;
}

shared_ptr<Block>  Board::boardChecker() {
    shared_ptr<Block> bptr = currentBlocks[currentBlocks.size() - 1];
    int rowold;
    int colold;
    for (int p = 0; p < bptr->getPointers().size() ; ++p) {
        if (bptr->getPointers()[0] != -1) {
            rowold = bptr->getPointers()[0];
            colold = bptr->getPointers()[1];
        }
    }
    bptr = board[rowold][colold]->getBptr();
    int multiplier = 0;
    int i;
    int j;
    for (i = 0; i < 18; ++i) {
        for (j = 0; j < 11; ++j) {
            if (!board[i][j]->getBptr()) break;
        }
        if (j == 11) {
            ++multiplier;
            rowDelete(i, multiplier);

            //goes through every cell, and updates any blocks if preceding cell is empty
            for (int r = 17; r >= 3; r--) {
                for (int c = 0; c < board[r].size(); c++) {
                    if ( board[r][c]->checkEmpty()) {
                        for ( int occupied = r; occupied >= 3; occupied--) {
                            if (!board[occupied][c]->checkEmpty()) {
                                moveDown(board[occupied][c]->getBptr());
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    return bptr;
}

void Board::printeger() {

}

void Board::rowDelete(int row, int mulitplier) {
    int i;
    vector<int> oldVec;
    vector<int> newVec;
    for (i = 0; i < 11; ++i) {
        oldVec.emplace_back(row);
        oldVec.emplace_back(i);

        //Loops through the coordinates vector of the given cell's block
        //      and changes the deleted coordinates to -1 & -1.
        vector<int> old = board[row][i]->getBptr()->getPointers();
//loops through currentblocks to find the corresponding block
        int cb = 0;
        for (cb; cb < currentBlocks.size() ; ++cb) {
            if (currentBlocks[cb]->getPointers() == old) {
                break;
            }
        }
        for (int j = 0; j < old.size(); j += 2) {
            //if this cell has the same coordinates as the cell being deleted
            if ((old[j] == row) && (old[j + 1] == i)) {
                //set to negative values:
                old[j] = -1;
                old[j + 1] = -1;
            }
        }
        board[row][i]->getBptr()->changeActiveCells(1);
        currentBlocks[cb]->changeCellPTRS(old);
        board[row][i]->getBptr()->changeCellPTRS(old);
        // notify(newVec, old, board[row][i]->getBptr());
    }
    //increments score
    score += (levelInt + mulitplier) * (levelInt + mulitplier);
    if (score > highscore) {
        highscore = score;
    }
    //removes any blocks that are empty from currentBlocks
    for (int k = 0; k < currentBlocks.size();) {

        if (currentBlocks[k]->getActiveCells() == 0) {
            score += (currentBlocks[k]->getLevel() + 1) * (currentBlocks[k]->getLevel() + 1);
            if (score > highscore) {
                highscore = score;
            }
            currentBlocks.erase(currentBlocks.begin() + k);
        } else {
            ++k;
        }
    }
    if (GraphicsOn) {
        gdPtr->updateScore(to_string(score), to_string(highscore));
        gdPtr->updateLevel(to_string(levelInt));
    }

    //nullifies the row
    notify(oldVec, newVec, nullptr);
    if (GraphicsOn) {
        gdPtr->print(levelInt, score, highscore, oldVec, newVec, nullptr);
    }
}


void Board::moveDown(std::shared_ptr<Block> n) {
    int i;
    vector<int> old = n->getPointers();
//loops through currentblocks to find the corresponding block
    int cb = 0;
    for (cb; cb < currentBlocks.size() ; ++cb) {
        if (currentBlocks[cb]->getPointers() == old) {
            break;
        }
    }
    vector<int> eraseVec = n->getPointers();
    if (((old[0] == -1 || (old[0] == 17)) ||
            //empty underneath
            (board[old[0] + 1][old[1]]->checkEmpty()) ||
            //same underneath and not one below end
            ((board[old[0] + 1][old[1]]->getBptr()->getPointers() == old) && ((old[0] + 1) != 17))) &&
            ((old[2] == -1 || (old[2] == 17)) ||
             //empty underneath
             (board[old[2] + 1][old[3]]->checkEmpty()) ||
             //same underneath and not one below end
             ((board[old[2] + 1][old[3]]->getBptr()->getPointers() == old) && ((old[2] + 1) != 17))) &&
            ((old[4] == -1 || (old[4] == 17)) ||
             (board[old[4] + 1][old[5]]->checkEmpty()) ||
             ((board[old[4] + 1][old[5]]->getBptr()->getPointers() == old) && ((old[4] + 1) != 17))) &&
            ((old[6] == -1 || (old[6] == 17)) ||
             (board[old[6] + 1][old[7]]->checkEmpty()) ||
             ((board[old[6] + 1][old[7]]->getBptr()->getPointers() == old) && ((old[6] + 1) != 17)))) {
        for (int i = 0; i < old.size(); i += 2) {
            if ((old[i] != -1) && (old[i] != 17)) {
                old[i] += 1;
            }
        }
    }
    if (!(old == n->getPointers())) {
        //updates board
        notify(eraseVec, old, currentBlocks[cb]);
        if (GraphicsOn) {
            gdPtr->print(levelInt, score, highscore, eraseVec, old, n);
        }
        moveDown(currentBlocks[cb]);
    } else {
        return;
    }
}


int Board::bestSpot() {
    return 0;
}

void Board::print() {

}

void Board::addCurrentBlock() {

}

int Board::updateBlocksAdded(std::shared_ptr<Block> b) {
    return 0;
}

std::string Board::getNext() {
    return "";
}

int Board::getHighScore() {
    return highscore;
}

void Board::updateHighScore(int s) {
    highscore = s;
}

int Board::getScore() {
    return score;
}

int Board::updateScore() {
    return 0;
}

int Board::getWidth() {
    return width;
}

int Board::getHeight() {
    return height;
}

int Board::getLevel() {
    return levelInt;
}

void Board::setLevel(int num) {
    levelInt = num;
}

void Board::levelUp() {
    if (levelInt != 4) {
        levelInt++;
    }
}

void Board::levelDown() {
    if (levelInt != 0) {
        levelInt--;
    }
}

void Board::printGraphicsLevel() {
    if (GraphicsOn) {
        gdPtr->updateLevel(to_string(levelInt));
    }
}

int Board::getLastRowDel() {
    return lastRowDel;
}

std::shared_ptr<Block> Board::swapBlock(std::shared_ptr<Block> b, std::string newLetter) {
    std::vector<int> bottomLeft = b->getBottomLeft();
    string letter = b->getLetter();
    int orientation = b->getOrientation();
    int level = b->getLevel();
    int x , y;
    x = bottomLeft[0];
    y = bottomLeft[1];
    vector<int> oldCoordinates = b->getPointers();
    std::vector<int> v;
    b->nullify();
    if (newLetter == "S") {

        if (orientation == 1 || orientation == 3) {

            if (y + 2 <= 10 &&
                    cellCheck(x, y) &&
                    cellCheck(x, y + 1) &&
                    cellCheck(x - 1, y + 1) &&
                    cellCheck(x - 1, y + 2)) {

                vector<int> newCoordinates = {x, y, x, y + 1,
                                              x - 1, y + 1, x - 1, y + 2
                                             };

                tdPtr->notify(oldCoordinates, v, nullptr);
                currentBlocks.pop_back();
                return getBlock(newCoordinates, b, newLetter, level, orientation);
            }
            else {
                return b;
            }
        }
        else {
            if (y + 1 <= 10 &&
                    cellCheck(x - 2, y) &&
                    cellCheck(x - 1, y) &&
                    cellCheck(x - 1, y + 1) &&
                    cellCheck(x, y + 1)) {
                vector<int> newCoordinates = {x - 2, y, x - 1, y,
                                              x - 1, y + 1, x, y + 1
                                             };

                tdPtr->notify(oldCoordinates, v, nullptr);
                currentBlocks.pop_back();
                return getBlock(newCoordinates, b, newLetter, level, orientation);
            }
            else {
                return b;
            }
        }
    }
    else if (newLetter == "Z") {
        if (orientation == 1 || orientation == 3) {
            if (y + 2 <= 10 &&
                    cellCheck(x - 1, y) &&
                    cellCheck(x - 1, y + 1) &&
                    cellCheck(x, y + 1) &&
                    cellCheck(x, y + 2)) {
                vector<int> newCoordinates = {x - 1, y, x - 1, y + 1,
                                              x, y + 1, x, y + 2
                                             };
                tdPtr->notify(oldCoordinates, v, nullptr);
                currentBlocks.pop_back();
                return getBlock(newCoordinates, b, newLetter, level, orientation);
            }
            else {
                return b;
            }
        }
        else {
            if (y + 1 <= 10 &&
                    cellCheck(x - 2, y + 1) &&
                    cellCheck(x - 1, y + 1) &&
                    cellCheck(x - 1, y) &&
                    cellCheck(x, y)) {
                vector<int> newCoordinates = {x - 2, y + 1, x - 1, y + 1,
                                              x - 1, y, x, y
                                             };
                tdPtr->notify(oldCoordinates, v, nullptr);
                currentBlocks.pop_back();
                return getBlock(newCoordinates, b, newLetter, level, orientation);
            }
            else {
                return b;
            }
        }
    }
    else if (newLetter == "T") {
        if (orientation == 1) {
            if (y + 2 <= 10 &&
                    cellCheck(x, y + 1) &&
                    cellCheck(x - 1, y) &&
                    cellCheck(x - 1, y + 1) &&
                    cellCheck(x - 1, y + 2)) {
                vector<int> newCoordinates = {x, y + 1, x - 1, y,
                                              x - 1, y + 1, x - 1, y + 2
                                             };
                tdPtr->notify(oldCoordinates, v, nullptr);
                currentBlocks.pop_back();
                return getBlock(newCoordinates, b, newLetter, level, orientation);
            }
            else {
                return b;
            }
        }
        else if (orientation == 2) {
            if (y + 1 <= 10 &&
                    cellCheck(x - 1, y) &&
                    cellCheck(x - 2, y + 1) &&
                    cellCheck(x - 1, y + 1) &&
                    cellCheck(x, y + 1)) {
                vector<int> newCoordinates = {x - 1, y, x - 2, y + 1,
                                              x - 1, y + 1, x, y + 1
                                             };
                tdPtr->notify(oldCoordinates, v, nullptr);
                currentBlocks.pop_back();
                return getBlock(newCoordinates, b, newLetter, level, orientation);
            }
            else {
                return b;
            }
        }
        else if (orientation == 3) {
            if (y + 2 <= 10 &&
                    cellCheck(x - 1, y + 1) &&
                    cellCheck(x, y + 2) &&
                    cellCheck(x, y + 1) &&
                    cellCheck(x, y)) {
                vector<int> newCoordinates = {x - 1, y + 1, x, y + 2,
                                              x, y + 1, x, y
                                             };
                tdPtr->notify(oldCoordinates, v, nullptr);
                currentBlocks.pop_back();
                return getBlock(newCoordinates, b, newLetter, level, orientation);
            }
            else {
                return b;
            }
        }
        else {
            if (y + 1 <= 10 &&
                    cellCheck(x - 1, y + 1) &&
                    cellCheck(x, y) &&
                    cellCheck(x - 1, y) &&
                    cellCheck(x - 2, y)) {
                vector<int> newCoordinates = {x - 1, y + 1, x, y,
                                              x - 1, y, x - 2, y
                                             };
                tdPtr->notify(oldCoordinates, v, nullptr);
                currentBlocks.pop_back();
                return getBlock(newCoordinates, b, newLetter, level, orientation);
            }
            else {
                return b;
            }
        }
    }
    else if (newLetter == "O") {
        if (y + 1 <= 10 &&
                cellCheck(x - 1, y) &&
                cellCheck(x - 1, y + 1) &&
                cellCheck(x, y) &&
                cellCheck(x, y + 1)) {
            vector<int> newCoordinates = {x - 1, y, x - 1, y + 1,
                                          x, y, x, y + 1
                                         };
            tdPtr->notify(oldCoordinates, v, nullptr);
            currentBlocks.pop_back();
            return getBlock(newCoordinates, b, newLetter, level, orientation);
        }
        else {
            return b;
        }
    }
    else if (newLetter == "L") {
        if (orientation == 1) {
            if (y + 2 <= 10 &&
                    cellCheck(x, y) &&
                    cellCheck(x, y + 1) &&
                    cellCheck(x, y + 2) &&
                    cellCheck(x - 1, y + 2)) {
                vector<int> newCoordinates = {x, y, x, y + 1,
                                              x, y + 2, x - 1, y + 2
                                             };
                tdPtr->notify(oldCoordinates, v, nullptr);
                currentBlocks.pop_back();
                return getBlock(newCoordinates, b, newLetter, level, orientation);
            }
            else {
                return b;
            }
        }
        else if (orientation == 2) {
            if (y + 1 <= 10 &&
                    cellCheck(x - 2, y) &&
                    cellCheck(x - 1, y) &&
                    cellCheck(x, y) &&
                    cellCheck(x, y + 1)) {
                vector<int> newCoordinates = {x - 2, y, x - 1, y,
                                              x, y, x, y + 1
                                             };
                tdPtr->notify(oldCoordinates, v, nullptr);
                currentBlocks.pop_back();
                return getBlock(newCoordinates, b, newLetter, level, orientation);
            }
            else {
                return b;
            }
        }
        else if (orientation == 3) {
            if (y + 2 <= 10 &&
                    cellCheck(x - 1, y + 2) &&
                    cellCheck(x - 1, y + 1) &&
                    cellCheck(x - 1, y) &&
                    cellCheck(x, y)) {
                vector<int> newCoordinates = {x - 1, y + 2, x - 1, y + 1,
                                              x - 1, y, x, y
                                             };
                tdPtr->notify(oldCoordinates, v, nullptr);
                currentBlocks.pop_back();
                return getBlock(newCoordinates, b, newLetter, level, orientation);
            }
            else {
                return b;
            }
        }
        else {
            if (y + 1 <= 10 &&
                    cellCheck(x, y + 1) &&
                    cellCheck(x - 1, y + 1) &&
                    cellCheck(x - 2, y + 1) &&
                    cellCheck(x - 2 , y)) {
                vector<int> newCoordinates = {x, y + 1, x - 1, y + 1,
                                              x - 2, y + 1, x - 2, y
                                             };
                tdPtr->notify(oldCoordinates, v, nullptr);
                currentBlocks.pop_back();
                return getBlock(newCoordinates, b, newLetter, level, orientation);
            }
            else {
                return b;
            }
        }
    }
    else if (newLetter == "J") {
        if (orientation == 1) {
            if (y + 2 <= 10 &&
                    cellCheck(x - 1, y) &&
                    cellCheck(x, y) &&
                    cellCheck(x, y + 1) &&
                    cellCheck(x, y + 2)) {
                vector<int> newCoordinates = {x - 1, y, x, y,
                                              x, y + 1, x, y + 2
                                             };
                tdPtr->notify(oldCoordinates, v, nullptr);
                currentBlocks.pop_back();
                return getBlock(newCoordinates, b, newLetter, level, orientation);
            }
            else {
                return b;
            }
        }
        else if (orientation == 2) {
            if (y + 1 <= 10 &&
                    cellCheck(x - 2, y + 1) &&
                    cellCheck(x - 2, y) &&
                    cellCheck(x - 1, y) &&
                    cellCheck(x, y)) {
                vector<int> newCoordinates = {x - 2, y + 1, x - 2, y,
                                              x - 1, y, x, y
                                             };
                tdPtr->notify(oldCoordinates, v, nullptr);
                currentBlocks.pop_back();
                return getBlock(newCoordinates, b, newLetter, level, orientation);
            }
            else {
                return b;
            }
        }
        else if (orientation == 3) {
            if (y + 2 <= 10 &&
                    cellCheck(x, y + 2) &&
                    cellCheck(x - 1, y + 2) &&
                    cellCheck(x - 1, y + 1) &&
                    cellCheck(x - 1, y)) {
                vector<int> newCoordinates = {x, y + 2, x - 1, y + 2,
                                              x - 1, y + 1, x - 1, y
                                             };
                tdPtr->notify(oldCoordinates, v, nullptr);
                currentBlocks.pop_back();
                return getBlock(newCoordinates, b, newLetter, level, orientation);
            }
            else {
                return b;
            }
        }
        else {
            if (y + 1 <= 10 &&
                    cellCheck(x, y) &&
                    cellCheck(x, y + 1) &&
                    cellCheck(x - 1, y + 1) &&
                    cellCheck(x - 2, y + 1)) {
                vector<int> newCoordinates = {x, y, x, y + 1,
                                              x - 1, y + 1, x - 2, y + 1
                                             };
                tdPtr->notify(oldCoordinates, v, nullptr);
                currentBlocks.pop_back();
                return getBlock(newCoordinates, b, newLetter, level, orientation);
            }
            else {
                return b;
            }
        }
    }
    else if (newLetter == "I") {
        if (orientation == 1 || orientation == 3) {
            if (y + 3 <= 10 &&
                    cellCheck(x, y) &&
                    cellCheck(x, y + 1) &&
                    cellCheck(x, y + 2) &&
                    cellCheck(x, y + 3)) {
                vector<int> newCoordinates = {x, y, x, y + 1,
                                              x, y + 2, x, y + 3
                                             };
                tdPtr->notify(oldCoordinates, v, nullptr);
                currentBlocks.pop_back();
                return getBlock(newCoordinates, b, newLetter, level, orientation);
            }
            else {
                return b;
            }
        }
        else {
            if (y <= 10 &&
                    cellCheck(x - 3, y) &&
                    cellCheck(x - 2, y) &&
                    cellCheck(x - 1, y) &&
                    cellCheck(x, y)) {
                vector<int> newCoordinates = {x - 3, y, x - 2, y,
                                              x - 1, y, x, y
                                             };
                tdPtr->notify(oldCoordinates, v, nullptr);
                currentBlocks.pop_back();
                return getBlock(newCoordinates, b, newLetter, level, orientation);
            }
            else {
                return b;
            }
        }
    }
}






