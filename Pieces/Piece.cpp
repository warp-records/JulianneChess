#include <cstdint>
#include "Piece.hpp"

Bitboard getMoveMap() {
	
}

/*Bitboard Piece::straightMoves() {
	uint64_t board = 0xFF;
	board <<= pos.row*8;

	//Magic for leftmost column
	board |= (0x8080808080808080 >> pos.column);

	return board;
}



Bitboard Piece::diagonalMoves() {
	//Magic for left to right diagonal
	Bitboard lrLine = 0x0102040810204080;
	Bitboard rlLine = 0x8040201008040201;

	Bitboard lCutMask = 0x8080808080808080;
	Bitboard rCutMask = 0x101010101010101;

	uint64_t board = 0x00;

	//Distance to move each diagonal from the point 0, 0
	int8_t lDist = pos.column - pos.row;

	if (lDist >= 0) {
		lrLine >>= lDist;

		for (int i = 0; i < lDist; i++)
			lrLine &= ~(lCutMask >> i);
	} else {
		lDist = -lDist;
		lrLine <<= lDist;

		for (int i = 0; i < lDist; i++)
			lrLine &= ~(rCutMask << i);
	}

	int8_t rDist = pos.column + pos.row - 7;

	if (rDist >= 0) {
		rlLine >>= rDist;

		for (int i = 0; i < rDist; i++)
			rlLine &= ~(lCutMask >> i);
	} else {
		rDist = -rDist;

		rlLine <<= rDist;
		for (int i = 0; i < rDist; i++)
			rlLine &= ~(rCutMask << i);
	}

	board |= lrLine | rlLine;//lrLine | rlLine;

	return board;
}*/