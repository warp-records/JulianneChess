
#include "Queen.hpp"

namespace Pieces {
	Bitboard Queen::genMoves() {
		return MoveTables::Queen[pos.column][pos.row];
	}
}