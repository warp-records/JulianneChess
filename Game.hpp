#include <array>
#include <tuple>
#include "Pieces/Piece.hpp"
#include "Gameboard.hpp"

using PieceMoveData = std::pair<Bitboard, 
	std::array<Pos, 8>>;

class Game {
	GameBoard gameBoard;

	//<Piece move map bitboard, piece attack possibilities
	static Pos constexpr POS_NONE = { 0xFF, 0xFF };
	void genMoves(Piece const& piece);

	//Generate move and attack possibilities

	PieceMoveData genStraightData(Piece const& piece) const;

	PieceMoveData genDiagonalData(Piece const& piece) const;

std::pair<Bitboard, std::optional<Pos>> 
	genMoveDataPart(Bitboard rangePart, bool useMSB) const;
};