#include "Piece.hpp"

namespace Pieces {
	struct Pawn : public Piece {
		Pawn(Pos _pos) { pos = _pos; };

		PieceType const type = PieceType::Pawn;

		Bitboard getMoveRange();
				
		operator std::string() const { return "Pawn"; }
	};
}