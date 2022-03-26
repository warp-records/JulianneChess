
#include "Queen.hpp"

namespace Pieces {
	Bitboard Queen::getMoveRange() {
		return MoveTables::Queen[pos.column][pos.row];
	}

	std::array<Pos, 8> Queen::genAttackList(GameBoard const& gb) {
		//Implement later
		return std::array<Pos, 8> {};
	}
}