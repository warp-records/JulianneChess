#include "Piece.hpp"

namespace Pieces {
	struct Knight : public Piece {
		Bitboard genMoves(Pos p);
	};
}