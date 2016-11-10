#include "board.h"

Board::Board() : turn("white") {
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j)
			position[i][j] = potential[i][j] = NULL;
	}
	for (int i = 0; i < 256; ++i)
		moves[i][0] = moves[i][1] = reals[i][0] = reals[i][1] = -1;
}

Board::~Board() { clear(); }

void Board::clear() {
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			if (position[i][j]) delete position[i][j];
			if (potential[i][j]) delete potential[i][j];
		}
	}
}

std::ostream& operator<<(std::ostream& out, const Board& b) {
	int r = 8;
	for (int i = 0; i < 8; ++i) {
		b.turn == "white" ? out << r-- << ' ' : out << 9 - r-- << ' ';
		for (int j = 0; j < 8; ++j) {
			b.turn == "white" ? out << b.position[i][j]->symbol() << ' ' : out << b.position[7 - i][7 - j]->symbol() << ' ';
		}
		out << '\n';
	}
	b.turn == "white" ? out << "  a b c d e f g h" : out << "  h g f e d c b a";
	return out;
}

Piece* Board::make(char f, int r, std::string type, std::string colour, bool moved, bool passable) {
	if (type == "pawn") return new Pawn(f, r, colour, moved, passable);
	else if (type == "knight") return new Knight(f, r, colour);
	else if (type == "bishop") return new Bishop(f, r, colour);
	else if (type == "rook") return new Rook(f, r, colour, moved);
	else if (type == "queen") return new Queen(f, r, colour);
	else if (type == "king") return new King(f, r, colour, moved);
	else return new Piece(f, r);
}

Piece* Board::make(Piece* p) { return make(p->getFile(), p->getRank(), p->getType(), p->getColour(), p->hasMoved(), p->isPassable()); }

void Board::defaultBoard() {
	if (position[0][0]) clear();
	for (int i = 2; i < 6; ++i) {
		for (int j = 0; j < 8; ++j)
			position[i][j] = new Piece(j + 'a', 8 - i);
	}
	// setting up the pawns
	for (int j = 0; j < 8; ++j) {
		position[8 - 2][j] = new Pawn(j + 'a', 2, "white");
		position[8 - 7][j] = new Pawn(j + 'a', 7, "black");
	}
	// setting up the pieces
	position[8 - 1]['a' - 'a'] = new Rook('a', 1, "white"); position[8 - 8]['a' - 'a'] = new Rook('a', 8, "black");
	position[8 - 1]['h' - 'a'] = new Rook('h', 1, "white"); position[8 - 8]['h' - 'a'] = new Rook('h', 8, "black");
	position[8 - 1]['b' - 'a'] = new Knight('b', 1, "white"); position[8 - 8]['b' - 'a'] = new Knight('b', 8, "black");
	position[8 - 1]['g' - 'a'] = new Knight('g', 1, "white"); position[8 - 8]['g' - 'a'] = new Knight('g', 8, "black");
	position[8 - 1]['c' - 'a'] = new Bishop('c', 1, "white"); position[8 - 8]['c' - 'a'] = new Bishop('c', 8, "black");
	position[8 - 1]['f' - 'a'] = new Bishop('f', 1, "white"); position[8 - 8]['f' - 'a'] = new Bishop('f', 8, "black");
	position[8 - 1]['d' - 'a'] = new Queen('d', 1, "white"); position[8 - 8]['d' - 'a'] = new Queen('d', 8, "black");
	position[8 - 1]['e' - 'a'] = new King('e', 1, "white"); position[8 - 8]['e' - 'a'] = new King('e', 8, "black");
	// make the previous board
}

void Board::setMoves() {
	for (int i = 0; i < 256; ++i) moves[i][0] = moves[i][1] = -1; // reset the moves
	int counter = 0;
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			if (position[i][j]->getColour() == turn) {
				position[i][j]->setMoves(position);
				for (int c = 0; c < position[i][j]->numMoves(); ++c) {
					moves[counter][0] = i * 8 + j;
					moves[counter][1] = position[i][j]->getMoves()[c];
					counter++;
				}
			}
		}
	}
}

int Board::numMoves() {
	int counter = 0;
	while (moves[counter][0] != -1 && counter < 256)
		counter++;
	return counter;
}

bool Board::isCheck(Piece* b[8][8], std::string side) {
	int Ki, Kj; // coordinates for the king
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			if (b[i][j]->getType() == "king" && b[i][j]->getColour() == side) {
				Ki = i; Kj = j;
			}
		}
	}
	// is the king being attacked?
	return b[Ki][Kj]->underAttack(b, side);
}

void Board::castle(Piece* b[8][8], std::string colour, std::string side) {
	int r;
	colour == "white" ? r = 1 : r = 8;
	// king's side
	if (side == "king") {
		delete b[8 - r]['e' - 'a']; b[8 - r]['e' - 'a'] = make('e', r);
		delete b[8 - r]['f' - 'a']; b[8 - r]['f' - 'a'] = make('f', r, "rook", colour, true);
		delete b[8 - r]['g' - 'a']; b[8 - r]['g' - 'a'] = make('g', r, "king", colour, true);
		delete b[8 - r]['h' - 'a']; b[8 - r]['h' - 'a'] = make('h', r);
	}
	// queen's side
	else {
		delete b[8 - r]['a' - 'a']; b[8 - r]['a' - 'a'] = make('a', r);
		delete b[8 - r]['b' - 'a']; b[8 - r]['b' - 'a'] = make('b', r);
		delete b[8 - r]['c' - 'a']; b[8 - r]['c' - 'a'] = make('c', r, "king", colour, true);
		delete b[8 - r]['d' - 'a']; b[8 - r]['d' - 'a'] = make('d', r, "rook", colour, true);
		delete b[8 - r]['e' - 'a']; b[8 - r]['e' - 'a'] = make('e', r);
	}
}

void Board::move(Piece *b[8][8], char f1, int r1, char f2, int r2) {
	// is the king trying to castle?
	if (b[8 - r1][f1 - 'a']->getType() == "king" && abs(f2 - f1) > 1) {
		std::string side;
		f2 == 'g' ? side = "king" : side = "queen";
		castle(b, turn, side);
	}
	// is a pawn trying to en passant?
	else if (b[8 - r1][f1 - 'a']->getType() == "pawn" && abs(f2 - f1) == 1 && abs(r2 - r1) == 1) {
		delete b[8 - r2][f2 - 'a']; b[8 - r2][f2 - 'a'] = make(f2, r2, "pawn", b[8 - r1][f1 - 'a']->getColour(), true, false);
		delete b[8 - r1][f1 - 'a']; b[8 - r1][f1 - 'a'] = make(f1, r1);
		delete b[8 - r1][f2 - 'a']; b[8 - r1][f2 - 'a'] = make(f2, r1);
	}
	else {
		delete b[8 - r2][f2 - 'a']; b[8 - r2][f2 - 'a'] = make(f2, r2, b[8 - r1][f1 - 'a']->getType(), b[8 - r1][f1 - 'a']->getColour(), true, false);
		delete b[8 - r1][f1 - 'a']; b[8 - r1][f1 - 'a'] = make(f1, r1);
		if (b[8 - r2][f2 - 'a']->getType() == "pawn" && abs(r2 - r1) == 2) b[8 - r2][f2 - 'a']->setPassable(); // for en passant
	}
}

void Board::setReals() {
	for (int i = 0; i < 256; ++i) reals[i][0] = reals[i][1] = -1; // reset the reals
	setMoves(); // set the moves, without check
	// make a move on the potential position
	char f1, f2; int r1, r2;
	int counter = 0;
	for (int c = 0; c < numMoves(); ++c) {
	// make the potential board
		for (int i = 0; i < 8; ++i) {
			for (int j = 0; j < 8; ++j) {
				if (potential[i][j]) delete potential[i][j];
				potential[i][j] = make(position[i][j]);
			}
		}
		f1 = moves[c][0] % 8 + 'a'; r1 = 8 - moves[c][0] / 8;
		f2 = moves[c][1] % 8 + 'a'; r2 = 8 - moves[c][1] / 8;
		move(potential, f1, r1, f2, r2); // make the move on the potential board
		// does the move put the king in check?
		if (!isCheck(potential, turn)) {
			reals[counter][0] = moves[c][0];
			reals[counter][1] = moves[c][1];
			counter++;
		}
	}
}

int Board::numReals() {
	int counter = 0;
	while (reals[counter][0] != -1 && counter < 256)
		counter++;
	return counter;
}

bool Board::isCheckmate() {
	return numReals() == 0 && isCheck(position, turn);
}

bool Board::isStalemate() {
	return numReals() == 0 && !isCheck(position, turn);
}

bool Board::isLegal(char f1, int r1, char f2, int r2) {
	for (int c = 0; c < 256; ++c) {
		if (reals[c][0] == convert(f1, r1) && reals[c][1] == convert(f2, r2)) return true;
	}
	return false;
}

void Board::promotion(char f, int r) {
	if (position[8 - r][f - 'a']->getType() == "pawn" && (r == 8 || r == 1)) {
		std::cout << "How would you like to promote your pawn? ";
		std::string piece;
		std::cin >> piece; std::cout << std::endl;
		delete position[8 - r][f - 'a']; position[8 - r][f - 'a'] = make(f, r, piece, turn, true, false);
	}
}

void Board::passed() {
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			if (position[i][j]->getType() == "pawn" && position[i][j]->getColour() == turn && position[i][j]->isPassable())
				position[i][j]->setPassable();
		}
	}
}

void Board::game() {
	defaultBoard();
	std::stack<Board> previous;
	char f1, f2; int r1, r2;
	while (true) {
		std::cout << *this << std::endl;
		setReals(); // legal moves
		std::cout << "number of moves: " << numMoves() << std::endl;
		if (isStalemate()) { std::cout << "Stalemate!\n"; break; } // check for stalemate
		if (isCheck(position, turn)) {
			if (isCheckmate()) {
				turn == "white" ? std::cout << "Checkmate! Black wins!\n" : std::cout << "Checkmate! White wins\n"; break; }
			else turn == "white" ? std::cout << "White is in check.\n" : std::cout << "Black is in check.\n";
		}
		std::cin >> f1; // see if make move or undo
		std::cin >> r1;
		// show legal moves
		for (int c = 0; c < numReals(); ++c) {
			if (reals[c][0] == convert(f1, r1)) deconvert(reals[c][1]);
		}
		std::cout << std::endl;
		std::cin >> f2 >> r2;
		if (!isLegal(f1, r1, f2, r2)) std::cout << "Illegal move!\n";
		// make the move
		else {
			// set the previous board
			move(position, f1, r1, f2, r2); // move
			promotion(f2, r2); // see if pawn promotion can be done and does it if it can
			turn == "white" ? turn = "black" : turn = "white"; // change turn
			passed(); // so that en passant only applies for the next move
		}
	}
}
