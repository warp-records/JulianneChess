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
		bitboard = 0x1;
		bitboard <<= (pos.row*8 + 7 - pos.column);

		return bitboard;
	}

public:	

	/*Allow for a bool paramater when a piece state
	must be passed, etc, a king is in check*/
	
	/*Consider using a lookup table instead
	of just generating the moves.*/

	/*Generate a range of moves for a given
	piece type based on a given position
	*/
	virtual Bitboard genMoves() = 0;
	virtual operator std::string() const = 0;

	Pos getPos() const { return pos; }
	void setPos(Pos newPos) { pos = newPos; }
	Bitboard getBBoard() {
		if (!bitboard) {
			bitboard = genBBoard();
		}

		return bitboard;
	}
	//Generate a bitboard from a position
	//This is bugged:

	/*Please note, in the case of a white king, 
	we must acknowledge that it has privelege over
	the other pieces, since it is a STRAIGHT, WHITE, M...*/
	Bitboard straightMoves();
	Bitboard diagonalMoves();


};