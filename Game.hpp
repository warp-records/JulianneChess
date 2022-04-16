#include <array>
#include <tuple>
#include "Pieces/Piece.hpp"
#include "Gameboard.hpp"
#include <iostream>

using PieceMoveData = std::pair<Bitboard, 
	std::array<Pos, 8>>;

class Game {
	GameBoard gameBoard;

	//<Piece move map bitboard, piece attack possibilities
	static Pos constexpr POS_NONE = { 0xFF, 0xFF };
	PieceMoveData genMoves(Piece const& piece) const;

	//Generate movespace and attack possibilities pair

	//Note: NONE of these test for CHECK! This must be
	//Implemented later
	PieceMoveData genStraightData(Piece const& piece) const;
	PieceMoveData genDiagonalData(Piece const& piece) const;

	PieceMoveData genKnightData(Piece const& piece) const;
	PieceMoveData genPawnData(Piece const& piece) const;
	PieceMoveData genKingData(Piece const& piece) const;


	/*Generate movespace and attack possibilities given
	a move part range, and wether it points upwards or downwards*/
	std::pair<Bitboard, std::optional<Pos>> 
		genMoveDataPart(Bitboard rangePart, bool spanUp) const;

public:

	/*Note: this interface should NOT be used as a final
	interface! You should redesign this - this should be used
	for debugging movegen ONLY*/
	//Debug functions
	Bitboard getMovesFromPos(Pos pos) const;
	Bitboard getBitBoard() const { return gameBoard.getWholeBoard(); }
	void movePiece(Pos start, Pos end);

	std::string gameOutput() const;
};
