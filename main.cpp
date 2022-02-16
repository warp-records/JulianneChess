#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <optional>
#include "Pieces.hpp"
#include "Gameboard.hpp"

#define VERSION "0.2.0"

//Some reason this doesn't link when placed in Piece.hpp or Piece.cpp
std::ostream& operator<<(std::ostream& os, Pos pos) {
	return os << std::string(pos);
}

std::istream& operator>>(std::istream& is, Pos& p) {
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

	p.column = column;
	p.row = row;

	return is;
}

int main() {
	std::cout << "Julianne Chess\n\n" <<
	 "Version " << VERSION << "\n\n";

	std::cout << 
	"   |\\_" <<   "      -----------------\n" <<
  	"  /  .\\_" << "   <  Horsey go MOOO!  >\n" <<
 	" |   ___)" << "  / -----------------\n" <<
 	" |    \\\n" <<
 	" |  =  |\n" <<
 	" /_____\\\n" <<
	"[_______]\n" << std::endl;

	GameBoard board;

	outBitBoard(std::cout, board.genBitBoard());
	
	/*Table format:
	tables are indexed by [Column][Row]
	*/
	Pieces::Bishop bishop({0, 0});
	std::ofstream moveOutput("bishopMoveTable.txt");

	for (uint8_t col = 0; col < 8; col++) {
		moveOutput << "\t\t{";

		for (uint8_t row = 0; row < 8; row++) {
			bishop.setPos({col, row});
			moveOutput << " 0x" <<
			std::hex << std::setfill('0') <<
			std::setw(16) << bishop.genMoves();

			if (row < 7)
				moveOutput << ", ";
		}

		moveOutput << " }";

		if (col < 7)
			moveOutput << ",\n";
	}
	

	return 0;
}