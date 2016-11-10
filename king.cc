#include "king.h"

King::King(char file, int rank, std::string colour, bool moved) : Piece(file, rank, "king", colour, moved) { }

void King::setMoves(Piece* b[8][8]) {
	Piece::setMoves(b);
	int counter = 0;
	if (onBoard(file - 1, rank - 1)) {
		if (colour != b[8 - (rank - 1)][(file - 1) - 'a']->getColour())
			moves[counter++] = convert(file - 1, rank - 1);
	}
	if (onBoard(file - 1, rank)) {
		if (colour != b[8 - rank][(file - 1) - 'a']->getColour())
			moves[counter++] = convert(file - 1, rank);
	}
	if (onBoard(file - 1, rank + 1)) {
		if (colour != b[8 - (rank + 1)][(file - 1) - 'a']->getColour())
			moves[counter++] = convert(file - 1, rank + 1);
	}
	if (onBoard(file, rank - 1)) {
		if (colour != b[8 - (rank - 1)][file - 'a']->getColour())
			moves[counter++] = convert(file, rank - 1);
	}
	if (onBoard(file, rank + 1)) {
		if (colour != b[8 - (rank + 1)][file - 'a']->getColour())
			moves[counter++] = convert(file, rank + 1);
	}
	if (onBoard(file + 1, rank - 1)) {
		if (colour != b[8 - (rank - 1)][(file + 1) - 'a']->getColour())
			moves[counter++] = convert(file + 1, rank - 1);
	}
	if (onBoard(file + 1, rank)) {
		if (colour != b[8 - rank][(file + 1) - 'a']->getColour())
			moves[counter++] = convert(file + 1, rank);
	}
	if (onBoard(file + 1, rank + 1)) {
		if (colour != b[8 - (rank + 1)][(file + 1) - 'a']->getColour())
			moves[counter++] = convert(file + 1, rank + 1);
	}
	// for castling
	if (canCastle(b, "king"))	moves[counter++] = convert('g', getRank());
	if (canCastle(b, "queen"))	moves[counter++] = convert('c', getRank());
}

int King::getRank() { return colour == "white" ? 1 : 8; }

bool King::canCastle(Piece* b[8][8], std::string side) {
	if ((colour == "white" && rank == 1) || (colour == "black" && rank == 8)) {
		// king's side
		if (side == "king")
			return file == 'e' && !hasMoved() && // king is in its original spot and hasn't moved
			b[8 - getRank()]['h' - 'a']->getType() == "rook" && !b[8 - getRank()]['h' - 'a']->hasMoved() && // rook hasn't moved
			b[8 - getRank()]['f' - 'a']->getType() == "empty" && b[8 - getRank()]['g' - 'a']->getType() == "empty"; // empty spaces in between
		// queen's side
		else
			return file == 'e' && !hasMoved() &&
			b[8 - getRank()]['a' - 'a']->getType() == "rook" && !b[8 - getRank()]['a' - 'a']->hasMoved() &&
			b[8 - getRank()]['b' - 'a']->getType() == "empty" && b[8 - getRank()]['c' - 'a']->getType() == "empty" && b[8 - getRank()]['d' - 'a']->getType() == "empty";
	}
	return false;
}
