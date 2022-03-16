
#include "Rook.hpp"

namespace Pieces {

	Bitboard Rook::getMoveRange() {
		return MoveTables::Rook[pos.column][pos.row];
	}

	std::array<Pos, 8> Rook::genAttackList(GameBoard const& gb) {
		//Implement later
		return std::array<Pos, 8> {};
	}
}