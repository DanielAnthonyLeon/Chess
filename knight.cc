#include "knight.h"

Knight::Knight(char file, int rank, std::string colour) : Piece(file, rank, "knight", colour) { }

void Knight::setMoves(Piece* b[8][8]) {
	Piece::setMoves(b);
	int counter = 0;
	if (onBoard(file - 2, rank - 1)) {
		if (colour != b[8 - (rank - 1)][(file - 2) - 'a']->getColour())
			moves[counter++] = convert(file - 2, rank - 1);
	}
	if (onBoard(file - 2, rank + 1)) {
		if (colour != b[8 - (rank + 1)][(file - 2) - 'a']->getColour())
			moves[counter++] = convert(file - 2, rank + 1);
	}
	if (onBoard(file - 1, rank - 2)) {
		if (colour != b[8 - (rank - 2)][(file - 1) - 'a']->getColour())
			moves[counter++] = convert(file - 1, rank - 2);
	}
	if (onBoard(file - 1, rank + 2)) {
		if (colour != b[8 - (rank + 2)][(file - 1) - 'a']->getColour())
			moves[counter++] = convert(file - 1, rank + 2);
	}
	if (onBoard(file + 1, rank - 2)) {
		if (colour != b[8 - (rank - 2)][(file + 1) - 'a']->getColour())
			moves[counter++] = convert(file + 1, rank - 2);
	}
	if (onBoard(file + 1, rank + 2)) {
		if (colour != b[8 - (rank + 2)][(file + 1) - 'a']->getColour())
			moves[counter++] = convert(file + 1, rank + 2);
	}
	if (onBoard(file + 2, rank - 1)) {
		if (colour != b[8 - (rank - 1)][(file + 2) - 'a']->getColour())
			moves[counter++] = convert(file + 2, rank - 1);
	}
	if (onBoard(file + 2, rank + 1)) {
		if (colour != b[8 - (rank + 1)][(file + 2) - 'a']->getColour())
			moves[counter++] = convert(file + 2, rank + 1);
	}
}
