
//YESSSS HERE WE GOO
#include "Game.hpp"
#include <limits.h>

//Just use piece value as eval function for now
int Game::boardEval() {
	int eval = 0;

	for (uint8_t col = 0; col < 8; col++) {
		for (uint8_t row = 0; row < 8; row++) {

			 if (gameBoard.squareOccupied({row, col})) {
			 	int sign = gameBoard.getPiece({row, col}).getColor() == Color::White ? 1 : -1;

		 		switch (gameBoard.getPiece({row, col}).getType()) {

		 			case (PieceType::Queen) : {
		 				eval += sign*10;
		 			}
		 			case (PieceType::Rook) : {
		 				eval += sign*5;
		 			}
		 			case (PieceType::Bishop) : {}
		 			case (PieceType::Knight) : {
		 				eval += sign*3;
		 			}
		 			case (PieceType::Pawn) : {
		 				eval += sign*1;
		 			}

		 		}
			 }
		}
	}

	return eval;
}

//Either return a move or a board evaluation

using EvalOrMove = std::variant<int, std::pair<Pos, Pos>>;
//Implement alpha beta later... or rather, try!
EvalOrMove Game::miniMax(bool max, int depth) {
	int constexpr maxDepth = 5;

	if (depth == maxDepth) {
		int eval = boardEval();
		return eval;
	}

	Color turnColor = max ? Color::White : Color::Black;

	int sign = max ? 1 : -1;


	std::pair<Pos, Pos> bestMove;
	//I would use std::numeric_limits but it looks like shit

	//I THINK this works out, because if they have no moves on
	//this turn, that would mean it's checkmate (except for stalemate)!
	int bestEval = INT_MAX;

	for (uint8_t row = 0; row < 8; row++) {
		for (uint8_t col = 0; col < 8; col++) {
			//Either no piece or piece is wrong color
			if (!gameBoard.squareOccupied({col, row}) && gameBoard.getPiece({col, row}).getColor() != turnColor)
				continue;

			Piece& piece = gameBoard.getPiece({col, row});

			Bitboard movesBoard = genMoves(piece);

			while (movesBoard) {
				//Note: bbAsPos will select the bottom rightmost
				//bit in a Bitboard
				Pos endPos = bbAsPos(movesBoard);

				movesBoard ^= endPos.asBitBoard();

				gameBoard.movePiece(piece.getPos(), endPos);
				
				int eval = std::get<int>(miniMax(!max, --depth));

				//> op if maximizing, < op if minimizing 
				if (eval*sign > bestEval*sign) {
					bestMove = std::make_pair(piece.getPos(), endPos);
					bestEval = eval;
				}
				//...
				gameBoard.undoMove();
			}
		}
	}

	return depth > 0 ? EvalOrMove(bestEval) : EvalOrMove(bestMove);
}