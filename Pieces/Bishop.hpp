#include "Piece.hpp"

namespace Pieces {
	struct Bishop : public Piece {
		Bishop(Pos _pos) { pos = _pos; };

		PieceType const type = PieceType::Bishop;

		Bitboard getMoveRange();
		//Get directional ranges
		std::array<Pos, 8> genAttackList(GameBoard const& gb);

		operator std::string() const { return "Bishop"; }
	};
}