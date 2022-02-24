
#include "../Bitboard.hpp"
#include "Piece.hpp"

//These are pieces of type piece who are only

class NonPiece {
	Pos pos;
	virtual Bitboard genMoves() = 0;
	void setPos(Pos _pos) : pos{_pos} {};

	NonPiece(Pos _pos) : pos{_pos} {};
}

