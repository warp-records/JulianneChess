#include "../Gameboard.hpp"
#include "PieceMoveTables.hpp"

#pragma once

namespace Pieces {
	struct Knight : public Piece {
		Knight(Pos _pos) { pos = _pos; };
		bool canCastle = true;

		Pieces::PieceType const type = Pieces::PieceType::Knight;

		Bitboard getMoveRange();

		operator std::string() const { return "Knight"; }
	};
}