#include "Piece.hpp"

namespace Pieces {
	struct Knight : public Piece {
		Knight(Pos _pos) { pos = _pos; };
		bool canCastle = true;

		Bitboard genMoves();
	};
}