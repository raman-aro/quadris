

#include "interpreter.h"
#include <memory>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Block.h"
#include "Board.h"
#include "window.h"
#include <string.h>


using namespace std;

vector<string> commands = {"drop", "down", "right", "left", "clockwise", "counterclockwise", 
                            "levelup", "leveldown" , "sequence", "random", "norandom", "restart", "hint", "exit"};
                            

int interpreter::run_quadris(int argc, char* argv[], int hscore) {
    bool hintPresent = false;
    string sequencefilename;
    bool gotfirst = false;
    bool random = true;
    string norandomfile;
    ifstream file;
    bool seedbool = false;
    int seed;
    bool commenceSequenceFile = false;
    bool sequenceFile = false;
    stringstream ss;
    string filename = "sequence.txt";
    int levelinput = 0;
    bool ShowGraphicUpdates = true;
    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-scriptfile") == 0)
        {
            filename = argv[i + 1];
        }
        else if (strcmp(argv[i], "-startlevel") == 0) {
            // if "-startlevel" is the last thing in the command or is followed by a non-number
            if ((i + 1) == argc || strlen(argv[i + 1]) != 1) {
                levelinput = 0;
            }
            else {
                ss.str(argv[i + 1]);
                ss >> levelinput;
                if (levelinput > 4 || levelinput < 0) { levelinput = 0; }
                ss.clear();
            }
        }
        else if (strcmp(argv[i], "-seed") == 0) {
            ss.clear();
            ss.str(argv[i + 1]);
            seedbool = true;
            ss >> seed;
            ss.clear();
        }
        else if (strcmp(argv[i], "-text") == 0) {
            ShowGraphicUpdates = false;
        }
    }
    while (true) {
        string command;
        Board b;
        if (!ShowGraphicUpdates) {
            b.noGraphicsShowing();
        }
        b.updateHighScore(hscore);
        Xwindow w;
        b.initialize(w);
        b.setLevel(levelinput);
        int num;
        bool heavy = false;
        bool startNewGame = false;
        while (b.getgameStatus()) {
            if (startNewGame) {
                cout << "Starting new game" << endl;
                return b.getHighScore();
            }

            shared_ptr<Block> block;
            try {
                block = b.getBlock(b.getLevel(), filename, random, norandomfile, seed, seedbool);
                //seedbool = false;
                if (block == nullptr) {
                    b.printTextDisplay();
                    return -1;
                }
            }
            catch (out_of_range ex) {
                cout << ex.what() << endl;
                return b.getHighScore();
            }
            b.printTextDisplay();
            if (ShowGraphicUpdates) {
                b.printNextGraphics(block);
                b.printGraphicsDisplay(block);
            }

            while (true) {
                if (commenceSequenceFile) {
                    file.open(sequencefilename);
                    commenceSequenceFile = false;
                    if (!file) {
                        cout << "file does not exist" << endl;
                        sequenceFile = false;
                        commenceSequenceFile = false;
                    }
                }
                if ( sequenceFile ) {
                    file >> command;
                } else {
                    cin >> command;
                }
                if (hintPresent) {
                    b.gethint(nullptr);
                    hintPresent = false;
                }
                string number;
                int i = 0;
                num = -1;
                for (; i < command.size() && command[i] <= 57 && command[i] >= 48; i++) {
                    number += command[i];
                }
                if (number != "") {
                    ss.clear();
                    ss.str(number);
                    ss >> num;
                }
                string remainder = command.substr(i);
                if (num == 0) { continue; }
                command = remainder;
                int counter = 0;
                int index = 0;
                for (int i = 0; i < commands.size(); i++) {
                    if (commands[i].compare(0, command.length(), command) == 0) {
                        counter++;
                        index = i;
                    }
                }
                if (counter == 1) {
                    command = commands[index];
                }
                bool noGraphics = false;
                bool noText = false;
                if (cin.eof()) {
                    cout << "EOF" << endl;
                    b.printTextDisplay();
                    return -1;
                }
                else if (file.eof()) {
                    sequenceFile = false;
                    commenceSequenceFile = false;
                    file.close();
                    file.clear();
                    continue;
                }
                else if (command == "restart") {
                    return b.getHighScore();
                }
                else if (command == "norandom" && b.getLevel() > 2) {
                    cin >> norandomfile;
                    random = false;
                }
                else if (command == "random" && b.getLevel() > 2) {
                    random = true;
                    continue;
                }
                else if (command == "exit") {
                    return -1;
                }
                while (num > 0 || num == -1) {
                    num--;
                    if (command == "left") {
                        block->left();
                    } else if (command == "right") {
                        block->right();
                    } else if (command == "down") {
                        block->down();
                    } else if (command == "drop") {
                        block->drop();
                        b.boardChecker();
                        startNewGame = b.resetGameChecker();
                        break;
                    } else if (command == "clockwise") {
                        block->rotateC();
                    } else if (command == "counterclockwise") {
                        block->rotateCC();
                    } else if (command == "levelup") {
                        b.levelUp();
                        noGraphics = true;
                    } else if (command == "leveldown") {
                        b.levelDown();
                        noGraphics = true;
                    } else if (command == "I") {
                        block = b.swapBlock(block, "I");
                    } else if (command == "J") {
                        block = b.swapBlock(block, "J");
                    } else if (command == "L") {
                        block = b.swapBlock(block, "L");
                    } else if (command == "O") {
                        block = b.swapBlock(block, "O");
                    } else if (command == "S") {
                        block = b.swapBlock(block, "S");
                    } else if (command == "Z") {
                        block = b.swapBlock(block, "Z");
                    } else if (command == "T") {
                        block = b.swapBlock(block, "T");
                    } else if (command == "sequence") {
                        sequenceFile = true;
                        commenceSequenceFile = true;
                        cin >> sequencefilename;
                        continue;
                    } else if (command == "hint") {
                        b.gethint(block);
                        hintPresent = true;
                        break;
                    } else if (command == "restart") {
                        break;
                    }
                    else {
                        noGraphics = true;
                        noText = true;
                    }
                }
                while (num > 0 && command == "drop") {
                    try {
                        if (ShowGraphicUpdates) {
                            b.printGraphicsDisplay(block);
                            b.printNextGraphics(block);
                        }
                        block = b.getBlock(b.getLevel(), filename, random, norandomfile, seedbool, seed);
                        //seedbool = false;
                        if (block == nullptr) {
                            b.printTextDisplay();
                            return -1;
                        }
                    }
                    catch (out_of_range ex) {
                        cout << ex.what() << endl;
                        return b.getHighScore();
                    }
                    block->drop();
                    num--;
                }
                if (b.getLevel() > 2) {
                    heavy = true;
                }
                //heavy feature:
                //fore level 3 & 4
                //in the interpreter loop add a bool check:
                if (!noGraphics && !noText && heavy && command != "drop" ) {
                    block->down();
                    heavy = false;
                }
                if (startNewGame) {
                    cout << "You lost!" << endl;
                    break;
                }
                if (command == "levelup" || command == "leveldown") {
                    if (ShowGraphicUpdates) {
                        b.printGraphicsLevel();
                    }
                }
                if (!noGraphics) {
                    if (ShowGraphicUpdates) {
                        b.printGraphicsDisplay(block);
                    }
                    noGraphics = false;
                }
                if (!noText) {
                    b.printTextDisplay();
                    noText = false;
                }
                if (command == "drop") {
                    break;
                }
            }
        }
    }
}





