#ifndef QUADRIS_LEVEL_H
#define QUADRIS_LEVEL_H

#include <string>

class Board;

class Level {
    int blocksGenerated = 0;
    int lettersRead = 0;
public:
    std::string getBlock(int currentLevel, std::string filename, bool random, std::string norandomfile, int seed, bool seedbool);
};


#endif
