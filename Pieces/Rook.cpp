
#include "Rook.hpp"

namespace Pieces {

	Bitboard Rook::genMoves() {
		return MoveTables::Rook[pos.column][pos.row];
	}
}