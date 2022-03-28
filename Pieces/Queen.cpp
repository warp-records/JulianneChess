
#include "Queen.hpp"

namespace Pieces {
	Bitboard Queen::getMoveRange() const {
		return MoveTables::Queen[pos.column][pos.row];
	}
}