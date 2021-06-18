

#include "TextDisplay.h"
#include "Block.h"
using namespace std;

const string T = "TTT\n T ";
const string L = "  L\nLLL";
const string J = "J  \nJJJ";
const string I = "IIII";
const string O = "OO\nOO";
const string S = " SS\nSS ";
const string Z = "ZZ \n ZZ";

void TextDisplay::print(string letter, int level, int score, int highscore) {
    cout << "Level: " << level << endl;
    cout << "Score: " << score << endl;
    cout << "Hi Score: " << highscore << endl;
    cout << "-----------" << endl;
    for (auto n : theDisplay) {
        for (auto k : n) {
            cout << *k;
        } cout << endl;
    }
    cout << "-----------" << endl;

    cout << "Next:" << endl;
    if (letter == "T") {
        cout << T << endl;
    }
    else if (letter == "L") {
        cout << L << endl;
    }
    else if (letter == "J") {
        cout << J << endl;
    }
    else if (letter == "O") {
        cout << O << endl;
    }
    else if (letter == "I") {
        cout << I << endl;
    }
    else if (letter == "S") {
        cout << S << endl;
    }
    else if (letter == "Z") {
        cout << Z << endl;
    }
}

void TextDisplay::notify(vector<int> oldCoordinates,
                         vector<int> newCoordinates,
                         shared_ptr<Block> b) {
    int row, col;
    //if old coordinates must be erased
    if (oldCoordinates.size() != 0) {
        for (int i = 0; i < oldCoordinates.size();  i += 2) {
            //checks to ensure not an empty cell
            if (oldCoordinates[i] != -1) {
                row = oldCoordinates[i];
                col = oldCoordinates[i + 1];
                *theDisplay[row][col] = " ";
            }
        }
    }
    //gets the appropriate letter.
    string l;
    if (b == nullptr) {
        l = "?";
    } else {
        l = b->getLetter();
    }
    if (newCoordinates.size() != 0) {
        for (int i = 0; i < newCoordinates.size(); i += 2) {
            //checks to ensure not an empty cell
            if (newCoordinates[i] != -1) {
                row = newCoordinates[i];
                col = newCoordinates[i + 1];
                *theDisplay[row][col] = l;
            }
        }
    }
}

TextDisplay::TextDisplay() {
    //make vector that is correct size
    theDisplay.resize(18);
    for (int r = 0; r < theDisplay.size(); r++) {
        //make each inner vector n in length
        theDisplay[r].resize(11);
        for (int c = 0; c < theDisplay[r].size(); c++) {
            theDisplay[r][c] = make_shared<string>();
            *theDisplay[r][c] = " ";
        }
    }
}

void TextDisplay::hint(std::vector<int> coordinates, bool place) {
    if (!place) {
        for (int r = 0; r < theDisplay.size(); r++) {
            //make each inner vector n in length
            for (int c = 0; c < theDisplay[r].size(); c++) {
                if (*theDisplay[r][c] == "?") {
                    *theDisplay[r][c] = " ";
                }
            }
        }
    }
    else {
        for (int i = 0; i < coordinates.size(); i += 2) {
            int row = coordinates[i];
            int col = coordinates[i + 1];
            *theDisplay[row][col] = "?";
        }
    }
}
