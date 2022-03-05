#include "NonPieces.hpp"

/*

*/

namespace Pieces {

	Bitboard upStrt::genMoves() {
		//Vertical line on column 0
		Bitboard board = 0x0101010101010101;
		board <<= pos.row*8 + (7 - pos.column);

		return board;
	}

	Bitboard downStrt::genMoves() {
		//Vertial line on column 7
		Bitboard board = 0x8080808080808080;
		board >>= (7 - pos.row)*8 + pos.column;

		return board;
	}

	Bitboard rightStrt::genMoves() {
		//Horizontal line on row 0
		Bitboard board = 0x00000000000000FF;
		board >>= pos.column;
		board <<= pos.row * 8;

		return board;
	}

	Bitboard leftStrt::genMoves() {
		//Horizontal line on row 7
		Bitboard board = 0xFF00000000000000;
		board <<= 7 - pos.column;
		board >>= (7 - pos.row)*8;

		return board;
	}
}