#ifndef BOARD_H
#define BOARD_H

#include "Cell.h"
#include "Level.h"
#include "TextDisplay.h"
#include "GraphicsDisplay.h"
class Block;
class Level;

class Board: public std::enable_shared_from_this<Board> {
	std::vector <std::vector<std::shared_ptr<Cell>>> board;
	std::vector <std::shared_ptr<Block>> currentBlocks;
	std::string next;
	int highscore = 0;
	int score = 0;
	int height;
	int width;
	bool gameOn = false;
	bool first = true;
	std::string blockLetter;
	std::string after;
	std::string temp;
	bool GraphicsOn = true;
	std::vector<int> hintCoordinates;
	std::shared_ptr<TextDisplay> tdPtr = std::make_shared<TextDisplay>();
	std::shared_ptr<GraphicsDisplay> gdPtr;
	int levelInt = 0;
	int blocksAdded;
	int lastRowDel;
	std::shared_ptr<Level> level = std::make_shared<Level>();
public:
	void printTextDisplay();
	void printGraphicsDisplay(std::shared_ptr<Block> b);
	void printNextGraphics(std::shared_ptr<Block> b);

	void noGraphicsShowing();

	//updates Board
	void notify(std::vector<int> oldCoordinates,
	            std::vector<int> newCoordinates,
	            std::shared_ptr<Block> b);

	//generates a new block
	std::shared_ptr<Block> getBlock(int levelnumber, std::string file, bool random, std::string norandomfile, int seed, bool seedbool);

	std::shared_ptr<Block> getBlock(std::vector<int> newCoordinates,
	                                std::shared_ptr<Block> b,
	                                std::string letter, int level,
	                                int orientation);

	std::shared_ptr<Cell> getCellPTR(int row, int col);

	std::shared_ptr<Block> swapBlock(std::shared_ptr<Block> b, std::string newLetter);

	bool cellCheck(int row, int col);

	bool getgameStatus();
	void moveDown(std::shared_ptr<Block> block);

	void changeGameStatus();
	//returns true if game needs to be reset
	bool resetGameChecker();
	//initializes grid
	void initialize(Xwindow & w);
	std::shared_ptr<Block> boardChecker();
	void printeger();
	//deletes the row at the given row
	void rowDelete(int row, int mulitplier);
	int	bestSpot();
	//prints the board
	void print();
	void addCurrentBlock();
	int updateBlocksAdded(std::shared_ptr<Block> b);
	std::string getNext();
	void printGraphicsLevel();
	int getHighScore();
	void updateHighScore(int s);
	int getScore();
	int	updateScore();
	int getWidth();
	int getHeight();
	int getLevel();
	void setLevel(int num);
	void levelUp();
	void levelDown();
	int getLastRowDel();
	void gethint(std::shared_ptr<Block> block);
	std::vector<int> moverighthint(std::vector<int> oldest);
	std::vector<int> movedownhint(std::vector<int> old);
};

#endif




