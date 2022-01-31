
#include "Bishop.hpp"

namespace Pieces {
	Bitboard Bishop::genMoves(Pos pos) {
		return diagonalMoves(pos);
	}
}