#include "queen.h"

Queen::Queen(char file, int rank, std::string colour) : Piece(file, rank, "queen", colour) { }

void Queen::setMoves(Piece* b[8][8]) {
	Piece::setMoves(b);
	int counter = 0;
	// moves like a bishop
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
	// moves like a rook
	for (int i = 1; i < 8; ++i) {
		if (onBoard(file, rank - i)) {
			if (b[8 - (rank - i)][file - 'a']->getColour() == "empty")
				moves[counter++] = convert(file, rank - i);
			else if (colour != b[8 - (rank - i)][file - 'a']->getColour()) {
				moves[counter++] = convert(file, rank - i); break; }
			else break;
		}
	}
	for (int i = 1; i < 8; ++i) {
		if (onBoard(file, rank + i)) {
			if (b[8 - (rank + i)][file - 'a']->getColour() == "empty")
				moves[counter++] = convert(file, rank + i);
			else if (colour != b[8 - (rank + i)][file - 'a']->getColour()) {
				moves[counter++] = convert(file, rank + i); break; }
			else break;
		}
	}
	for (int i = 1; i < 8; ++i) {
		if (onBoard(file - i, rank)) {
			if (b[8 - rank][(file - i) - 'a']->getColour() == "empty")
				moves[counter++] = convert(file - i, rank);
			else if (colour != b[8 - rank][(file - i) - 'a']->getColour()) {
				moves[counter++] = convert(file - i, rank); break; }
			else break;
		}
	}
	for (int i = 1; i < 8; ++i) {
		if (onBoard(file + i, rank)) {
			if (b[8 - rank][(file + i) - 'a']->getColour() == "empty")
				moves[counter++] = convert(file + i, rank);
			else if (colour != b[8 - rank][(file + i) - 'a']->getColour()) {
				moves[counter++] = convert(file + i, rank); break; }
			else break;
		}
	}
}
