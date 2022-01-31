
#include "Rook.hpp"

namespace Pieces {

	Bitboard Rook::genMoves(Pos pos) {
		return straightMoves(pos);
	}
}