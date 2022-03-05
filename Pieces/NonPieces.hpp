
#include "../Bitboard.hpp"
#include "Piece.hpp"

//These are pieces of type piece who are only

namespace Pieces {

	class NonPiece {

	protected:
		Pos pos;

	public:
		NonPiece(Pos _pos) : pos{_pos} {}
		void setPos(Pos _pos) { pos = _pos; }
		virtual Bitboard genMoves() = 0;
	};

	struct upStrt : public NonPiece { upStrt(Pos _pos) : NonPiece(_pos) {}; Bitboard genMoves(); };
	struct downStrt : public NonPiece { downStrt(Pos _pos) : NonPiece(_pos) {}; Bitboard genMoves(); };
	struct rightStrt : public NonPiece { rightStrt(Pos _pos) : NonPiece(_pos) {}; Bitboard genMoves(); };
	struct leftStrt : public NonPiece { leftStrt(Pos _pos) : NonPiece(_pos) {}; Bitboard genMoves(); };

	struct upRight : public NonPiece { upRight(Pos _pos) : NonPiece(_pos) {}; Bitboard genMoves(); };
	//struct downRight : public NonPiece { downRight(Pos _pos) : NonPiece(_pos) {}; Bitboard genMoves(); };
	struct upLeft : public NonPiece { upLeft(Pos _pos) : NonPiece(_pos) {}; Bitboard genMoves(); };
	//struct downLeft : public NonPiece { downLeft(Pos _pos) : NonPiece(_pos) {}; Bitboard genMoves(); };

	/*
	class upRight : NonPiece;
	class downRight : NonPiece;
	class upLeft : NonPiece;
	class downLeft : NonPiece;
	*/

}