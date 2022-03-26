#include "../Gameboard.hpp"
#include "PieceMoveTables.hpp"

#pragma once

namespace Pieces {
	struct Pawn : public Piece {
		Pawn(Pos _pos) { pos = _pos; };

		Pieces::PieceType const type = Pieces::PieceType::Pawn;

		Bitboard getMoveRange();
				
		operator std::string() const { return "Pawn"; }
	};
}