#ifndef QUEEN_H
#define QUEEN_H
#include "piece.h"

class Queen : public Piece {
	public:
		Queen(char file, int rank, std::string colour);
		void setMoves(Piece* b[8][8]);
};

#endif
