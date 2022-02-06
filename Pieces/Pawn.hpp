#include "Piece.hpp"

namespace Pieces {
	struct Pawn : public Piece {
		Pawn(Pos _pos) { pos = _pos; };

		Bitboard genMoves();
		operator std::string() const { return "Pawn"; }
	};
}