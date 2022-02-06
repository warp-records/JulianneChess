#include "Piece.hpp"

namespace Pieces {
	struct Queen : public Piece {
		Queen(Pos _pos) { pos = _pos; };

		Bitboard genMoves();
		operator std::string() const { return "Queen"; }
	};
}