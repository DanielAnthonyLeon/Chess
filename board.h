#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <stack>
#include "pawn.h"
#include "knight.h"
#include "bishop.h"
#include "rook.h"
#include "queen.h"
#include "king.h"

class Board {
	Piece* position[8][8];
	Piece* potential[8][8]; // used to check if a move puts own king in check
	std::string turn; // white or black
	int moves[256][2]; // does not take check into account
	int reals[256][2]; // takes check into account
	public:
		Board();
		~Board();
		void clear();
		Piece* make(char f, int r, std::string type = "empty", std::string colour = "empty", bool moved = false, bool passable = false);
		Piece* make(Piece* p);
		void defaultBoard();
		void setMoves();
		int numMoves();
		bool isCheck(Piece* b[8][8], std::string side);
		void castle(Piece* b[8][8], std::string colour, std::string side);
		void move(Piece* b[8][8], char f1, int r1, char f2, int r2);
		void setReals();
		int numReals();
		bool isCheckmate();
		bool isStalemate();
		bool isLegal(char f1, int r1, char f2, int r2);
		void promotion(char f, int r);
		void passed(); // so that en passant can only be done immediately
		void game();
		friend std::ostream& operator<<(std::ostream& out, const Board& b);
};

#endif
