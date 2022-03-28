#include "Piece.hpp"

namespace Pieces {
	struct King : public Piece {
		using Piece::Piece;
		
		bool canCastle = true;

		PieceType const type = PieceType::King;

		
		Bitboard getMoveRange() const;
		operator std::string() const { return "King"; }
	};
}