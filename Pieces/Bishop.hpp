#include "Piece.hpp"

namespace Pieces {
	struct Bishop : public Piece {
		Bishop(Pos _pos) { pos = _pos; };

		Bitboard getMoveRange();
		operator std::string() const { return "Bishop"; }
	};
}