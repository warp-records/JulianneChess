
#include "Bishop.hpp"

namespace Pieces {

	Bitboard Bishop::gentMoveRange() {
		return MoveTables::Bishop[pos.column][pos.row];
	}
}