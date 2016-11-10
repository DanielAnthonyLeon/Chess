#ifndef KING_H
#define KING_H
#include "piece.h"

class King : public Piece {
	public:
		King(char file, int rank, std::string colour, bool moved = false);
		void setMoves(Piece* b[8][8]);
		int getRank(); // 1 for white and 8 for black
		bool canCastle(Piece* b[8][8], std::string side); // king's or queen's side
};

#endif
