
#include "Pieces.hpp"

#include <vector>
#include <memory>
#include <array>
//#include "Gameboard.hpp"
#include "Bitboard.hpp"

#pragma once

class Piece;

class GameBoard {
	enum Color { Black, White };

	/*Having trouble using a unique_ptr while
	iterating. Use shared_ptr will work for now.*/

	typedef std::unique_ptr<Piece> PiecePtr;


	/*All this will take up a considerable chunk
	of memory... you may need to move to heap
	to prevent a stack overflow*/
	struct Team {
		Color color;
		/*Optimize later, after getting a working product.
		Keep a list of all pieces and a list of specific
		piece types, for quicker lookup.*/
		std::vector<PiecePtr> pieceList;
		Bitboard bitBoard;

		Team(Color _color);
	};

	Team black { Black };
	Team white { White };

	//Board size is 64
	std::array<std::array<Piece*, 8>, 8> board {};

public:
	GameBoard();

	Bitboard getTeamBitBoard(Pieces::Color color) const { 
		return color == Pieces::Color::Black ? black.bitBoard : white.bitBoard;
	}

	//For debugging purposes
	Bitboard genBitBoard() const;
};

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

	template <typename Funct> Bitboard genValidRange(Funct shiftFunct, int iter);

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