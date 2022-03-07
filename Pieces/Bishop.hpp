#include "Piece.hpp"

namespace Pieces {
	struct Bishop : public Piece {
		Bishop(Pos _pos) { pos = _pos; };

		PieceType const type = Pieces::Bishop;

		Bitboard getMoveRange();
		operator std::string() const { return "Bishop"; }
	};
}