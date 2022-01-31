
#include "Queen.hpp"

namespace Pieces {
	Bitboard Queen::genMoves(Pos pos) {
		return diagonalMoves(pos) | straightMoves(pos);
	}
}