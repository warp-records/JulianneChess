#include "Gameboard.hpp"

#pragma once

class Game {
	GameBoard board;

	void genMoves(Piece const& piece);
};