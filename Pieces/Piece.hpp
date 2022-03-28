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
};

/*This really should be inside the Pieces namespace,
but adding it would screw with a lot of code*/
class Piece {
protected:
	Color _color;

	Pos pos;

public:	
	PieceType const type = PieceType::PIECE_TYPE_BASE;

	virtual Bitboard getMoveRange() const = 0;
	virtual operator std::string() const = 0;

	Pos getPos() const { return pos; }

	Bitboard getBBoard() const {
		return 1 << (pos.row*8 + 7 - pos.column);
	}

	Color color() const { return _color; }

	Piece(Color _arg_color, Pos _pos) : 
	_color{_arg_color}, pos{_pos} {}; 
};