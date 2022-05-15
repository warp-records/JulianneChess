#include <iostream>
#include <string>
#include <optional>
#include "Pieces.hpp"
#include "Game.hpp"

#define VERSION "0.3.1"

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

	Game game;
	/*
	00000000
	00000000
	00000000
	00000000
	00000000
	00000000
	00000000
	0 1 1 1 0 1 1 0
	*/
	
	while (true) {
		//outBitBoard(std::cout, game.getBitBoard(), false);
		std::cout << game.gameOutput();

		Pos piecePos;

		std::cout << "\nPosition of piece to move:" << std::endl;
		std::cin >> piecePos;


		Pos endPos;

		std::cout << "Move piece to:" << std::endl;
		std::cin >> endPos;

		
		game.movePiece(piecePos, endPos);

		std::cout <<  "\n\n";

	}
}