#include "Pieces.hpp"
#include <vector>
#include <memory>

#pragma once

enum Color { Black, White };

class GameBoard {

	typedef std::vector<std::shared_ptr<Piece>> PieceList;
	typedef std::shared_ptr<Piece> PiecePtr;

	struct Team {
		Color color;
		/*Optimize later, after getting a working product.
		Keep a list of all pieces and a list of specific
		piece types, for quicker lookup.
		Consider moving to stack for better performance.*/
		PieceList pieceLists;
		PieceList king, queens, rooks, bishops, knights, pawns;
		Bitboard teamBoard;
		/*
		
		Black board:
		0b
		11111111
		11111111
		00000000
		00000000
		00000000
		00000000
		00000000
		00000000

		0xFFFF000000000000

		White board:
		0b
		00000000
		00000000
		00000000
		00000000
		00000000
		00000000
		11111111
		11111111

		0x000000000000FFFF
		*/
	}

	Team black(Black);
	Team white(White);

public:
	GameBoard();
	Team(Color _color);
};