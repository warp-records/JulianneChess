#include <bit>
#include <optional>
#include <array>
#include <algorithm>
#include "Game.hpp"
#include "Pieces/PieceMoveTables.hpp"


//ok i know its not the best code but like
//who cares ig youll like figure it out or sum
//if you wanna read it XD
PieceMoveData Game::genMoves(Piece const& piece) {
	PieceMoveData data;


	switch (piece.type) {
		case (PieceType::King) : {
			//...
			break;
		}

		case (PieceType::Queen) : {
			//Generate move data for both straight and diagonal moves
			std::pair<PieceMoveData, PieceMoveData> dataParts =
				std::make_pair(genStraightData(piece), genDiagonalData(piece));


			/*Then, copy the attack data from both parts into
			  the final data*/
			std::copy(dataParts.first.second.begin(), 
				dataParts.first.second.end(), data.second.begin());

			std::copy(dataParts.second.second.begin(), 
				dataParts.second.second.end(), data.second.begin() + 4);

			//Finally, combine the movespace bitboards of both
			data.first = dataParts.first.first | dataParts.second.first;
			break;
		}

		case (PieceType::Rook) : {
			data = genStraightData(piece);
			break;
		}

		case (PieceType::Bishop) : {
			data = genDiagonalData(piece);
			break;
		}

		case (PieceType::Knight) : {
			//...
			break;
		}

		case (PieceType::Pawn) : {
			//...
			break;
		}
	}

	return data;
}

PieceMoveData Game::genStraightData(Piece const& piece) const {

	//Note: THE ORDER OF THESE MATTERS!
	std::array<MoveTable const*, 4> constexpr straightRangeTables {{
		&Pieces::MoveTables::upStraight,
		&Pieces::MoveTables::downStraight,
		&Pieces::MoveTables::rightStraight,
		&Pieces::MoveTables::leftStraight
	}};

	//Change later
	Bitboard moveRange = 0x00;
	
	uint8_t numAttacks = 0;

	std::array<Pos, 8> attacks {{ POS_NONE, POS_NONE, POS_NONE, POS_NONE,
						POS_NONE, POS_NONE, POS_NONE, POS_NONE }};

	//Consider creating unpackMoveData() function
	bool spanUp = true;
	for (MoveTable const* table : straightRangeTables) {
		/*std::pair which contains:
		  Bitboard of valid moves
		  optional intersected piece pos*/
		auto movePartData = genMoveDataPart((*table)[piece.getPos().column][piece.getPos().row], spanUp);
		//Every other move is span
		spanUp = !spanUp;

		moveRange |= movePartData.first;

		if (movePartData.second) {
			attacks[numAttacks] = movePartData.second.value();
			numAttacks++;
		}
	}

	return std::make_pair(moveRange, attacks);
}

PieceMoveData Game::genDiagonalData(Piece const& piece) const {
	std::array<MoveTable const*, 4> constexpr diagonalRangeTables {{
		&Pieces::MoveTables::upRight,
		&Pieces::MoveTables::downRight,
		&Pieces::MoveTables::upLeft,
		&Pieces::MoveTables::downLeft
	}};

	Bitboard moveRange = 0x00;
	
	uint8_t numAttacks = 0;

	std::array<Pos, 8> attacks {{ POS_NONE, POS_NONE, POS_NONE, POS_NONE,
						POS_NONE, POS_NONE, POS_NONE, POS_NONE }};

	bool spanUp = true;

	for (MoveTable const* table :diagonalRangeTables) {
		auto movePartData = genMoveDataPart((*table)[piece.getPos().column][piece.getPos().row], spanUp);
		//Every other move is span
		spanUp = !spanUp;

		moveRange |= movePartData.first;

		if (movePartData.second) {
			attacks[numAttacks] = movePartData.second.value();
			numAttacks++;
		}
	}

	return std::make_pair(moveRange, attacks);
}

//<Bitboard move, (optional) attack position>
/*Wether to use MSB or use LSB for finding
the nearest intersected piece*/
std::pair<Bitboard, std::optional<Pos>> 
	Game::genMoveDataPart(Bitboard rangePart, bool spansUp) const {

		/*Select the closest piece to the piece
	we are generating move data for...*/
	uint8_t targetBitIdx = spansUp ? 
			63 - std::countl_zero(rangePart) : std::countr_zero(rangePart);


	Bitboard targetPiece = 0b01;
	/*Select the closest piece to the piece
	we are generating move data for...*/
	targetPiece <<= targetBitIdx;
	//If it's on the board
	targetPiece &= gameBoard.getWholeBoard();

	if (!targetPiece)
		std::make_pair(rangePart, std::nullopt);


	Bitboard rangePartIdx = spansUp ? 
			63 - std::countl_zero(rangePart) 
				: std::countr_zero(rangePart);


	Bitboard clipMask = rangePart;

	if (spansUp) {
		clipMask <<= targetBitIdx - rangePartIdx;
	} else {
		clipMask >>= rangePartIdx - targetBitIdx;
	}

	rangePart &= ~clipMask;

	//x >> 3 divides x by 8 and discards remainder
	return std::make_pair(
				rangePart,
				std::make_optional<Pos>(Pos {targetBitIdx % 8, targetBitIdx >> 3})
			);
}