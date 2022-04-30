#include <bit>
#include <optional>
#include <array>
#include <algorithm>
#include <sstream>
#include "Game.hpp"
#include "Pieces/PieceMoveTables.hpp"


//ok i know its not the best code but like
//who cares ig youll like figure it out or sum
//if you wanna read it XD
PieceMoveData Game::genMoves(Piece const& piece) const {

	switch (piece.getType()) {

		case (PieceType::King) : {
			return genKingData(piece);
			break;
		}

		case (PieceType::Queen) : {
			PieceMoveData data;

			//Generate move data for both straight and diagonal moves
			std::pair<PieceMoveData, PieceMoveData> dataParts =
				std::make_pair(genStraightData(piece), genDiagonalData(piece));


			//Combine the movespace of both ranges
			data.first = dataParts.first.first | dataParts.second.first;

			/*Then, copy the attack data from both parts into
			  the final data*/
			std::copy(dataParts.first.second.begin(), 
				dataParts.first.second.end(), data.second.begin());

			std::copy(dataParts.second.second.begin(), 
				dataParts.second.second.end(), data.second.begin() + 4);
			break;
		}

		case (PieceType::Rook) : {
			return genStraightData(piece);
			break;
		}

		case (PieceType::Bishop) : {
			return genDiagonalData(piece);
			break;
		}

		case (PieceType::Knight) : {
			return genKnightData(piece);
			break;
		}

		case (PieceType::Pawn) : {
			return genPawnData(piece);
			break;
		}
	}
}





PieceMoveData Game::genStraightData(Piece const& piece) const {

	//Note: THE ORDER OF THESE MATTERS for the loop to work!
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

	for (MoveTable const* table : diagonalRangeTables) {
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

	Bitboard intersect = rangePart & gameBoard.getWholeBoard();

	/*Select the closest piece to the piece
	we are generating move data for...*/
	uint8_t targetBitIdx = spansUp ? 
			std::countr_zero(intersect) :
			63 - std::countl_zero(intersect);

	Bitboard targetPiece = 0b01;
	targetPiece <<= targetBitIdx;

	Bitboard rangePartIdx = spansUp ? 
			std::countr_zero(rangePart) :
			63 - std::countl_zero(rangePart);


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




PieceMoveData Game::genKnightData(Piece const& piece) const {
	if (piece.getType() != PieceType::Knight)
		throw std::exception();
	
	PieceMoveData data;
	Bitboard moveRange;

	data.first = piece.getMoveRange() ^ gameBoard.getColorBoard(piece.color());
	Bitboard enemyIntersect = piece.getMoveRange() & gameBoard.getColorBoard(!piece.color());

	for (int i = 0; enemyIntersect != 0x00 && i < 8; i++) {
		data.second[i] = { std::countr_zero(enemyIntersect) % 8, 
							std::countr_zero(enemyIntersect) >> 8 };
	}

	return data;
}

PieceMoveData Game::genPawnData(Piece const& piece) const {
	if (piece.getType() != PieceType::Pawn)
		throw std::exception();

	PieceMoveData data;


	if (!(piece.getBBoard() << 8 & gameBoard.getWholeBoard()))
		data.first |= piece.getBBoard() << 8;

	if (piece.getBBoard() << 7 & gameBoard.getColorBoard(!piece.color()) &&
		piece.getPos().column < 7) {

		data.first |= piece.getBBoard() << 7;
		data.second[0] = { piece.getPos().column + 1, piece.getPos().row + 1  };
	}

	if (piece.getBBoard() << 9 & gameBoard.getColorBoard(!piece.color()) &&
			piece.getPos().column > 0) {

		data.first |= piece.getBBoard() << 7;
		data.second[1] = { piece.getPos().column + 1, piece.getPos().row + 1  };
	}

	return data;
}

PieceMoveData Game::genKingData(Piece const& piece) const  {
	if (piece.getType() != PieceType::King)
		throw std::exception();
	
	PieceMoveData data;

	data.first = piece.getMoveRange() & ~gameBoard.getColorBoard(piece.color());
	Bitboard enemyIntersect = piece.getMoveRange() & gameBoard.getColorBoard(!piece.color());

	for (int i = 0; enemyIntersect != 0x00 && i < 8; i++) {
		data.second[i] = { std::countr_zero(enemyIntersect) % 8, 
							std::countr_zero(enemyIntersect) >> 8 };
	}

	return data;
}



void Game::movePiece(Pos start, Pos end) {

	if (!(genMoves(gameBoard.getPiece(start)).first & end.asBitBoard())) {
		std::cerr << "Error: invalid move" << std::endl;
		//throw std::exception();
		return;
	}

	gameBoard.movePiece(start, end);
}

Bitboard Game::getMovesFromPos(Pos pos) const {
	return genMoves(gameBoard.getPiece(pos)).first;
}


std::string Game::gameOutput() const {
	std::ostringstream stream;

	stream << "Will Smith vs Chris Rock:\n\n";
	stream << gameBoard;

	return stream.str();
}