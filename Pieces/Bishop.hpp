#include "Piece.hpp"

namespace Pieces {
	struct Bishop : public Piece {
		Bitboard genMoves(Pos p);
	};
}