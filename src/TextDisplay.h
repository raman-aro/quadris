
#ifndef QUADRIS_TEXTDISPLAY_H
#define QUADRIS_TEXTDISPLAY_H

#include <iostream>
#include <string>
#include "Observer.h"

class Cell;

class TextDisplay: public Observer {
    std::vector<std::vector<std::shared_ptr<std::string>>> theDisplay;
public:
    TextDisplay();
    void print(std::string letter, int level, int score, int highscore);
    void notify(std::vector<int> oldCoordinates,
                std::vector<int> newCoordinates,
                std::shared_ptr<Block> b);
    void hint(std::vector<int> coordinates, bool place);
};

#endif 
