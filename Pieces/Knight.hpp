#include "Piece.hpp"

namespace Pieces {
	struct Knight : public Piece {
		Knight(Pos _pos) { pos = _pos; };
		bool canCastle = true;

		PieceType const type = PieceType::Knight;

		Bitboard getMoveRange();
		std::array<Pos, 8> genAttackList(GameBoard const& gb);

		operator std::string() const { return "Knight"; }
	};
}