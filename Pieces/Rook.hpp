#include "Piece.hpp"

namespace Pieces {
	struct Rook : public Piece {
		using Piece::Piece;

		/*Permanently set to false if piece has 
		moved and / or castled*/
		bool canCastle = true;

		PieceType const type = PieceType::Rook;

		//Bitboard genCastle();
		Bitboard getMoveRange();
		operator std::string() const { return "Queen"; }
	};
}