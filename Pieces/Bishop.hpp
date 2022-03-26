#include "../Gameboard.hpp"
#include "PieceMoveTables.hpp"

#pragma once

namespace Pieces {
	struct Bishop : public Piece {
		Bishop(Pos _pos) { pos = _pos; };

		Pieces::PieceType const type = Pieces::PieceType::Bishop;
		
		Bitboard getMoveRange();
		
		operator std::string() const { return "Bishop"; }
	};
}