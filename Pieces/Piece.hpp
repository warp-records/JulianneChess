#include <vector>
#include "../Bitboard.hpp"
#include "PieceMoveTables.hpp"

#pragma once


/*Weird huh? It's an experimental code
design I thought I'd try out, I guess
*/

enum class PieceType { King, Queen, Rook,
						Bishop, Knight, Pawn, PIECE_TYPE_BASE };
enum class Color { Black, White };

Color operator!(Color color);

struct Pos {
	uint8_t column;
	uint8_t row;

	operator std::string() const {
		std::string str;
		str += 'A' + row;
		str += '0' + column;

		return str;
	}

	Bitboard asBitBoard() const {
		Bitboard bb = 0b1;
		bb <<= (row*8 + 7 - column); 

		return bb;
	}
};

/*This really should be inside the Pieces namespace,
but adding it would screw with a lot of code*/
class Piece {
protected:
	Color color;

	Pos pos;

public:	
	virtual PieceType getType() const = 0;

	virtual Bitboard getMoveRange() const = 0;
	virtual operator std::string() const = 0;

	Pos getPos() const { return pos; }
	void setPos(Pos _pos) { pos = _pos; }

	Bitboard getBBoard() const {
		pos.asBitBoard();
	}

	Color getColor() const { return color; }

	Piece(Color _color, Pos _pos) : 
		color{_color}, pos{_pos} {}; 
};