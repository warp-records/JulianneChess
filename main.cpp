#include <iostream>
#include <string>
#include <optional>
#include "Pieces.hpp"
#include "Game.hpp"

#define VERSION "0.3.1"

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