#include "piece.h"

Piece::Piece(char file, int rank, std::string type, std::string colour, bool moved, bool passable) :
file(file), rank(rank), type(type), colour(colour), moved(moved), passable(passable) {
	for (int i = 0; i < 64; ++i) moves[i] = -1;
}

char Piece::getFile() { return file; }

int Piece::getRank() { return rank; }

std::string Piece::getType() { return type; }

std::string Piece::getColour() const { return colour; }

std::string Piece::symbol() const {
	if (type == "pawn")
		return colour == "white" ? "\u2659" : "\u265F";
	else if (type == "knight")
		return colour == "white" ? "\u2658" : "\u265E";
	else if (type == "bishop")
		return colour == "white" ? "\u2657" : "\u265D";
	else if (type == "rook")
		return colour == "white" ? "\u2656" : "\u265C";
	else if (type == "queen")
		return colour == "white" ? "\u2655" : "\u265B";
	else if (type == "king")
		return colour == "white" ? "\u2654" : "\u265A";
	else
		return (file + rank) % 2 == 0 ? "#" : " ";
	return "!";
}

bool Piece::onBoard(char f, int r) { return f >= 'a' && f <= 'h' && r >= 1 && r <= 8; }

int convert(char f, int r) { return (8 - r) * 8 + (f - 'a'); }

void deconvert(int s) {
	char f = s % 8 + 'a';
	int r = 8 - s / 8;
	std::cout << f << r << ' ';
}

void Piece::setMoves(Piece* b[8][8]) { for (int i = 0; i < 64; ++i) moves[i] = -1; }

int Piece::numMoves() {
	int counter = 0;
	while (moves[counter] != -1 && counter < 64)
		counter++;
	return counter;
}

int* Piece::getMoves() { return moves; }

bool Piece::underAttack(Piece* b[8][8], std::string side) {
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			if (b[i][j]->getColour() != "empty" && b[i][j]->getColour() != colour) {
				b[i][j]->setMoves(b);
				for (int c = 0; c < b[i][j]->numMoves(); ++c) {
					if (b[i][j]->getMoves()[c] == convert(file, rank)) return true;
				}
			}
		}
	}
	return false;
}

bool Piece::hasMoved() const { return moved; }

void Piece::setMoved() { moved == false ? moved = true : moved = false; }

void Piece::setPassable() { passable == true ? passable = false : passable = true; }

bool Piece::isPassable() const { return passable; }
