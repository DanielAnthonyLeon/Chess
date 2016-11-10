#ifndef PAWN_H
#define PAWN_H
#include "piece.h"

class Pawn : public Piece {
	public:
		Pawn(char file, int rank, std::string colour, bool moved = false, bool passable = false);
		void setMoves(Piece* b[8][8]);
		int increment(); // 1 for white, -1 for black
};

#endif
