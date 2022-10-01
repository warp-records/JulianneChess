#include <iostream>
#include <sstream>
#include <string>
#include <optional>
#include "Pieces.hpp"
#include "Game.hpp"

#define VERSION "0.4.0"

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
	
	std::cout << "\nPs: now you can type \"undo\"" <<
		" to undo a move!\n" << std::endl;

	while (true) {
		std::cout << game.gameOutput();

		std::cout << "\nPosition of piece to move:" << std::endl;

		std::string strIn;

		std::cin >> strIn;
		if (strIn == "undo") {
			game.undoMove();
			continue;
		}

		Pos piecePos;

		std::stringstream ssOut(strIn);

		ssOut >> piecePos;

		Pos endPos;

		std::cout << "Move piece to:" << std::endl;
		std::cin >> endPos;
		
		game.movePiece(piecePos, endPos);

		std::cout <<  "\n\n";

	}
}