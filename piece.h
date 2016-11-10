#ifndef PIECE_H
#define PIECE_H
#include <cstdlib>
#include <string>
#include <iostream>

class Piece {
	protected:
		char file; int rank; // the square where the piece is
		std::string type, colour; // type e.g. pawn, rook, etc. colour white black
		bool moved; // if a piece has moved
		int moves[64];
		bool passable; // for pawns
	public:
		Piece(char file, int rank, std::string type = "empty", std::string colour = "empty", bool moved = false, bool passable = true);
		char getFile();
		int getRank();
		std::string getType();
		std::string getColour() const;
		std::string symbol() const;
		bool onBoard(char f, int r);
		virtual void setMoves(Piece* b[8][8]);
		int numMoves();
		int* getMoves();
		bool underAttack(Piece* b[8][8], std::string side);
		bool hasMoved() const; // for king and rooks
		void setMoved();
		// for pawns
		void setPassable();
		bool isPassable() const;
};

int convert(char f, int r); // e.g. convert h1 to 63

void deconvert(int s); // e.g. convert 63 to h1

#endif
