#include <cstdint>
#include <iostream>
#include "Piece.hpp"

Color operator!(Color color) {
	return color == Color::Black ? Color::White : Color::Black;
}

std::ostream& operator<<(std::ostream& os, Pos pos) {
	return os << std::string(pos);
}

std::istream& operator>>(std::istream& is, Pos& pos) {
	char colIn, rowIn;
	uint8_t column, row;
		
	is >> colIn;
	is >> rowIn;

	/*if (!isdigit(colIn))
		throw std::exception();*/

	//SCREW IT, we're doing it the C way!
	row = rowIn - '1';
	if (row < 0 || row > 7)
		throw std::exception();

	colIn = tolower(colIn);
	if (colIn < 'a' || 'h' < colIn)
		throw std::exception();

	column = colIn - 'a';

	pos.column = column;
	pos.row = row;

	return is;
}