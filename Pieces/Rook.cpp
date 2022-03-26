
#include "Rook.hpp"

namespace Pieces {

	Bitboard Rook::getMoveRange() {
		return MoveTables::Rook[pos.column][pos.row];
	}
}