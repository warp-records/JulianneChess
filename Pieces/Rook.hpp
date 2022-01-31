#include "Piece.hpp"

namespace Pieces {
	struct Rook : public Piece {
		Bitboard genMoves(Pos p); 
	};
}