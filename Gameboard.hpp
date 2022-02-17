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
		Team(Color _color);
	};

	Team black { Black };
	Team white { White };

public:
	GameBoard();

	//For debugging purposes
	Bitboard genBitBoard() const;
};