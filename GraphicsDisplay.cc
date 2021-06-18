#include "GraphicsDisplay.h"
#include "Cell.h"
#include "Block.h"

using namespace std;


void GraphicsDisplay::hint(std::vector<int> coordinates, bool place) {
	if (!place) {
		for (int i = 0; i < coordinates.size(); i += 2) {
			int row = coordinates[i];
			int col = coordinates[i + 1];
			w.fillRectangle(col * blockSize, (row + 2) * blockSize, blockSize, blockSize, Xwindow::White);
		}
	}
	else {
		for (int i = 0; i < coordinates.size(); i += 2) {
			int row = coordinates[i];
			int col = coordinates[i + 1];
			w.fillRectangle(col * blockSize, (row + 2) * blockSize, blockSize, blockSize, Xwindow::Black);
		}
	}
}


void GraphicsDisplay::printNext(std::string nextLetter) {
	//erase previous current block
	w.fillRectangle(0 * blockSize, 21 * blockSize, 3 * blockSize, blockSize, Xwindow::White);
	w.fillRectangle(0 * blockSize, 22 * blockSize, 4 * blockSize, blockSize, Xwindow::White);
	//change l to nextLetter
	if (nextLetter == "I") {
		w.fillRectangle(0 * blockSize, 22 * blockSize, 4 * blockSize, blockSize, Xwindow::Red);
	}
	else if (nextLetter == "J") {
		w.fillRectangle(0 * blockSize, 21 * blockSize, blockSize, blockSize, Xwindow::Green);
		w.fillRectangle(0 * blockSize, 22 * blockSize, 3 * blockSize, blockSize, Xwindow::Green);
	}
	else if (nextLetter == "L") {
		w.fillRectangle(2 * blockSize, 21 * blockSize, blockSize, blockSize, Xwindow::Blue);
		w.fillRectangle(0 * blockSize, 22 * blockSize, 3 * blockSize, blockSize, Xwindow::Blue);
	}
	else if (nextLetter == "O") {
		w.fillRectangle(0 * blockSize, 21 * blockSize, 2 * blockSize, blockSize, Xwindow::Cyan);
		w.fillRectangle(0 * blockSize, 22 * blockSize, 2 * blockSize, blockSize, Xwindow::Cyan);
	}
	else if (nextLetter == "S") {
		w.fillRectangle(1 * blockSize, 21 * blockSize, 2 * blockSize, blockSize, Xwindow::Magenta);
		w.fillRectangle(0 * blockSize, 22 * blockSize, 2 * blockSize, blockSize, Xwindow::Magenta);
	}
	else if (nextLetter == "Z") {
		w.fillRectangle(0 * blockSize, 21 * blockSize, 2 * blockSize, blockSize, Xwindow::Orange);
		w.fillRectangle(1 * blockSize, 22 * blockSize, 2 * blockSize, blockSize, Xwindow::Orange);
	}
	else if (nextLetter == "T") {
		w.fillRectangle(0 * blockSize, 21 * blockSize, 3 * blockSize, blockSize, Xwindow::Yellow);
		w.fillRectangle(1 * blockSize, 22 * blockSize, blockSize, blockSize, Xwindow::Yellow);
	}
}

void GraphicsDisplay::print(int level,
                            int score, int highscore,
                            std::vector<int> oldCoordinates,
                            std::vector<int> newCoordinates,
                            std::shared_ptr<Block> b) {
	int row, col;
	//if old coordinates need to be erased
	int sizeOld = oldCoordinates.size();
	if (sizeOld != 0) {
		for (int i = 0; i < sizeOld; i += 2) {
			//checks to ensure not an empty cell
			if (oldCoordinates[i] != -1) {
				row = oldCoordinates[i];
				col = oldCoordinates[i + 1];
				w.fillRectangle(col * blockSize, (row + 2) * blockSize, blockSize, blockSize, Xwindow::White);
			}
		}
	}
	//gets the appropriate letter, colour, and next block
	string l;
	string colour;
	if (b == nullptr) {
		l = "?";
	} else {
		l = b->getLetter();
		colour = b->getColour();
	}
	int sizeNew = newCoordinates.size();
	if (sizeNew != 0) {
		for (int i = 0; i < sizeNew; i += 2) {
			//checks to ensure not an empty cell
			if (newCoordinates[i] != -1) {
				row = newCoordinates[i];
				col = newCoordinates[i + 1];
				if (colour == "red") {
					w.fillRectangle(col * blockSize, (row + 2) * blockSize, blockSize, blockSize, Xwindow::Red);
				}
				else if (colour == "green") {
					w.fillRectangle(col * blockSize, (row + 2) * blockSize, blockSize, blockSize, Xwindow::Green);
				}
				else if (colour == "blue") {
					w.fillRectangle(col * blockSize, (row + 2) * blockSize, blockSize, blockSize, Xwindow::Blue);
				}
				else if (colour == "cyan") {
					w.fillRectangle(col * blockSize, (row + 2) * blockSize, blockSize, blockSize, Xwindow::Cyan);
				}
				else if (colour == "magenta") {
					w.fillRectangle(col * blockSize, (row + 2) * blockSize, blockSize, blockSize, Xwindow::Magenta);
				}
				else if (colour == "orange") {
					w.fillRectangle(col * blockSize, (row + 2) * blockSize, blockSize, blockSize, Xwindow::Orange);
				}
				else if (colour == "yellow") {
					w.fillRectangle(col * blockSize, (row + 2) * blockSize, blockSize, blockSize, Xwindow::Yellow);
				}
				else if (colour == "black") {
					w.fillRectangle(col * blockSize, (row + 2) * blockSize, blockSize, blockSize, Xwindow::Black);
				}

			}
		}
	}
}

void GraphicsDisplay::notify(std::vector<int> oldCoordinates,
                             std::vector<int> newCoordinates,
                             std::shared_ptr<Block> b) {

}

void GraphicsDisplay::updateScore(string score, string hiscore) {
	w.fillRectangle(letterSize * 3.5, 1.25 * letterSize, blockSize * 11, letterSize, Xwindow::White);
	w.fillRectangle(letterSize * 5, 2.25 * letterSize, blockSize * 11, letterSize, Xwindow::White);
	w.drawString(letterSize * 4, 2 * letterSize, score, Xwindow::Black);
	w.drawString(letterSize * 5.5, 3 * letterSize, hiscore, Xwindow::Black);

}

void GraphicsDisplay::updateLevel(std::string level) {
	w.fillRectangle(letterSize * 3.5, 0.25 * letterSize, letterSize, letterSize, Xwindow::White);
	w.drawString(letterSize * 4, letterSize, level, Xwindow::Black);

}

GraphicsDisplay::GraphicsDisplay(Xwindow & w): w{w} {
	w.drawString(letterSize / 2, letterSize, "Level: ", Xwindow::Black);
	w.drawString(letterSize / 2, 2 * letterSize, "Score: ", Xwindow::Black);
	w.drawString(letterSize / 2, 3 * letterSize, "Hi Score: ", Xwindow::Black);
	w.drawString(0, 2 * blockSize, "-------------------------------------------------------", Xwindow::Black);
	w.drawString(0, 20 * blockSize + 10, "-------------------------------------------------------", Xwindow::Black);
	w.drawString(letterSize / 2, 20 * blockSize + 22, "Next: ", Xwindow::Black);
}

GraphicsDisplay::~GraphicsDisplay() {}




