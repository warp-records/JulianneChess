#include "Piece.hpp"

namespace Pieces {
	struct Rook : public Piece {
		Rook(Pos _pos) { pos = _pos; };
		/*Permanently set to false if piece has 
		moved and / or castled*/
		bool canCastle = true;

		PieceType const type = PieceType::Rook;

		//Bitboard genCastle();
		Bitboard getMoveRange();
		std::array<Pos, 8> genAttackList(GameBoard const& gb);
		
		operator std::string() const { return "Rook"; }
	};
}