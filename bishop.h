#ifndef BISHOP_H
#define BISHOP_H
#include "piece.h"

class Bishop : public Piece {
	public:
		Bishop(char file, int rank, std::string colour);
		void setMoves(Piece* b[8][8]);
};

#endif
