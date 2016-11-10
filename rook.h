#ifndef ROOK_H
#define ROOK_H
#include "piece.h"

class Rook : public Piece {
	public:
		Rook(char file, int rank, std::string colour, bool moved = false);
		void setMoves(Piece* b[8][8]);
};

#endif
