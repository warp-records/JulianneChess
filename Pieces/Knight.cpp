
#include "Knight.hpp"

namespace Pieces {

	Bitboard Knight::getMoveRange() const {
		return MoveTables::Knight[pos.column][pos.row];
	}
}