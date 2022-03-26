
#include "Bishop.hpp"

namespace Pieces {

	Bitboard Bishop::getMoveRange() {
		return MoveTables::Bishop[pos.column][pos.row];
	}

	std::array<Pos, 8> Bishop::genAttackList(GameBoard const& gb) {
		//Implement later
		return std::array<Pos, 8> {};
	}
}