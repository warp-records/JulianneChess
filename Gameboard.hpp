#include "Pieces.hpp"
#include <vector>
#include <optional>
#include <memory>
#include <unordered_map>
#include <iostream>

#pragma once


//Consider just making struct
class GameBoard {

	/*Having trouble using a unique_ptr while
	iterating. Use shared_ptr will work for now.*/

	//typedef std::unique_ptr<Piece> PiecePtr;

	struct MoveData {
		Pos start;
		Pos end;
		bool hasMoved;
		std::optional<Piece*> removedPiece;
	};

	std::vector<MoveData> moveHistory;

	std::vector<MoveData>::iterator currMove = moveHistory.end();

	struct Team {
		Color color;
		/*Optimize later, after getting a working product.
		Keep a list of all pieces and a list of specific
		piece types, for quicker lookup.*/
		std::vector<std::unique_ptr<Piece>> pieceList;
		Bitboard teamBitBoard;

		Team(Color _color);
	};

	/*Need to use brace initialization 
	to avoid vex parsing error*/
	Team black { Color::Black };
	Team white { Color::White };

	//Board size is 64
	std::array<std::array<Piece*, 8>, 8> board {};
	Piece*& getSquare(Pos pos) { return board[pos.column][pos.row]; }

public:
	GameBoard();

	Bitboard getColorBoard(Color color) const;
	Bitboard getWholeBoard() const { return black.teamBitBoard | white.teamBitBoard; }

	
	//Revisit this interface later
	Bitboard genBitBoard() const;
	Piece const& getPiece(Pos pos) const { return *(board.at(pos.column).at(pos.row)); }
	bool squareOccupied(Pos pos) const { return board.at(pos.column).at(pos.row) != nullptr; }

	
	//Make a move and keep track of move history...
	//will probably be useful for minimax
	void movePiece(Pos start, Pos end);
	void undoMove();
	void redoMove();
	//Must explicitly speicfy template arguments to function
	//call since iterators are different types
	int getNumMoves() const { return std::distance<std::vector<MoveData>::const_iterator>(currMove, moveHistory.end()); }; 

	void castleMove(bool kingSide);

};

std::ostream& operator<<(std::ostream& os, GameBoard const& gameBoard);
