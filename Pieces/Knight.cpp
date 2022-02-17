
#include "Knight.hpp"

namespace Pieces {

	Bitboard Knight::genMoves() {
		return MoveTables::Knight[pos.column][pos.row];
	}
}