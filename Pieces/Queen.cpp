
#include "Queen.hpp"

namespace Pieces {
	Bitboard Queen::genMoves() {
		return diagonalMoves() | straightMoves();
	}
}