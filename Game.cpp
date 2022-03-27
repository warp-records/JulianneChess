#include <bit>
#include <optional>
#include "Game.hpp"
#include "Pieces/PieceMoveTables.hpp"


Game::genMoves(Piece const& piece) {

	//This works for now I guess
	//if ()
};

/*Consdier using a hardware accelerated approach later*/

PieceMoveData Game::genStraightData(Piece const& piece) const {
	//Change later
	std::array<8, Pos> moveData = {{NONE, NONE, NONE, NONE,
							 NONE, NONE, NONE, NONE}};
	//...
	return std::make_pair(moveRange, std::array<8, Pos> {{0, 0}});
}

PieceMoveData Game::genDiagonalData(Piece const& piece) const {
	std::array<8, Pos> moveData = {{NONE, NONE, NONE, NONE,
						 NONE, NONE, NONE, NONE}};
	//...
	return std::make_pair(0x00, std::array<8, Pos> {{0, 0}});
}


//<Bitboard move, (optional) attack position>
/*Wether to use MSB or use LSB for finding
the nearest intersected piece*/
std::pair<Bitboard, std::optional<Pos>> getMoveDataPart(Bitboard rangePart, bool useMSB) {
	Bitboard rangePart = piece.getMoveRange();

		/*Select the closest piece to the piece
	we are generating move data for...*/
	uint8_t targetBitIdx = useMSB ? 
			63 - std::countl_zero(rangePart) : std::countr_zero(rangePart);


	Bitboard targetPiece = 0b01;
	/*Select the closest piece to the piece
	we are generating move data for...*/
	targetPiece <<= targetBitIdx;
	//If it's on the board
	targetPiece &= gameBoard.getWholeBoard();

	if (!targetPiece)
		std::make_pair(rangePart, std::null_opt);


	Bitboard rangePartIdx = MSB ? 
			63 - std::countl_zero(rangePart) 
				: std::countr_zero(rangePart);


	Bitboard clipMask = piece.getMoveRange();

	if (useMSB) {
		clipMask <<= targetBitIdx - rangePartIdx;
	} else {
		clipMask >>= rangePartIdx - targetBitIdx;
	}

	rangePart &= ~clipMask;

	if (targetPiece & gameBoard.getColorBoard(piece.color())) {
		//We can't attack it since it's 

		std::make_pair(rangePart ^ targetPiece, std::null_opt);
	} else {

		//x >> 3 divides x by 8 and discards remainder
		std::make_pair(rangePart,
		 std::make_optional<Pos>({ targetPieceIdx % 8, targetPieceIdx >> 3 }));
	}
}