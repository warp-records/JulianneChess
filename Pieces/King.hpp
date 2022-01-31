#include "Piece.hpp"

namespace Pieces {
	struct King : public Piece {
		Bitboard genMoves(Pos p);
	};
}