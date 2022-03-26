#include "Piece.hpp"

namespace Pieces {
	struct Pawn : public Piece {
		using Piece::Piece;

		PieceType const type = PieceType::Pawn;

		Bitboard getMoveRange();
		operator std::string() const { return "Pawn"; }
	};
}