
#include "Queen.hpp"

namespace Pieces {
	Bitboard Queen::getMoveRange() {
		return MoveTables::Queen[pos.column][pos.row];
	}
}