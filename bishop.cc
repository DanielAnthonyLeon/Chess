#include "bishop.h"

Bishop::Bishop(char file, int rank, std::string colour) : Piece(file, rank, "bishop", colour) { }

void Bishop::setMoves(Piece* b[8][8]) {
	Piece::setMoves(b);
	int counter = 0;
	for (int i = 1; i < 8; ++i) {
		if (onBoard(file - i, rank - i)) {
			if (b[8 - (rank - i)][(file - i) - 'a']->getColour() == "empty")
				moves[counter++] = convert(file - i, rank - i);
			else if (colour != b[8 - (rank - i)][(file - i) - 'a']->getColour()) {
				moves[counter++] = convert(file - i, rank - i); break; }
			else break;
		}
	}
	for (int i = 1; i < 8; ++i) {
		if (onBoard(file - i, rank + i)) {
			if (b[8 - (rank + i)][(file - i) - 'a']->getColour() == "empty")
				moves[counter++] = convert(file - i, rank + i);
			else if (colour != b[8 - (rank + i)][(file - i) - 'a']->getColour()) {
				moves[counter++] = convert(file - i, rank + i); break; }
			else break;
		}
	}
	for (int i = 1; i < 8; ++i) {
		if (onBoard(file + i, rank - i)) {
			if (b[8 - (rank - i)][(file + i) - 'a']->getColour() == "empty")
				moves[counter++] = convert(file + i, rank - i);
			else if (colour != b[8 - (rank - i)][(file + i) - 'a']->getColour()) {
				moves[counter++] = convert(file + i, rank - i); break; }
			else break;
		}
	}
	for (int i = 1; i < 8; ++i) {
		if (onBoard(file + i, rank + i)) {
			if (b[8 - (rank + i)][(file + i) - 'a']->getColour() == "empty")
				moves[counter++] = convert(file + i, rank + i);
			else if (colour != b[8 - (rank + i)][(file + i) - 'a']->getColour()) {
				moves[counter++] = convert(file + i, rank + i); break; }
			else break;
		}
	}
}
