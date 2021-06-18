#include "Level.h"
#include <fstream>
#include <iostream>
#include <cstdlib>

using namespace std;

bool doOnce = true;

std::string Level::getBlock(int currentLevel, string filename, bool random, string norandomfile, int seed, bool seedbool) {
    string blockLetter;
    int i = 0;
    ifstream file;
    string letter;
    int j = 0;
    ifstream stream;
    //level 0
    if (doOnce && seedbool) {
        srand(seed);
        doOnce = false;
    }
    if (currentLevel == 0) {
        file.open(filename);
        while (file >> blockLetter) {
            if (i == blocksGenerated) {
                ++blocksGenerated;
                return blockLetter;
            }
            ++i;
        } 
        return "gameover";
    }//level 1
    else if (currentLevel == 1) {
        int v1 = rand() % 12 + 1;
        if (v1 == 1 || v1 == 2) {
            return "I";
        }
        else if (v1 == 3 || v1 == 4) {
            return "J";
        }
        else if (v1 == 5 || v1 == 6) {
            return "L";
        }
        else if (v1 == 7 || v1 == 8) {
            return  "O";
        }
        else if (v1 == 9 || v1 == 10) {
            return "T";
        }
        else if (v1 == 11) {
            return "S";
        }
        else {
            return "Z";
        }
    }
        //level 2
    else if (currentLevel == 2) {
        int v1 = rand() % 7 + 1;
        if (v1 == 1) {
            return "I";
        }
        else if (v1 == 2) {
            return "J";
        }
        else if (v1 == 3) {
            return "L";
        }
        else if (v1 == 4) {
            return  "O";
        }
        else if (v1 == 5) {
            return "T";
        }
        else if (v1 == 6) {
            return "S";
        }
        else {
            return "Z";
        }
    }
    else if ((currentLevel > 2) && !random) {
        stream.open(norandomfile);
        while (stream >> letter){
            if (j == lettersRead) {
                ++lettersRead;
                return letter;
            }
            ++j;
        }
        return "gameover";
    }
    else if (currentLevel == 3) {
        int v1 = rand() % 9 + 1;
        if (v1 == 1) {
            return "I";
        }
        else if (v1 == 2) {
            return "J";
        }
        else if (v1 == 3) {
            return "L";
        }
        else if (v1 == 4) {
            return  "O";
        }
        else if (v1 == 5) {
            return "T";
        }
        else if (v1 == 6 || v1 == 7) {
            return "S";
        }
        else {
            return "Z";
        }
    }
        //level 4
    else if (currentLevel == 4) {
        int v1 = rand() % 9 + 1;
        if (v1 == 1) {
            return "I";
        }
        else if (v1 == 2) {
            return "J";
        }
        else if (v1 == 3) {
            return "L";
        }
        else if (v1 == 4) {
            return  "O";
        }
        else if (v1 == 5) {
            return "T";
        }
        else if (v1 == 6 || v1 == 7) {
            return "S";
        }
        else {
            return "Z";
        }
    }
}
