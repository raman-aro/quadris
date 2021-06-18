#include <iostream>
#include "interpreter.h"
int main(int argc, char* argv[]) {
    interpreter i;
    int highscore = i.run_quadris(argc, argv, 0);
    while (highscore >= 0) {
    	highscore = i.run_quadris(argc, argv, highscore);
    }
    std::cout<<"GAME OVER"<<std::endl;
}
