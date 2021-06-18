#include <iostream>
#include "window.h"

using namespace std;

int main() {
	Xwindow w;
	//int dimension = 500;
	//needs to be 18 x 11 blocks - width 550 - height 900
	int blockSize = 30;
	// void drawString(int x, int y, std::string msg, int colour=Black);

	// Draws a string
// void drawBigString(int x, int y, std::string msg, int colour=Black);
	int letterSize = 16;

	w.drawString(letterSize / 2, letterSize, "Level: ", Xwindow::Black);
	w.drawString(letterSize / 2, 2 * letterSize, "Score: ", Xwindow::Black);
	w.drawString(letterSize / 2, 3 * letterSize, "Hi Score: ", Xwindow::Black);
	w.drawString(0, 2 * blockSize, "-------------------------------------------------------", Xwindow::Black);

	//for (int col = 0; col < 11; col++) {
	//	w.fillRectangle(col * blockSize, 3 * blockSize, blockSize, blockSize, Xwindow::Black);

	//}
		w.fillRectangle(10 * blockSize, 2 * blockSize, blockSize, blockSize, Xwindow::Brown);

	w.fillRectangle(0 * blockSize, 2 * blockSize, blockSize, blockSize, Xwindow::Brown);
	w.fillRectangle(0 * blockSize, 4 * blockSize, blockSize, blockSize, Xwindow::White);

	w.fillRectangle(0 * blockSize, 5 * blockSize, blockSize, blockSize, Xwindow::Orange);

	w.fillRectangle(0 * blockSize, 6 * blockSize, blockSize, blockSize, Xwindow::Blue);
	w.fillRectangle(0 * blockSize, 7 * blockSize, blockSize, blockSize, Xwindow::Green);
	w.fillRectangle(0 * blockSize, 8 * blockSize, blockSize, blockSize, Xwindow::Red);
	w.fillRectangle(0 * blockSize, 9 * blockSize, blockSize, blockSize, Xwindow::Brown);
	w.fillRectangle(0 * blockSize, 10 * blockSize, blockSize, blockSize, Xwindow::White);
	w.fillRectangle(0 * blockSize, 11* blockSize, blockSize, blockSize, Xwindow::Red);
	w.fillRectangle(0 * blockSize, 12 * blockSize, blockSize, blockSize, Xwindow::Brown);
	w.fillRectangle(0 * blockSize, 13 * blockSize, blockSize, blockSize, Xwindow::White);

	w.fillRectangle(0 * blockSize, 14 * blockSize, blockSize, blockSize, Xwindow::Orange);

	w.fillRectangle(0 * blockSize, 15 * blockSize, blockSize, blockSize, Xwindow::Blue);
	w.fillRectangle(0 * blockSize, 16 * blockSize, blockSize, blockSize, Xwindow::Green);
	w.fillRectangle(0 * blockSize, 17 * blockSize, blockSize, blockSize, Xwindow::Red);
	w.fillRectangle(0 * blockSize, 18 * blockSize, blockSize, blockSize, Xwindow::Brown);
	w.fillRectangle(0 * blockSize, 19 * blockSize, blockSize, blockSize, Xwindow::Yellow);
	w.fillRectangle(0 * blockSize, 3 * blockSize, blockSize, blockSize, Xwindow::Red);

	w.drawString(0, 20 * blockSize + 10, "-------------------------------------------------------", Xwindow::Black);

	w.drawString(letterSize / 2, 20 * blockSize + 22, "Next: ", Xwindow::Black);

	w.fillRectangle(0 * blockSize, 21 * blockSize, blockSize, blockSize, Xwindow::Red);
		w.fillRectangle(0 * blockSize, 22 * blockSize, blockSize, blockSize, Xwindow::Blue);


	/*w.fillRectangle(0 * blockSize, 0 * blockSize, blockSize, blockSize, Xwindow::Blue);
	w.fillRectangle(0 * blockSize, 1 * blockSize, blockSize, blockSize, Xwindow::Green);
	w.fillRectangle(0 * blockSize, 2 * blockSize, blockSize, blockSize, Xwindow::Blue);
	w.fillRectangle(1 * blockSize, 0 * blockSize, blockSize, blockSize, Xwindow::Blue);
	w.fillRectangle(1 * blockSize, 1 * blockSize, blockSize, blockSize, Xwindow::Green);
	w.fillRectangle(1 * blockSize, 2 * blockSize, blockSize, blockSize, Xwindow::Blue);
	w.fillRectangle(2 * blockSize, 0 * blockSize, blockSize, blockSize, Xwindow::Blue);
	w.fillRectangle(2 * blockSize, 1 * blockSize, blockSize, blockSize, Xwindow::Green);
	w.fillRectangle(2 * blockSize, 2 * blockSize, blockSize, blockSize, Xwindow::Blue);*/
	char c;
	cin >> c;
}

