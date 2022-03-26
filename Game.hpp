#include <array>
#include <pair>
#include "Piece.hpp"

class Game {
	GameBoard board;

	//<Piece move map bitboard, piece attack possibilities
	using PieceMoveData = std::pair<Bitboard, 
		std::array<8, Pos>>;

	void genMoves(Piece const& piece);

	//Generate move and attack possibilities
	PieceMoveData genStraightData(Piece const& piece) const;

	PieceMoveData genDiagonalData(Piece const& piece) const;
};