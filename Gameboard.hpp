#include "Pieces.hpp"
#include <vector>
#include <memory>

#pragma once

class GameBoard {

	enum Color { Black, White };

	typedef std::shared_ptr<Piece> PiecePtr;

	struct Team {
		Color color;
		/*Optimize later, after getting a working product.
		Keep a list of all pieces and a list of specific
		piece types, for quicker lookup.
		Consider moving to stack for better performance.*/
		std::vector<PiecePtr> pieceList;
		std::vector<PiecePtr> king, queens, rooks, bishops, knights, pawns;
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
		Team(Color _color);
	};

	Team black { Black };
	Team white { White };

public:
	GameBoard();

	//For debugging purposes
	Bitboard genBitBoard() const;
};