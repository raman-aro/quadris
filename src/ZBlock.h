#ifndef ZBLOCK_H
#define ZBLOCK_H
#include "Block.h"
#include "Board.h"
#include <string>


class Cell;
class ZBlock: public Block {
	std::shared_ptr<Board> brdptr = std::make_shared<Board>();

	std::vector<int> newCoordinates;
	std::vector<int> oldCoordinates;
	int level;
	int activeCells = 4;
	std::string colour = "orange";
	std::string letter = "Z";
	std::vector<std::shared_ptr<Observer>> v;
	int orientation = 1;
public:
	std::vector<int> getOldCoordinates() override;
	std::vector<int> getNewCoordinates() override;
	void changeOldCoordinates(std::vector<int> changed) override;
	ZBlock (std::shared_ptr<Board> brdptr, std::vector<int> newCoordinates, int level,
	        int orientation) :
		brdptr{brdptr}, newCoordinates{newCoordinates}, level{level},
		orientation{orientation}, oldCoordinates{newCoordinates}  {
		changeCellPTRS(newCoordinates);
	}
	std::string getColour() override {
		return colour;
	}
	~ZBlock() {}
	void rotateC() override;

	void changeCellPTRS(std::vector<int> vec) override ;

	int getOrientation() override;

	std::vector<int> getPointers () override;

	void rotateCC() override;

	bool down() override;

	void right() override;

	void left() override;

	void drop() override;

	int getLevel() override;

	void changeLevel(int new_level) override;

	int getActiveCells() override;

	void changeActiveCells(int destroyed) override;

	std::string getLetter() override;

	void changeLetter(std::string l) override;

	std::vector<int> getBottomLeft() override;

	void nullify() override;

};


#endif


