#include "pawn.h"

Pawn::Pawn(char file, int rank, std::string colour, bool moved, bool passable) : Piece(file, rank, "pawn", colour, moved, passable) { }

void Pawn::setMoves(Piece* b[8][8]) {
	Piece::setMoves(b);
	int counter = 0;
	// pawn is in its starting position
	if ((rank == 2 && colour == "white") || (rank == 7 && colour == "black")) {
		if (b[8 - (rank + increment())][file - 'a']->getColour() == "empty" && b[8 - (rank + 2 * increment())][file - 'a']->getColour() == "empty")
			moves[counter++] = convert(file, rank + 2 * increment());
	}
	// regular pawn move
	if (onBoard(file, rank + increment())) {
		if (b[8 - (rank + increment())][file - 'a']->getColour() == "empty")
			moves[counter++] = convert(file, rank + increment());
	}
	// pawn capture
	if (file > 'a') {
		if (b[8 - (rank + increment())][(file - 1) - 'a']->getColour() != "empty" && b[8 - (rank + increment())][(file - 1) - 'a']->getColour() != colour)
			moves[counter++] = convert(file - 1, rank + increment());
	}
	if (file < 'h') {
		if (b[8 - (rank + increment())][(file + 1) - 'a']->getColour() != "empty" && b[8 - (rank + increment())][(file + 1) - 'a']->getColour() != colour)
			moves[counter++] = convert(file + 1, rank + increment());
	}
	// en passant
	if ((rank == 5 && colour == "white") || (rank == 4 && colour == "black")) {
		if (file > 'a') {
			if (b[8 - rank][(file - 1) - 'a']->getType() == "pawn" && b[8 - rank][(file - 1) - 'a']->getColour() != colour && b[8 - rank][(file - 1) - 'a']->isPassable())
				moves[counter++] = convert(file - 1, rank + increment());
		}
		if (file < 'h') {
			if (b[8 - rank][(file + 1) - 'a']->getType() == "pawn" && b[8 - rank][(file + 1) - 'a']->getColour() != colour && b[8 - rank][(file + 1) - 'a']->isPassable())
				moves[counter++] = convert(file + 1, rank + increment());
		}
	}
}

int Pawn::increment() { return colour == "white" ? 1 : -1; }
