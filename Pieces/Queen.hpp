#include "Piece.hpp"

namespace Pieces {
	struct Queen : public Piece {
		using Piece::Piece;

		PieceType getType() const { return PieceType::Queen; }

		Bitboard getMoveRange() const;
		operator std::string() const { return "Queen"; }
	};
}