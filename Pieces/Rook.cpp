
#include "Rook.hpp"

namespace Pieces {

	Bitboard Rook::getMoveRange() const {
		return MoveTables::Rook[pos.column][pos.row];
	}
}