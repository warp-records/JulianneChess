
#include "King.hpp"

/*
King moves magic:

0b
00000000
00000000
00000000
00000000
00000000
11100000
11100000
11100000

0x00e0e0e0


Left cut mask:
0b
01111111
01111111
01111111
01111111
01111111
01111111
01111111
01111111

0x7f7f7f7f7f7f7f7f

Right cut mask:
11111110
11111110
11111110
11111110
11111110
11111110
11111110

0xfefefefefefefe

*/

namespace Pieces {

	Bitboard King::genMoves() {
		Bitboard moves = 0x00e0e0e0;

		Bitboard constexpr lCutMask = 0x7f7f7f7f7f7f7f7f;
		Bitboard constexpr rCutMask = 0xfefefefefefefe;

		int const shift = (pos.row - 1)*8 - pos.column + 1;
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
	};
}