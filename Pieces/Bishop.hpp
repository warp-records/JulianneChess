#include "Piece.hpp"

namespace Pieces {
	struct Bishop : public Piece {
		using Piece::Piece;

		PieceType const type = PieceType::Bishop;

		Bitboard getMoveRange();
		operator std::string() const { return "Bishop"; }
	};
}