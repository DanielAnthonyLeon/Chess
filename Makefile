CXX = g++
CXXFLAGS = -Wall -MMD -g
EXEC = chess
OBJECTS = piece.o pawn.o knight.o bishop.o rook.o queen.o king.o board.o main.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
