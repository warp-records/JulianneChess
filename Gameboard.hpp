#include "Pieces.hpp"
#include <vector>
#include <memory>

#pragma once

class GameBoard {

	/*Having trouble using a unique_ptr while
	iterating. Use shared_ptr will work for now.*/

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

	Team black { Color::Black };
	Team white { Color::White };

	//Board size is 64
	std::array<std::array<Piece*, 8>, 8> board {};

public:
	GameBoard();

	Bitboard getColorBoard(Color color) const;
	Bitboard getWholeBoard() const { return black.teamBitBoard | white.teamBitBoard; }

	
	Bitboard genBitBoard() const;
	Piece const& getPiece(Pos pos) const { return *(board.at(pos.column).at(pos.row)); }
	bool squareOccupied(Pos pos) const { return board.at(pos.column).at(pos.row) != nullptr; }
	void movePiece(Pos start, Pos end);

	//operator std::string const();
};