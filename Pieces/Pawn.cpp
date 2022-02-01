
#include "Pawn.hpp"

namespace Pieces {
	/*
	Pawn move magic:
		With attack:

		00000000
		00000000
		00000000
		00000000
		00000000
		00000000
		10100000
		01000000

		0xa040

		Without attack:

		00000000
		00000000
		00000000
		00000000
		00000000
		00000000
		10000000
		00000000

		0x8000
	*/

	Bitboard Pawn::genMoves() {

		Bitboard moves = 0x8000;

		Bitboard constexpr lCutMask = 0x7f7f7f7f7f7f7f7f;
		Bitboard constexpr rCutMask = 0xfefefefefefefe;

		int const shift = (pos.row - 1)*8 - pos.column;
		if (shift >= 0) {
			moves <<= shift;
		} else {
			moves >>= -shift;
		}

		if (pos.column == 0) {
			moves &= rCutMask;
		} else if (pos.column == 7) {
			moves &= lCutMask;
		}

		return moves;
	}
}