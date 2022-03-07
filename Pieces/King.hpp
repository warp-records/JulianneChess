#include "Piece.hpp"

namespace Pieces {
	struct King : public Piece {
		King(Pos _pos) { pos = _pos; };
		bool canCastle = true;

		//PieceType const type = Pieces::King;

		
		Bitboard getMoveRange();
		operator std::string() const { return "King"; }
	};
}