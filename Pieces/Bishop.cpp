
#include "Bishop.hpp"

namespace Pieces {

	Bitboard Bishop::getMoveRange() const {
		return MoveTables::Bishop[pos.column][pos.row];
	}
}