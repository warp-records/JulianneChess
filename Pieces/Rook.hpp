#include "../Gameboard.hpp"

namespace Pieces {
	struct Rook : public Piece {
		Rook(Pos _pos) { pos = _pos; };
		bool canCastle = true;

		PieceType const type = PieceType::Rook;

		//Bitboard genCastle();
		Bitboard getMoveRange();
		
		operator std::string() const { return "Rook"; }
	};
}