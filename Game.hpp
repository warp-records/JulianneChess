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
	PieceMoveData genMoves(Piece const& piece);

	//Generate movespace and attack possibilities pair
	PieceMoveData genStraightData(Piece const& piece) const;

	PieceMoveData genDiagonalData(Piece const& piece) const;

	/*Generate movespace and attack possibilities given
	a move part range, and wether it points upwards or downwards*/
	std::pair<Bitboard, std::optional<Pos>> 
		genMoveDataPart(Bitboard rangePart, bool spanUp) const;
};