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

	//Pretty clever huh! One night I had a high IQ moment and thought of this
	Bitboard upRight::genMoves() {
		Bitboard board = 0x0102040810204080;
		board >>= std::max(pos.column, pos.row) * 8;
		board <<= pos.row * 8 + (pos.row > pos.column ? pos.row - pos.column : 0);

		return board;
	}

	Bitboard upLeft::genMoves() {
		Bitboard board = 0x8040201008040201;
		board >>= std::max((uint8_t) (7 - pos.column), pos.row) * 8;
		board <<= pos.row * 8 - (pos.row > (7 - pos.column) ? pos.row - (7 - pos.column) : 0);

		return board;
	}

	Bitboard downRight::genMoves() {
		Bitboard board = 0x8040201008040201;
		board <<= std::max(pos.column, (uint8_t) (7 - pos.row)) * 8;
		board >>= (7 - pos.row) * 8 - (pos.column < (7 - pos.row) ? (7 - pos.row) - pos.column : 0);

		return board;
	}

	Bitboard downLeft::genMoves() {
		Bitboard board = 0x0102040810204080;
		board <<= std::max((uint8_t) (7 - pos.column), (uint8_t) (7 - pos.row)) * 8;
		board >>= (7 - pos.row) * 8 + (pos.column > pos.row ? pos.column - pos.row : 0);

		return board;
	}

}