
#include "Pawn.hpp"

namespace Pieces {

	Bitboard Pawn::getMoveRange() {

		Bitboard moves = 0x8000;

		Bitboard constexpr lCutMask = 0x7f7f7f7f7f7f7f7f;
		Bitboard constexpr rCutMask = 0xfefefefefefefe;

		int const shift = (pos.row - 1)*8 - pos.column;
		if (shift >= 0) {
			moves <<= shift;
		} else {
			moves >>= -shift;
		}

		if (pos.column == 0) {
			moves &= rCutMask;
		} else if (pos.column == 7) {
			moves &= lCutMask;
		}

		return moves;
	}

	std::array<Pos, 8> Pawn::genAttackList(GameBoard const& gb) {
		//Implement later
		return std::array<Pos, 8> {};
	}
}