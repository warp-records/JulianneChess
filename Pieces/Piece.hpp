#include <vector>
#include "../Bitboard.hpp"
#include "PieceMoveTables.hpp"

#pragma once


/*Weird huh? It's an experimental code
design I thought I'd try out, I guess
*/
namespace Pieces {
	enum class PieceType { King, Queen, Rook,
						 Bishop, Knight, Pawn };
	enum class Color { Black, White };
};

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

/*This really should be inside the Pieces namespace,
but adding it would screw with a lot of code*/
class Piece {
protected:

	Pos pos;
	//This will be invalidated when the 
	//piece moves. Change later.
	Bitboard bitboard = 0x00;

	Bitboard genBBoard() {
		bitboard = 0x1;
		bitboard <<= (pos.row*8 + 7 - pos.column);

		return bitboard;
	}

public:	

	virtual Bitboard getMoveRange() = 0;
	virtual operator std::string() const = 0;

	Pos getPos() const { return pos; }
	Bitboard getBBoard() {
		if (!bitboard) {
			bitboard = genBBoard();
		}

		return bitboard;
	}

};