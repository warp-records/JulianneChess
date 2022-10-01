#include <bit>
#include <optional>
#include <array>
#include <algorithm>
#include <sstream>
#include "Game.hpp"
#include "Pieces/PieceMoveTables.hpp"


//Should this return illegal moves too?
Bitboard Game::genMoves(Piece const& piece) {
	Bitboard moveSpace = 0x00;
	
	//Will need to be modified for moves where the king is in check
	if (pieceDatCache[&piece].boardIntersect == 
		piece.getMoveRange() & gameBoard.getWholeBoard() && 
			piece.getType() != PieceType::King) {

		return pieceDatCache[&piece].moveSpace & 
			~gameBoard.getColorBoard(piece.getColor());
	}
	

	switch (piece.getType()) {

		case (PieceType::King) : {
			moveSpace = genKingMoves(piece);
			break;
		}

		case (PieceType::Queen) : {
			moveSpace = genStraightMoves(piece) | genDiagonalMoves(piece);
			break;
		}

		case (PieceType::Rook) : {
			moveSpace = genStraightMoves(piece);
			break;
		}

		case (PieceType::Bishop) : {
			moveSpace = genDiagonalMoves(piece);
			break;
		}

		case (PieceType::Knight) : {
			moveSpace = genKnightMoves(piece);
			break;
		}

		case (PieceType::Pawn) : {
			moveSpace = genPawnMoves(piece);
			break;
		}
	}

	pieceDatCache[&piece].boardIntersect = piece.getMoveRange() & gameBoard.getWholeBoard();
	pieceDatCache[&piece].moveSpace = moveSpace;

	moveSpace &= ~gameBoard.getColorBoard(piece.getColor());

	return moveSpace;
}

Bitboard Game::genStraightMoves(Piece const& piece) const {
	Bitboard moveSpace = 0x00;

	moveSpace |= genMoveSpacePart(Pieces::MoveTables::upStraight
		[piece.getPos().column][piece.getPos().row], true);

	moveSpace |= genMoveSpacePart(Pieces::MoveTables::downStraight
		[piece.getPos().column][piece.getPos().row], false);

	moveSpace |= genMoveSpacePart(Pieces::MoveTables::leftStraight
		[piece.getPos().column][piece.getPos().row], true);

	moveSpace |= genMoveSpacePart(Pieces::MoveTables::rightStraight
		[piece.getPos().column][piece.getPos().row], false);	

	return moveSpace;
}

Bitboard Game::genDiagonalMoves(Piece const& piece) const {
	Bitboard moveSpace = 0x00;

	moveSpace |= genMoveSpacePart(Pieces::MoveTables::upRight
		[piece.getPos().column][piece.getPos().row], true);
	moveSpace |= genMoveSpacePart(Pieces::MoveTables::upLeft
		[piece.getPos().column][piece.getPos().row], true);
	moveSpace |= genMoveSpacePart(Pieces::MoveTables::downRight
		[piece.getPos().column][piece.getPos().row], false);

	moveSpace |= genMoveSpacePart(Pieces::MoveTables::downLeft
		[piece.getPos().column][piece.getPos().row], false);	

	return moveSpace;
}

/*Wether to use MSB or use LSB for finding
the nearest intersected piece*/
Bitboard Game::genMoveSpacePart(Bitboard rangePart, bool spansUp) const {

	Bitboard intersect = rangePart & gameBoard.getWholeBoard();

	if (!intersect)
		return rangePart;

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

	//Make branchless later
	if (spansUp) {
		clipMask <<= targetBitIdx - rangePartIdx;
	} else {
		clipMask >>= rangePartIdx - targetBitIdx;
	}

	/*
	Bitboard tailClipMask = 0b1;

	tailClipMask <<= spansUp ? 
			std::countr_zero(intersect) :
			63 - std::countl_zero(intersect);
	*/

	//Preserve the target piece bit
	Bitboard moveSpacePart = rangePart & ~clipMask /*& ~tailClipMask*/ | targetPiece;

	return moveSpacePart;
}

Bitboard Game::genPawnMoves(Piece const& piece) const {
	Bitboard moveSpace = 0x00;

	//Prevent pawns on one end column of the board
	//from bleeding into the opposite column
	Bitboard constexpr rightClip = 0xFEFEFEFEFEFEFEFE;
	Bitboard constexpr leftClip  = 0X7F7F7F7F7F7F7F7F;

	bool movesUp = piece.getColor() == Color::White;

	/*No need to check if the pawn is at the end of the board,
	since it will always be promoted to a different piece*/

	Bitboard moveTile;

	moveTile = movesUp ? 
		piece.getBBoard() << 8 : piece.getBBoard() >> 8;

	moveSpace |= (moveTile & ~gameBoard.getWholeBoard());

	moveTile = movesUp ? 
		piece.getBBoard() << 16 : piece.getBBoard() >> 16;

	if (!piece.hasMoved && !(moveTile & gameBoard.getWholeBoard()))
		moveSpace |= moveTile;

	moveSpace |= genPawnThreat(piece) & gameBoard.getColorBoard(!piece.getColor());

	return moveSpace;
}

Bitboard Game::genPawnThreat(Piece const& piece) const {
	Bitboard constexpr rightClip = 0xFEFEFEFEFEFEFEFE;
	Bitboard constexpr leftClip  = 0X7F7F7F7F7F7F7F7F;

	bool movesUp = piece.getColor() == Color::White;

	Bitboard threatBB = movesUp ? 
		(piece.getBBoard() << 9)&rightClip : (piece.getBBoard() >> 9)&leftClip;

	threatBB |= movesUp ? 
		piece.getBBoard() << 7 : piece.getBBoard() >> 7;

	return threatBB;
}

//Should I ditch these?!?
Bitboard Game::genKnightMoves(Piece const& piece) const {
	return piece.getMoveRange();
}

Bitboard Game::genKingMoves(Piece const& piece) const  {
	return piece.getMoveRange() | genCastleMoves(piece);
}


void Game::movePiece(Pos start, Pos end) {
	Piece const& piece = gameBoard.getPiece(start);

	if (!(genMoves(gameBoard.getPiece(start)) & end.asBitBoard())) {
		std::cerr << "Error: illegal move" << std::endl;
		return;
	}

	gameBoard.movePiece(start, end);
	if (isCheck(piece.getColor())) {
		std::cerr << "Error: illegal move" << std::endl;
		gameBoard.undoMove();
		return;
	}
}

//Note: this is ONLY FOR USE BY THE KING
Bitboard Game::genCastleMoves(Piece const& piece) const {
	Bitboard castleMask = 0;

	uint8_t const row = piece.getColor() == Color::Black ? 7 : 0;

	//Mask of space between the king and the rooks
	Bitboard const lSpaceMask = (uint64_t) 0x70 << row * 8;
	Bitboard const rSpaceMask = (uint64_t) 0x06 << row * 8;

	Bitboard const lCastleMask = (uint64_t) 0x20 << row * 8;
	Bitboard const rCastleMask = (uint64_t) 0x02 << row * 8;

	auto checkConds = [&](Piece const* piece, PieceType type, Bitboard mask = 0x00) -> bool {
		return piece && piece->getType() == type && 
			!piece->hasMoved && !(gameBoard.getWholeBoard() & mask);
	};

	Piece const* king = &gameBoard.getPiece({4, row});

	if (!checkConds(king, PieceType::King))
		return 0;

	std::pair<Piece const*, Piece const*> rooks = std::make_pair(
			&gameBoard.getPiece({0, row}), 
			&gameBoard.getPiece({7, row})
		);

	if (checkConds(rooks.first, PieceType::Rook, lSpaceMask)) {
		castleMask |= lCastleMask;
	}

	if (checkConds(rooks.second, PieceType::Rook, rSpaceMask)) {
		castleMask |= rCastleMask;
	}

	return castleMask;
}



Bitboard Game::getMovesFromPos(Pos pos) {
	return genMoves(gameBoard.getPiece(pos));
}


bool Game::isCheck(Color color, std::optional<Pos> kingPosHint) {
	Bitboard threatBB = 0;
	Bitboard kingBB = kingPosHint.has_value() ? kingPosHint.value().asBitBoard() : 0;

	for (uint8_t col = 0; col < 8; col++) {
		for (uint8_t row = 0; row < 8; row++) {
			if (gameBoard.squareOccupied({col, row})) {

				Piece const& piece = gameBoard.getPiece({col, row});

				if (!kingBB && piece.getType() == PieceType::King && 
						piece.getColor() == color) { kingBB = piece.getBBoard(); }

				if (piece.getColor() == !color) {
					//Pawns have distinct attack and normal moves
					threatBB |= piece.getType() != PieceType::Pawn ? 
						genMoves(piece) : genPawnThreat(piece);

					if (threatBB & kingBB)
						return true;
				}
			}
		}
	}

	return false;
}

std::string Game::gameOutput() {
	std::ostringstream stream;

	stream << "Will Smith vs Chris Rock:\n\n";
	stream << gameBoard;
	bool blackCheck = isCheck(Color::Black);
	bool whiteCheck = isCheck(Color::White);

	if (blackCheck)
		stream << "Black is in check!" << std::endl;

	if (whiteCheck)
		stream << "White is in check!" << std::endl;

	return stream.str();
}


Game::Game() {
	for (uint8_t col = 0; col < 8; col++) {
		for (uint8_t row = 0; row < 8; row++) {

			if (gameBoard.squareOccupied({col, row})) {
				pieceDatCache.insert({&gameBoard.getPiece({col, row}), {0, 0}});
			}
		}
	}
}