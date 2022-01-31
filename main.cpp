#include <iostream>
#include <string>
#include <optional>
#include "Pieces.hpp"
#include "Bitboard.hpp"

#define VERSION "0.1.0"

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
	"Version: " << VERSION << "\n\nRift84\n\n";

	std::cout << 
	"   |\\_" <<   "      -----------------\n" <<
  	"  /  .\\_" << "   <  Horsey go MOOO!  >\n" <<
 	" |   ___)" << "  / -----------------\n" <<
 	" |    \\\n" <<
 	" |  =  |\n" <<
 	" /_____\\\n" <<
	"[_______]\n" << std::endl;

	Pieces::Queen 	queen;
	Pieces::Bishop 	bishop;
	Pieces::Rook 	rook;
	Pieces::King 	king;
	Pieces::Knight 	knight;
	Pieces::Pawn 	pawn;
	
	/*std::cout << "King moves at " << pos << '\n' << std::endl;
	outBitBoard(std::cout, king.genMoves(pos));

	std::cout << "Queen moves at " << pos << '\n' << std::endl;
	outBitBoard(std::cout, queen.genMoves(pos));

	std::cout << "Bishop moves at " << pos << '\n' << std::endl;
	outBitBoard(std::cout, bishop.genMoves(pos));

	std::cout << "Rook moves at " << pos << '\n' << std::endl;
	outBitBoard(std::cout, rook.genMoves(pos));

	std::cout << "Knight moves at " << pos << '\n' << std::endl;
	outBitBoard(std::cout, knight.genMoves(pos));

	std::cout << "Pawn moves at " << pos << '\n' << std::endl;
	outBitBoard(std::cout, pawn.genMoves(pos));*/

	while (true) {
		char in;

		std::cout << "Select a piece type:\n\n" <<
		"0 - King\n" <<
		"1 - Queen\n" <<
		"2 - Rook\n" <<
		"3 - Bishop\n" <<
		"4 - Knight\n" <<
		"5 - Pawn\n" << 
		"6 - Quit\n\n> " << std::flush;

		std::cin >> in;
		in -= '0';

		if (!std::cin.good() || !(0 <= in && in <= 6)) {
			std::cerr << "Error" << std::endl;
			return -1;
		}

		//I have no clue how else I can do this god damn it this is weird
		Piece* piece = nullptr;

		switch (in) {
			case 0:
				piece = new Pieces::King;
				break;

			case 1:
				piece = new Pieces::Queen;
				break;

			case 2:
				piece = new Pieces::Rook;
				break;

			case 3:
				piece = new Pieces::Bishop;
				break;

			case 4:
				piece = new Pieces::Knight;
				break;

			case 5:
				piece = new Pieces::Pawn;
				break;

			case 6:
				return 0;
		}

		std::cout << "\n\nEnter a position (A1 - H8):\n> "
		<< std::flush;

		Pos pos { 0, 0 };
		std::cin >> pos;

		std::cout <<  "\n\n";

		outBitBoard(std::cout, piece->genMoves(pos), false);

		delete piece;
	}


	return 0;
}