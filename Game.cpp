#include <bit>
#include "Game.hpp"
#include "Pieces/PieceMoveTables.hpp"


Game::genMoves(Piece const& piece) {

	//This works for now I guess
	//if ()
};

/*Consdier using a hardware accelerated approach later*/

PieceMoveData Game::genStraightData(Piece const& piece) const {
	//...
	return std::make_pair(0x00, std::array<8, Pos> {{0, 0}});
}

PieceMoveData Game::genDiagonalData(Piece const& piece) const {
	//...
	return std::make_pair(0x00, std::array<8, Pos> {{0, 0}});
}