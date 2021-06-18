#ifndef __GRAPHICSDISPLAY_H__
#define __GRAPHICSDISPLAY_H__
#include "Observer.h"
#include "window.h"
#include <iostream>
#include <string>
class Cell;

class GraphicsDisplay: public Observer {
	const int blockSize = 30;
	const int letterSize = 16;
	Xwindow &w;
public:
	GraphicsDisplay(Xwindow &w);
	void print(int level,
	           int score, int highscore,
	           std::vector<int> oldCoordinates,
	           std::vector<int> newCoordinates,
	           std::shared_ptr<Block> b);
	void printNext(std::string nextLetter);
	void hint(std::vector<int> coordinates, bool place);
	void clearGrid();
	void notify(std::vector<int> oldCoordinates,
	            std::vector<int> newCoordinates,
	            std::shared_ptr<Block> b) override;

	//	SubscriptionType subType() const override;
	void updateScore(std::string score, std::string hiscore);
	void updateLevel(std::string level);

	~GraphicsDisplay();
};
#endif





