#include <vector>
#include "../Bitboard.hpp"

#pragma once

/*Weird huh? It's an experimental code
design I thought I'd try out, I guess
*/
struct Piece {
	virtual Bitboard genMoves(Bitboard piece, Bitboard board) = 0;
	/*Allow for a bool paramater when a piece state
	must be passed, etc, a king is in check*/
	virtual Bitboard genMoves(Bitboard piece, bool, Bitboard board) = 0;
};