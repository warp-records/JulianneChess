
#include "Bishop.hpp"

namespace Pieces {

	Bitboard Bishop::genMoves() {
		return MoveTables::Bishop[pos.column][pos.row];
	}
}