#include "Piece.hpp"

namespace Pieces {
	struct Pawn : public Piece {
		using Piece::Piece;
		bool hasMoved = false;

		PieceType const type = PieceType::Pawn;

		Bitboard getMoveRange() const;
		operator std::string() const { return "Pawn"; }
	};
}