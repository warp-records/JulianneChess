#include "../Gameboard.hpp"
#include "PieceMoveTables.hpp"

#pragma once

namespace Pieces {
	struct Queen : public Piece {
		Queen(Pos _pos) { pos = _pos; };

		Pieces::PieceType const type = Pieces::PieceType::Queen;

		Bitboard getMoveRange();

		operator std::string() const { return "Queen"; }
	};
}