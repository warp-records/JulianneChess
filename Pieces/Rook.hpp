#include "../Gameboard.hpp"
#include "PieceMoveTables.hpp"

#pragma once

namespace Pieces {
	struct Rook : public Piece {
		Rook(Pos _pos) { pos = _pos; };
		bool canCastle = true;

		Pieces::PieceType const type = Pieces::PieceType::Rook;

		//Bitboard genCastle();
		Bitboard getMoveRange();
		
		operator std::string() const { return "Rook"; }
	};
}