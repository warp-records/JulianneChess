#include "Piece.hpp"

namespace Pieces {
	struct King : public Piece {
		using Piece::Piece;
		
		bool canCastle = true;

		PieceType getType() const { return PieceType::King; }
		
		Bitboard getMoveRange() const;
		operator std::string() const { return "King"; }
	};
}