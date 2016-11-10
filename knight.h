#ifndef KNIGHT_H
#define KNIGHT_H
#include "piece.h"

class Knight : public Piece {
	public:
		Knight(char file, int rank, std::string colour);
		void setMoves(Piece* b[8][8]);
};

#endif
