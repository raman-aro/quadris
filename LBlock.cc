#include "LBlock.h"
#include "Cell.h"
using namespace std;

std::vector<int> LBlock::getOldCoordinates() {
	return oldCoordinates;
}
std::vector<int> LBlock::getNewCoordinates() {
	return newCoordinates;
}
void LBlock::changeOldCoordinates(std::vector<int> changed) {
	int size = changed.size();
	for (int i = 0; i < size; i++) {
		oldCoordinates[i] = changed[i];
	}
}

int LBlock::getOrientation() {
	return orientation;
}

std::vector<int> LBlock::getPointers () {
	return newCoordinates;
}

// nullifies all cell pointers in block
void LBlock::nullify() {
	vector<int> temp;
	brdptr->notify(newCoordinates, temp, nullptr );
}

void LBlock::rotateC()  {
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
		if ((y + 1) <= 10 &&
		        brdptr->cellCheck((x - 1), y) &&
		        brdptr->cellCheck((x - 2), y)) {
			//create vector of new positions
			std::vector<int> newvec {(x - 2), y, (x - 1), y,
			                         (x), (y), x, (y + 1)};
			//notify observers
			brdptr->notify(old, newvec, make_shared<LBlock>(*this));
			//change CellPtrs to new positions
			changeCellPTRS(newvec);
			newCoordinates = newvec;
			orientation = 2;
		}
	}
	else if (orientation == 2) {
		//checking that rotation does not go off the board and
		//  that potential spaces are empty
		if ((y + 2) <= 10 &&
		        brdptr->cellCheck((x + 1), y + 1) &&
		        brdptr->cellCheck((x + 1), y + 2)) {
			//create vector of new positions
			std::vector<int> newvec {(x + 1), y + 2, (x + 1), y + 1,
			                         (x + 1), (y), x + 2, (y)};
			//notify observers
			brdptr->notify(old, newvec, make_shared<LBlock>(*this));
			//change CellPtrs to new positions
			changeCellPTRS(newvec);
			newCoordinates = newvec;
			orientation = 3;
		}
	}
	else if (orientation == 3) {
		//checking that rotation does not go off the board and
		//  that potential spaces are empty
		if (brdptr->cellCheck((x + 1), y - 1) &&
		        brdptr->cellCheck((x - 1), y - 1) &&
		        brdptr->cellCheck((x - 1), y - 2)) {
			//create vector of new positions
			std::vector<int> newvec {(x + 1), y - 1, (x), y - 1,
			                         (x - 1), (y - 1), x - 1, (y - 2)};
			//notify observers
			brdptr->notify(old, newvec, make_shared<LBlock>(*this));
			//change CellPtrs to new positions
			changeCellPTRS(newvec);
			newCoordinates = newvec;
			orientation = 4;
		}
	}
	else {
		// checking that rotation does not go off the board and
		//  that potential spaces are empty
		if ((y + 1) <= 10 &&
		        brdptr->cellCheck((x), y - 1) &&
		        brdptr->cellCheck((x), y + 1) &&
		        brdptr->cellCheck((x - 1), (y + 1))) {
			//create vector of new positions
			std::vector<int> newvec {(x), y - 1, (x), (y),
			                         (x), (y + 1), (x - 1), (y + 1)};
			//notify observers
			brdptr->notify(old, newvec, make_shared<LBlock>(*this));
			//change CellPtrs to new positions
			changeCellPTRS(newvec);
			newCoordinates = newvec;
			orientation = 1;
		}
	}
}

void LBlock::rotateCC() {
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
		if (brdptr->cellCheck((x - 2), y) &&
		        brdptr->cellCheck((x - 1), y + 1) &&
		        brdptr->cellCheck((x - 2), y + 1)) {
			//create vector of new positions
			std::vector<int> newvec {(x), y + 1, (x - 1), y + 1,
			                         (x - 2), (y + 1), x - 2, (y)};
			//notify observers
			brdptr->notify(old, newvec, make_shared<LBlock>(*this));
			//change CellPtrs to new positions
			changeCellPTRS(newvec);
			newCoordinates = newvec;
			orientation = 4;
		}
	}
	else if (orientation == 2) {
		//checking that rotation does not go off the board and
		//  that potential spaces are empty
		if ((y + 2) <= 10 &&
		        brdptr->cellCheck((x + 2), y + 2) &&
		        brdptr->cellCheck((x + 1), y + 2)) {
			//create vector of new positions
			std::vector<int> newvec {(x + 2), y, (x + 2), y + 1,
			                         (x + 2), (y + 2), x + 1, (y + 2)};
			//notify observers
			brdptr->notify(old, newvec, make_shared<LBlock>(*this));
			//change CellPtrs to new positions
			changeCellPTRS(newvec);
			newCoordinates = newvec;
			orientation = 1;
		}
	}
	else if (orientation == 3) {
		//checking that rotation does not go off the board and
		//  that potential spaces are empty
		if (brdptr->cellCheck((x + 1), y - 1) &&
		        brdptr->cellCheck((x - 1), y - 2)) {
			//create vector of new positions
			std::vector<int> newvec {(x - 1), y - 2, (x), y - 2,
			                         (x + 1), (y - 2), x + 1, (y - 1)};
			//notify observers
			brdptr->notify(old, newvec, make_shared<LBlock>(*this));
			//change CellPtrs to new positions
			changeCellPTRS(newvec);
			newCoordinates = newvec;
			orientation = 2;
		}
	}
	else {
		// checking that rotation does not go off the board and
		//  that potential spaces are empty
		if ((y + 1) <= 10 &&
		        brdptr->cellCheck((x), y - 1) &&
		        brdptr->cellCheck((x - 1), y - 1) &&
		        brdptr->cellCheck((x - 1), (y + 1))) {
			//create vector of new positions
			std::vector<int> newvec {(x - 1), y + 1, (x - 1), (y),
			                         (x - 1), (y - 1), (x), (y - 1)};
			//notify observers
			brdptr->notify(old, newvec, make_shared<LBlock>(*this));
			//change CellPtrs to new positions
			changeCellPTRS(newvec);
			newCoordinates = newvec;
			orientation = 3;
		}
	}
}

void LBlock::changeCellPTRS(std::vector<int> vec) {
	newCoordinates = vec;
}

bool LBlock::down() {
	//uses cellptr1 for reference
	int x , y;
	x = newCoordinates[0];
	y = newCoordinates[1];

	//creates vector of old coordinates
	std::vector<int> old = newCoordinates;
	if (orientation == 1) {
		// check if cells below are empty so block can be moved down
		// check to see if viable
		if ((x + 1) <= 17 &&
		        brdptr->cellCheck((x + 1), y) &&
		        brdptr->cellCheck((x + 1), (y + 1)) &&
		        brdptr->cellCheck(x + 1, (y + 2))) {
			//create vector of new positions
			std::vector<int> newvec {(x + 1), y, (x + 1), (y + 1),
			                         x + 1, (y + 2), x, (y + 2)};
			//notify observers
			brdptr->notify(old, newvec, make_shared<LBlock>(*this));
			//change CellPtrs to new positions
			changeCellPTRS(newvec);
			newCoordinates = newvec;
			return true;
		}
	}
	else if (orientation == 2) {
		// check if cells below are empty so block can be moved down
		// check to see if viable
		if ((x + 3) <= 17 &&
		        brdptr->cellCheck((x + 3), y) &&
		        brdptr->cellCheck((x + 3), (y + 1))) {
			//create vector of new positions
			std::vector<int> newvec {(x + 1), y, (x + 2), (y),
			                         x + 3, (y), x + 3, (y + 1)};
			//notify observers
			brdptr->notify(old, newvec, make_shared<LBlock>(*this));
			//change CellPtrs to new positions
			changeCellPTRS(newvec);
			newCoordinates = newvec;
			return true;
		}
	}
	else if (orientation == 3) {
		// check if cells below are empty so block can be moved down
		// check to see if viable
		if ((x + 2) <= 17 &&
		        brdptr->cellCheck((x + 1), y) &&
		        brdptr->cellCheck((x + 1), (y - 1)) &&
		        brdptr->cellCheck(x + 2, (y - 2))) {
			//create vector of new positions
			std::vector<int> newvec {(x + 1), y, (x + 1), (y - 1),
			                         x + 1, (y - 2), x + 2, (y - 2)};
			//notify observers
			brdptr->notify(old, newvec, make_shared<LBlock>(*this));
			//change CellPtrs to new positions
			changeCellPTRS(newvec);
			newCoordinates = newvec;
			return true;
		}
	}
	else {
		// check if cells below are empty so block can be moved down
		if ((x + 1) <= 17 &&
		        brdptr->cellCheck((x + 1), y) &&
		        brdptr->cellCheck((x - 1), (y - 1))) {
			//create vector of new positions
			std::vector<int> newvec {(x + 1), y, (x), y,
			                         (x - 1), (y), (x - 1), (y - 1)};
			//notify observers
			brdptr->notify(old, newvec, make_shared<LBlock>(*this));
			//change CellPtrs to new positions
			changeCellPTRS(newvec);
			newCoordinates = newvec;
			return true;
		}
	}
	return false;
}

void LBlock::right() {
	//uses cellptr1 for reference
	int x , y;
	x = newCoordinates[0];
	y = newCoordinates[1];

	//creates vector of old coordinates
	std::vector<int> old = newCoordinates;

	if (orientation == 1) {
		// check if cells right are empty so block can be moved right
		if ((y + 3) <= 10 &&
		        brdptr->cellCheck(x, (y + 3)) &&
		        brdptr->cellCheck((x - 1), (y + 3))) {
			//create vector of new positions
			std::vector<int> newvec {x, y + 1, x, y + 2, x, y + 3, x - 1, (y + 3)};
			//notify observers
			brdptr->notify(old, newvec, make_shared<LBlock>(*this));
			//change CellPtrs to new positions
			changeCellPTRS(newvec);
			newCoordinates = newvec;
		}
	}
	else if (orientation == 2) {
		// check if cells right are empty so block can be moved right
		if ((y + 2) <= 10 &&
		        brdptr->cellCheck(x, (y + 1)) &&
		        brdptr->cellCheck((x + 1), (y + 1)) &&
		        brdptr->cellCheck((x + 2), (y + 2))) {
			//create vector of new positions
			std::vector<int> newvec {x, y + 1, x + 1, y + 1,
			                         x + 2, y + 1, x + 2, (y + 2)};
			//notify observers
			brdptr->notify(old, newvec, make_shared<LBlock>(*this));
			//change CellPtrs to new positions
			changeCellPTRS(newvec);
			newCoordinates = newvec;
		}
	}
	else if (orientation == 3) {
		// check if cells right are empty so block can be moved right
		if ((y + 1) <= 10 &&
		        brdptr->cellCheck(x, (y + 1)) &&
		        brdptr->cellCheck((x + 1), (y - 1))) {
			//create vector of new positions
			std::vector<int> newvec {x, y + 1, x, y, x, y - 1, x + 1, (y - 1)};
			//notify observers
			brdptr->notify(old, newvec, make_shared<LBlock>(*this));
			//change CellPtrs to new positions
			changeCellPTRS(newvec);
			newCoordinates = newvec;
		}
	}
	else {
		if ((y + 1) <= 10 &&
		        brdptr->cellCheck(x, y + 1) &&
		        brdptr->cellCheck(x - 1, y + 1) &&
		        brdptr->cellCheck((x - 2), (y + 1))) {
			//create vector of new positions
			std::vector<int> newvec {x, y + 1, x - 1, y + 1,
			                         x - 2, y + 1, x - 2, (y)};
			//notify observers
			brdptr->notify(old, newvec, make_shared<LBlock>(*this));
			//change CellPtrs to new positions
			changeCellPTRS(newvec);
			newCoordinates = newvec;
		}
	}
}

void LBlock::left() {
	//uses cellptr1 for reference
	int x , y;
	x = newCoordinates[0];
	y = newCoordinates[1];

	//creates vector of old coordinates
	std::vector<int> old = newCoordinates;

	if (orientation == 1) {
		// check if cells right are empty so block can be moved right
		if ((y - 1) >= 0 &&
		        brdptr->cellCheck(x, (y - 1)) &&
		        brdptr->cellCheck((x - 1), y + 1)) {
			//create vector of new positions
			std::vector<int> newvec {x, y - 1, x, y,
			                         x, y + 1, x - 1, (y + 1)};
			//notify observers
			brdptr->notify(old, newvec, make_shared<LBlock>(*this));
			//change CellPtrs to new positions
			changeCellPTRS(newvec);
			newCoordinates = newvec;
		}
	}
	else if (orientation == 2) {
		// check if cells right are empty so block can be moved right
		if ((y - 1) >= 0 &&
		        brdptr->cellCheck(x, (y - 1)) &&
		        brdptr->cellCheck((x - 1), y - 1) &&
		        brdptr->cellCheck((x - 2), y - 1)) {
			//create vector of new positions
			std::vector<int> newvec {x, y - 1, x + 1, y - 1,
			                         x + 2, y - 1, x + 2, (y)};
			//notify observers
			brdptr->notify(old, newvec, make_shared<LBlock>(*this));
			//change CellPtrs to new positions
			changeCellPTRS(newvec);
			newCoordinates = newvec;
		}
	}
	else if (orientation == 3) {
		// check if cells right are empty so block can be moved right
		if ((y - 3) >= 0 &&
		        brdptr->cellCheck(x, (y - 3)) &&
		        brdptr->cellCheck((x + 1), y - 3)) {
			//create vector of new positions
			std::vector<int> newvec {x, y - 1, x, y - 2,
			                         x, y - 3, x + 1, (y - 3)};
			//notify observers
			brdptr->notify(old, newvec, make_shared<LBlock>(*this));
			//change CellPtrs to new positions
			changeCellPTRS(newvec);
			newCoordinates = newvec;
		}
	}
	else {
		if ((y - 2) >= 0 &&
		        brdptr->cellCheck(x, y - 1) &&
		        brdptr->cellCheck(x - 1, y - 1) &&
		        brdptr->cellCheck((x - 2), (y - 2))) {
			//create vector of new positions
			std::vector<int> newvec {x, y - 1, x - 1, y - 1,
			                         x - 2, y - 1, x - 2, (y - 2)};
			//notify observers
			brdptr->notify(old, newvec, make_shared<LBlock>(*this));
			//change CellPtrs to new positions
			changeCellPTRS(newvec);
			newCoordinates = newvec;
		}
	}
}

void LBlock::drop() {
	while (down()) {}
	brdptr->printGraphicsDisplay(make_shared<LBlock>(*this));
}

int LBlock::getLevel() {
	return level;
}

void LBlock::changeLevel(int new_level) {
	level = new_level;
}

int LBlock::getActiveCells() {
	return *activeCells;
}

void LBlock::changeActiveCells(int destroyed) {
	*activeCells -= destroyed;
}

string LBlock::getLetter() {
	return letter;
}

void LBlock::changeLetter(string l) {
	letter = l;
}

std::vector<int> LBlock::getBottomLeft() {
	int x, y;
	y = newCoordinates[1];
	x = newCoordinates[0];
	std::vector<int> bottomLeft;
	if (orientation == 1) {
		bottomLeft.emplace_back(x);
		bottomLeft.emplace_back(y);
	}
	else if (orientation == 2) {
		bottomLeft.emplace_back(x + 2);
		bottomLeft.emplace_back(y);
	}
	else if (orientation == 3) {
		bottomLeft.emplace_back(x + 1);
		bottomLeft.emplace_back(y - 2);
	}
	else {
		bottomLeft.emplace_back(x);
		bottomLeft.emplace_back(y - 1);
	}
	return bottomLeft;
}




