
#include "Knight.hpp"

namespace Pieces {



		/*
		Knight move magic: 
		0b
		00000000
		00000000
		00000000
		01010000
		10001000
		00100000
		10001000
		01010000
	
		0x5088208850

		lCutMask: 
		
		00001111
		00001111
		00001111
		00001111
		00001111
		00001111
		00001111
		00001111

		0x0f0f0f0f0f0f0f0f
	
		rCutMask: 
		
		11110000
		11110000
		11110000
		11110000
		11110000
		11110000
		11110000
		11110000

		0xf0f0f0f0f0f0f0f0

		Check:

	
		11110000
		11110000
		11110000
		11110000
		11110000
		11110000
		11110000
		1111


		*/

	Bitboard Knight::genMoves(Pos p) {

		Bitboard moves = 0x5088208850;

		Bitboard constexpr lCutMask = 0x0f0f0f0f0f0f0f0f;
		Bitboard constexpr rCutMask = 0xf0f0f0f0f0f0f0f0;

		int const shift = (p.row - 2)*8 - p.column + 2;
		if (shift >= 0) {
			moves <<= shift;
		} else {
			moves >>= -shift;
		}

		if (p.column < 2) {
			moves &= rCutMask;
		} else if (p.column > 5) {
			moves &= lCutMask;
		}

		return moves;
	}
}