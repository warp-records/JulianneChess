
#include "Rook.hpp"

namespace Pieces {

	Bitboard Rook::genMoves() {
		return straightMoves();
	}
}