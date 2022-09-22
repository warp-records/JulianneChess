
#include <array>
#include <tuple>
#include "Pieces/Piece.hpp"
#include "Gameboard.hpp"
#include <optional>
#include <iostream>

class Game {

	GameBoard gameBoard;

	struct Cache {
		Bitboard boardIntersect;
		Bitboard moveSpace;
	};
	
	//Cache each piece's move space, along with a list of it's
	//board intersections to check if it's old moves are still valid
	std::unordered_map<const Piece*, Cache> pieceDatCache;
	
	Bitboard genMoves(Piece const& piece);

	//Generate movespace and attack possibilities pair

	//Note: NONE of these test for CHECK! This must be
	//Implemented later
	Bitboard genStraightMoves(Piece const& piece) const;
	Bitboard genDiagonalMoves(Piece const& piece) const;

	Bitboard genKnightMoves(Piece const& piece) const;
	Bitboard genPawnMoves(Piece const& piece) const;
	Bitboard genKingMoves(Piece const& piece) const;

	//Generates **KING'S** castle moves
	Bitboard genCastleMoves(Piece const& piece) const;

	/*Generate movespace a move part range, and wether 
	it points upwards or downwards*/
	Bitboard genMoveSpacePart(Bitboard rangePart, bool spanUp) const;

	//NEEEEEEDS to be optimized!
	bool isCheck_(Color color, std::optional<Pos> kingPosHint = std::nullopt);	

	//Exclusively used for check detecting functions...
	//doesn't behave the same as the rest of the move gen functions
	Bitboard genPawnThreat(Piece const& piece) const;

public:

	/*Note: this interface should NOT be used as a final
	interface! You should redesign this - this should be used
	for debugging movegen ONLY*/
	//Debug functions
	Bitboard getMovesFromPos(Pos pos);
	Bitboard getBitBoard() const { return gameBoard.getWholeBoard(); }

	void movePiece(Pos start, Pos end);

	std::string gameOutput();

	bool isCheck() { return isCheck_(Color::Black) && isCheck_(Color::White); } 

	Game();
};
