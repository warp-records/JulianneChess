
#include "Bishop.hpp"

namespace Pieces {

	Bitboard Bishop::getMoveRange() {
		return MoveTables::Bishop[pos.column][pos.row];
	}
}