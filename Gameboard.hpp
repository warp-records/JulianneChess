#include "Pieces.hpp"
#include <vector>
#include <memory>

#pragma once

class GameBoard {
	enum Color { Black, White }

	/*Note: if you copy this into another unique_ptr
	(etc during move space searching), you'll get an
	exception!*/

	typedef std::unique_ptr<Piece> PiecePtr;


	/*All this will take up a considerable chunk
	of memory... you may need to move to heap
	to prevent a stack overflow*/
	struct Team {
		Color color;
		/*Optimize later, after getting a working product.
		Keep a list of all pieces and a list of specific
		piece types, for quicker lookup.*/
		std::vector<PiecePtr> pieceList;
		Bitboard teamBitBoard;

		Team(Color _color);
	};

	Team black { Black };
	Team white { White };

	//Board size is 64
	std::array<std::array<Piece*, 8>, 8> board {};

public:
	GameBoard();

	//For debugging purposes
	Bitboard genBitBoard() const;
};