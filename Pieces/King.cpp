
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

	Bitboard King::getMoveRange() const {
		return MoveTables::King[pos.column][pos.row];
	}
}