#include "../Gameboard.hpp"

namespace Pieces {
	struct Knight : public Piece {
		Knight(Pos _pos) { pos = _pos; };
		bool canCastle = true;

		PieceType const type = PieceType::Knight;

		Bitboard getMoveRange();

		operator std::string() const { return "Knight"; }
	};
}