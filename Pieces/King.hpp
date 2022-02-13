#include "Piece.hpp"

namespace Pieces {
	struct King : public Piece {
		King(Pos _pos) { pos = _pos; };

		bool canCastle = true;
		
		Bitboard genMoves();
		operator std::string() const { return "King"; }
	};
}