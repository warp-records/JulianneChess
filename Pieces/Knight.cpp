
#include "Knight.hpp"

namespace Pieces {

	Bitboard Knight::getMoveRange() {
		return MoveTables::Knight[pos.column][pos.row];
	}
}