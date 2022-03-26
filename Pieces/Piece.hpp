#include <vector>
#include <array>
//#include "Gameboard.hpp"
#include "../Bitboard.hpp"
#include "PieceMoveTables.hpp"

#pragma once


class GameBoard;

/*Weird huh? It's an experimental code
design I thought I'd try out, I guess
*/
namespace Pieces {
	enum class PieceType { King, Queen, Rook,
						 Bishop, Knight, Pawn };

	enum class Color { Black = false, White = true };

	//For some reason this needs to be defined :eye_roll:
};


//Pieces needed for move generation
/*
struct Boards {
	Bitboard ally;
	Bitboard enemy;
};
*/

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
	//A little hacky, but IT'LL WORK... Trust me!
	static GameBoard* gameBoard;

	Pos pos;

	//MUST be initialized by constructor later
	Pieces::Color color;
	//This will be invalidated when the 
	//piece moves. Change later.
	Bitboard bitboard = 0x00;

	Bitboard genBBoard() {
		bitboard = 0x1;
		bitboard <<= (pos.row*8 + 7 - pos.column);

		return bitboard;
	}

	struct {
		bool valid = false;

		//Note: initialize per piece later
		//Bitboard allyIntersect = 0x00;
		//Bitboard enemyInterset = 0x00;

		//List of positions where the Piece can capture another piece
		std::array<Pos, 8> attackList;
		int listLen = 0;
		//Positions that the peice can move to
		Bitboard moveRange;

	} cache;

	//Have piece generate move data, and cache it
	//virtual void updateMoveData() = 0;

	/*Note: make functions for generating straight moves, straight
	attack lists, diagonal moves, and diagonal attack lists. Try 
	implementing them first, and THEN decide how (and if) they will
	be split into functions.*/
	void genStraightMoveData();
	void genDiagonalMoveData();

	template <typename ShiftFunct> Bitboard genValidRange();

public:	
	Bitboard getMoveRange() { return cache.moveRange; }
	std::array<Pos, 8> getAttackList() { return cache.attackList; }

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