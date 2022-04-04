#include "Piece.hpp"

namespace Pieces {
	struct Bishop : public Piece {
		using Piece::Piece;

		type = PieceType::Bishop;

		Bitboard getMoveRange() const;
		operator std::string() const { return "Bishop"; }
	};
}