#include "Piece.hpp"

namespace Pieces {
	struct King : public Piece {
		King(Pos _pos) { pos = _pos; };
		bool canCastle = true;

		PieceType const type = PieceType::King;

		
		Bitboard getMoveRange();
		std::array<Pos, 8> genAttackList(GameBoard const& gb);
		
		operator std::string() const { return "King"; }
	};
}