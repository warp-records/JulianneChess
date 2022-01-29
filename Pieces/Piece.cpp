#include <cstdint>
#include <cmath>
#include "Piece.hpp"

/*Pos Piece::getPos(Bitboard piece) {
		//Maybe be memory conservative
		//for deep move generation
		//Start one out of bounds because of pre-increment and pre-decrement
		uint8_t row = 0, column = 7;

		//Note: the calculatd row and column are endian dependent
		//Consider calculating beforehand

		//Using a binary search would result in
		//a quicker search.
		for (size_t mask = 0xFF; piece & mask == 0x00; mask <<= 8) {
			row++;
		}

		for (uint8_t mask = 0x01 << row; piece & mask == 0x00; mask <<= 1) {
			column--;
		}

		return { row, column };
}*/





Pos Piece::getPos(Bitboard piece) {
		/*Maybe be memory conservative
		for deep move generation*/
		//Start one out of bounds because of pre-increment and pre-decrement
		uint8_t row = 0, column = 7;

		//Note: the calculated row and column are endian dependent
		//Consider calculating beforehand

		/*Using a binary search would result in
		a quicker search.*/
		uint64_t n = 0b1;

		int i = 0;
		for (; n != piece; i++, n<<=1);

		return { i / 8, 7 - (i % 8) };
}


/*
Left to right diagonal:
10000000
01000000
00100000
00010000
00001000
00000100
00000010
00000001

Magic for left to right diagonal:
0x0102040810204080



Magic for right to left diagonal:
01
02
04
08
10
20
40
80

0x8040201008040201
*/

Bitboard Piece::straightMoves(Pos p) {

	//board |= (0xFF << (p.row*8));
	uint64_t board = 0xFF;
	board <<= p.row*8;

	//Magic for leftmost column
	board |= (0x8080808080808080 >> p.column);

	return board;
}

/*
Magic for left column:
0x8080808080808080

10000000
10000000
10000000
10000000
10000000
10000000
10000000
10000000

Magic for right column:
0x101010101010101
*/



Bitboard Piece::diagonalMoves(Pos p) {
	//Magic for left to right diagonal
	uint64_t lrLine = 0x0102040810204080;
	uint64_t rlLine = 0x8040201008040201;

	uint64_t lCutMask = 0x8080808080808080;
	uint64_t rCutMask = 0x101010101010101;

	uint64_t board = 0x00;

	//Distance to move each diagonal from the point 0, 0
	int8_t lDist = p.column - p.row;

	if (lDist >= 0) {
		lrLine >>= lDist;

		for (int i = 0; i < lDist; i++)
			lrLine &= ~(lCutMask >> i);
	} else {
		lDist = std::abs(lDist);
		lrLine <<= lDist;

		for (int i = 0; i < lDist; i++)
			lrLine &= ~(rCutMask << i);
	}

	int8_t rDist = p.column + p.row - 7;

	if (rDist >= 0) {
		rlLine >>= rDist;

		for (int i = 0; i < rDist; i++)
			rlLine &= ~(lCutMask >> i);
	} else {
		rDist = std::abs(rDist);

		rlLine <<= rDist;
		for (int i = 0; i < rDist; i++)
			rlLine &= ~(rCutMask << i);
	}

	board |= lrLine | rlLine;//lrLine | rlLine;

	return board;
}
