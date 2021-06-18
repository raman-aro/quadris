cmake_minimum_required(VERSION 3.6)
project(Quadris)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES main.cc interpreter.cc interpreter.h Block.cc Block.h IBlock.cc IBlock.h JBlock.cc JBlock.h LBlock.cc LBlock.h OBlock.cc OBlock.h Observer.cc Observer.h
        SBlock.cc SBlock.h Subject.cc Subject.h TBlock.cc TBlock.h ZBlock.cc ZBlock.h Cell.cc Cell.h TextDisplay.cc TextDisplay.h window.cc window.h GraphicsDisplay.cc GraphicsDisplay.h Board.cc Board.h Level.cc Level.h)
add_executable(Quadris ${SOURCE_FILES})

