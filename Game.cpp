
#include "Game.hpp"


Game::genMoves(Piece const& piece) {
	/*Optimization note: see Intel POP_CNT
	  instruction*/

	//This works for now I guess
	//if ()
};

Game::genStraightData(Piece const& piece) const {
	//...
	return std::make_pair(0x00, std::array<8, Pos> {{0, 0}});
}

Game::genDiagonalData(Piece const& piece) const {
	//...
	return std::make_pair(0x00, std::array<8, Pos> {{0, 0}});
}