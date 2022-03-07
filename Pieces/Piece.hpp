#include <vector>
#include "../Bitboard.hpp"
#include "PieceMoveTables.hpp"

#pragma once


//Lmao how did I forget to encapsulate all this

namespace Pieces {
	enum Color { Black, White };
	
	enum PieceType { 
		King, Queen, Rook, 
		Bishop, Knight, Pawn
	};
}

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

	void genAttackMap();

	struct {
		//Note: initialize per piece later
		Bitboard allyIntersect = 0x00;
		Bitboard enemyInterset = 0x00;
		bool valid = false;

	} cache;

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

	Bitboard getMoveMap() {};
	//Generate a bitboard from a position

	//Bench straight moves to see how it compares to
	//a lookup table
	/*
	Bitboard straightMoves();
	Bitboard diagonalMoves();
	*/
};