
#include "Bishop.hpp"

namespace Pieces {

	Bitboard Bishop::genMoves() {
		return diagonalMoves();
	}
}