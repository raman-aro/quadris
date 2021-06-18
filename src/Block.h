#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include <vector>
#include <memory>
#include "Subject.h"
class Cell;

class Block: public Subject {
public:
	Block() {}
	virtual std::string getColour() = 0;
	virtual void rotateC() = 0;
	virtual void rotateCC() = 0;
	virtual bool down() = 0;
	virtual void right() = 0;
	virtual void left() = 0;
	virtual void drop() = 0;
	virtual int getLevel() = 0;
	virtual void changeLevel(int new_level) = 0;
	virtual int getActiveCells() = 0;
	virtual void changeActiveCells(int destroyed) = 0;
	virtual std::string getLetter() = 0;
	virtual void changeLetter(std::string l) = 0;
	virtual void changeCellPTRS(std::vector<int> vec) = 0;
	virtual std::vector<int> getBottomLeft() = 0;
	virtual	int getOrientation() = 0;
	virtual std::vector<int> getPointers () = 0;
	virtual void nullify() = 0;
	virtual std::vector<int> getOldCoordinates() = 0;
	virtual std::vector<int> getNewCoordinates() = 0;
	virtual void changeOldCoordinates(std::vector<int> changed) = 0;
	virtual ~Block() {}
};

#endif


