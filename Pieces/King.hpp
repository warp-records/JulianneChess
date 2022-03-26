#include "../Gameboard.hpp"
#include "PieceMoveTables.hpp"

#pragma once

namespace Pieces {
	struct King : public Piece {
		King(Pos _pos) { pos = _pos; };
		bool canCastle = true;

		Pieces::PieceType const type = Pieces::PieceType::King;
		
		Bitboard getMoveRange();
		
		operator std::string() const { return "King"; }
	};
}