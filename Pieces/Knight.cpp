
#include "Knight.hpp"

namespace Pieces {

	Bitboard Knight::getMoveRange() {
		return MoveTables::Knight[pos.column][pos.row];
	}

	std::array<Pos, 8> Knight::genAttackList(GameBoard const& gb) {
		//Implement later
		return std::array<Pos, 8> {};
	}
}