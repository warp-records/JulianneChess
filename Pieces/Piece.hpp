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



/*DONT INSTANTIATE THIS! Making this an
abstract class is causing a ton of trouble,
even though it really should be.*/ 

class Piece {
protected:

	Pos pos;
	Bitboard bitboard = 0x00;

	Bitboard genBBoard() {
		if (!bitboard) {
			bitboard = 0x1;
			bitboard <<= (pos.row*8 + 7 - pos.column);
		}

		return bitboard;
	}

public:	

	//virtual Bitboard genMoves(Boards pieces) = 0;
	/*Allow for a bool paramater when a piece state
	must be passed, etc, a king is in check*/
	//virtual Bitboard genMoves(Boards pieces, bool) = 0;
	
	/*Consider using a lookup table instead
	of just generating the moves.*/
	virtual Bitboard genMoves() { throw std::exception(); }
	virtual operator std::string() const { throw std::exception(); }

	Pos getPos() { return pos; }
	Bitboard getBBoard() { return bitboard; }
	//Generate a bitboard from a position
	//This is bugged:

	/*Please note, in the case of a white king, 
	we must acknowledge that it has privelege over
	the other pieces, since it is a STRAIGHT, WHITE, M...*/
	Bitboard straightMoves();
	Bitboard diagonalMoves();

	Piece() { throw std::exception(); }
};