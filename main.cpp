#include <iostream>
#include <string>
#include "Pieces.hpp"
#include "Bitboard.hpp"

//Some reason this doesn't link when placed in Piece.hpp or Piece.cpp
std::ostream& operator<<(std::ostream& os, Pos p) {
	return os << "(column, row):\n(" << (int) p.column <<
	", " << (int) p.row << ")" << std::endl;
}

std::istream& operator>>(std::istream& is, Pos& p) {
	char colIn, rowIn;
	uint8_t column, row;
	is >> colIn;
	is >> rowIn;

	if (!isdigit(colIn))
		throw std::exception();

	//SCREW IT, we're doing it the C way!
	column = colIn - '0';
	if (column > 8)
		throw std::exception();

	rowIn = tolower(rowIn);
	if (rowIn > 'a' || 'h' < rowIn)
		throw std::exception();

	row = rowIn - 'a';

	p.column = column;
	p.row = row;

	return is;
}

int main() {
	std::string const version = "0.0.1";

	std::cout << "JulianneChess\n\n" <<
	"Version: " << version << "\n\n";

	std::cout << 
	"   |\\_" <<   "      -----------------\n" <<
  	"  /  .\\_" << "   <  Horsey go MOOO!  >\n" <<
 	" |   ___)" << "  / -----------------\n" <<
 	" |    \\\n" <<
 	" |  =  |\n" <<
 	" /_____\\\n" <<
	"[_______]" << std::endl;

	Pieces::Bishop testPiece;

	Pos p {6, 2};//testPiece.getPos(testBoard);
	std::cout << p << std::endl;

	outBitBoard(std::cout, testPiece.diagonalMoves(p));

	return 0;
}