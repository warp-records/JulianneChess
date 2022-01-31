#include "Piece.hpp"

namespace Pieces {
	struct Pawn : public Piece {
		Bitboard genMoves(Pos p);	
	};
}