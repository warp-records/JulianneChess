#include <iostream>
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
	uint8_t column;
	uint8_t row;
};


//Avoid handling checks, for now
struct Piece {
	//virtual Bitboard genMoves(Boards pieces) = 0;
	/*Allow for a bool paramater when a piece state
	must be passed, etc, a king is in check*/
	//virtual Bitboard genMoves(Boards pieces, bool) = 0;

	//Consider cacheing a piece's bitboard as well as it's position

	Pos getPos(Bitboard piece);
	//Generate a bitboard from a position
	//This is bugged:
	Bitboard getBBoard(Pos p) { return 0b1 << (p.row*8 + 7 - p.column); }
	//STRAIGHT, WHITE M...
	Bitboard straightMoves(Pos p);
	Bitboard diagonalMoves(Pos p);
};
