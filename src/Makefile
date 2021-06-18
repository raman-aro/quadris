CXX = g++-5
CXXFLAGS = -std=c++14 -g -Wall -MMD
EXEC = quadris
OBJECTS = main.o interpreter.o Block.o Board.o Cell.o IBlock.o JBlock.o LBlock.o Level.o OBlock.o Observer.o SBlock.o Subject.o TBlock.o TextDisplay.o ZBlock.o GraphicsDisplay.o window.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
`