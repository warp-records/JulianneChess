
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

	Bitboard King::genMoves(Pos p) {
		Bitboard moves = 0x00e0e0e0;

		Bitboard constexpr lCutMask = 0x7f7f7f7f7f7f7f7f;
		Bitboard constexpr rCutMask = 0xfefefefefefefe;

		int const shift = (p.row - 1)*8 - p.column + 1;
		if (shift >= 0) {
			moves <<= shift;
		} else {
			moves >>= -shift;
		}

		if (p.column == 0) {
			moves &= rCutMask;
		} else if (p.column == 7) {
			moves &= lCutMask;
		}

		return moves;
	};
}