#ifndef IBLOCK_H
#define IBLOCK_H

#include "Block.h"
#include "Board.h"
#include <string>

class Cell;

class IBlock: public Block {
	std::shared_ptr<Board> brdptr = std::make_shared<Board>();
	std::vector<int> newCoordinates;
	std::vector<int> oldCoordinates;

	int level;
	std::shared_ptr<int> activeCells = std::make_shared<int>();
	std::string letter = "I";
	std::string colour = "red";
	std::vector<std::shared_ptr<Observer>> v;
	int orientation = 1;
public:
	std::vector<int> getOldCoordinates() override;
	std::vector<int> getNewCoordinates() override;
	void changeOldCoordinates(std::vector<int> changed) override;

	IBlock (std::shared_ptr<Board> brdptr, std::vector<int> newCoordinates, int level,
	        int orientation) :
		brdptr{brdptr}, newCoordinates{newCoordinates}, level{level},
		orientation{orientation}, oldCoordinates{newCoordinates} {
		changeCellPTRS(newCoordinates);
		*activeCells = 4;
	}

	~IBlock() {}
	std::string getColour() override {
		return colour;
	}

	void rotateC() override;

	void nullify() override;

	int getOrientation() override;

	std::vector<int> getPointers () override;

	void rotateCC() override;

	bool down() override;

	void right() override;

	void left() override;

	void drop() override;

	void changeCellPTRS(std::vector<int> vec) override ;

	int getLevel() override;

	void changeLevel(int new_level) override;

	int getActiveCells() override;

	void changeActiveCells(int destroyed) override;

	std::string getLetter() override;

	std::vector<int> getBottomLeft() override;

	void changeLetter(std::string l) override;
};

#endif






