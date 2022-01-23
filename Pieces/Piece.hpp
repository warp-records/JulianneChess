#include <vector>
#include "../Bitboard.hpp"

#pragma once

/*Weird huh? It's an experimental code
design I thought I'd try out, I guess
*/
//Pieces needed for move generation
struct Boards {
	Bitboard piece;
	Bitboard ally;
	Bitboard enemy;
};

struct Pos {
	uint8_t row;
	uint8_t column;
};

struct Piece {
	//virtual Bitboard genMoves(Boards pieces) = 0;
	/*Allow for a bool paramater when a piece state
	must be passed, etc, a king is in check*/
	//virtual Bitboard genMoves(Boards pieces, bool) = 0;

	Pos getPos(Bitboard piece);
	//STRAIGHT, WHITE M...
	Bitboard straightMoves(Boards pieces);
	Bitboard diagonalMoves(Boards pieces);
};