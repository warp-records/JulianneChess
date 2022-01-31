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

	operator std::string() const {
		std::string str;
		str += 'A' + row;
		str += '0' + column;

		return str;
	} 
};


struct Piece {
	//virtual Bitboard genMoves(Boards pieces) = 0;
	/*Allow for a bool paramater when a piece state
	must be passed, etc, a king is in check*/
	//virtual Bitboard genMoves(Boards pieces, bool) = 0;
	//Consider caching a piece's bitboard as well as it's position
	virtual Bitboard genMoves(Pos pos) = 0;
	virtual Bitboard genMoves(Bitboard piece) {
		return genMoves(getPos(piece));
	}

	Pos getPos(Bitboard piece);
	//Generate a bitboard from a position
	//This is bugged:
	Bitboard getBBoard(Pos p) {
		Bitboard board = 0x1;
		return board << (p.row*8 + 7 - p.column); 
	}
	//STRAIGHT, WHITE M...
	Bitboard straightMoves(Pos p);
	Bitboard diagonalMoves(Pos p);
};