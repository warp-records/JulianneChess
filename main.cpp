#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>
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

template<typename P> std::stringstream genBBTable();

int main() {
	std::cout << "Julianne Chess\n\n";

	std::cout << 
	"   |\\_" <<   "      -----------------\n" <<
  	"  /  .\\_" << "   <  Horsey go MOOO!  >\n" <<
 	" |   ___)" << "  / -----------------\n" <<
 	" |    \\\n" <<
 	" |  =  |\n" <<
 	" /_____\\\n" <<
	"[_______]\n" << std::endl;

	std::cout << "Move Bitboards are indexed by [Column][Row]." << 
	"Use the output to initialize a data structure to store your magics.\n" <<
	"Generating magic..." << std::flush;

	std::ofstream kingTable("kingTable.txt");
	kingTable << genBBTable<Pieces::King>().str();

	std::ofstream queenTable("queenTable.txt");
	queenTable << genBBTable<Pieces::Queen>().str();

	std::ofstream rookTable("rookTable.txt");
	rookTable << genBBTable<Pieces::Rook>().str();

	std::ofstream bishopTable("bishopTable.txt");
	bishopTable << genBBTable<Pieces::Bishop>().str();

	std::ofstream knightTable("knightTable.txt");
	knightTable << genBBTable<Pieces::Knight>().str();

	std::cout << "\n\nDone!\n";
	
	/*Table format:
	tables are indexed by [Column][Row]
	*/
	

	return 0;
}



//It's really sloppy but I don't feel like creating an entire external class for it
//STUPID HORSE I JUST FELL OUT OF THE PORSCHE!

template<typename P> std::stringstream genBBTable() {
	P piece({0, 0});
	std::stringstream ss;

	ss << "{\n";
	for (uint8_t col = 0; col < 8; col++) {
		ss << "\t\t{";

		for (uint8_t row = 0; row < 8; row++) {
			piece.setPos({col, row});
			ss << " 0x" <<
			std::hex << std::setfill('0') <<
			std::setw(16) << piece.genMoves();

			if (row < 7)
				ss << ",";
		}

		ss << " }";

		if (col < 7)
			ss << ",\n";
	}

	ss << "\n}";

	return ss;
}