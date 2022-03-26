#include <cstdint>
#include "../Gameboard.hpp"

Pieces::Color operator!(Pieces::Color color) {
	return color == Pieces::Color::Black ? Pieces::Color::White : Pieces::Color::Black;
}

void Piece::genStraightMoveData() {
	Bitboard rangeBoard = 0x00;
	//Up
	rangeBoard |= genValidRange([](Bitboard b) { return b << 8; }, 7 - pos.row);
	//Down
	rangeBoard |= genValidRange([](Bitboard b) { return b >> 8; }, pos.row);
	//Right
	rangeBoard |= genValidRange([](Bitboard b) { return b >> 1; }, 7 - pos.column);
	//Left
	rangeBoard |= genValidRange([](Bitboard b) { return b << 1; }, pos.column);

	cache.moveRange |= rangeBoard;
	//THE PAGAN WINTER!
}

void Piece::genDiagonalMoveData() { 

	Bitboard rangeBoard = 0x00;
	//Up right
	rangeBoard |= genValidRange([](Bitboard b) { return b << 7; }, std::min(7 - pos.column, 7 - pos.row));
	//Up left
	rangeBoard |= genValidRange([](Bitboard b) { return b << 9; }, std::min(pos.column, 7 - pos.row));
	//Down right
	rangeBoard |= genValidRange([](Bitboard b) { return b >> 9; }, std::min(7 - pos.column, pos.row));
	//Down left
	rangeBoard |= genValidRange([](Bitboard b) { return b >> 7; }, std::min(pos.column, pos.row));

	cache.moveRange |= rangeBoard;
}

//Shift function: function for shifting tilemask
template <typename Funct> Bitboard Piece::genValidRange(Funct shiftFunct, int iter) {
	Bitboard rangeBoard = 0x00;
	Bitboard tileMask = shiftFunct(getBBoard());

	//While tile mask is in range

	for (int i = 0; i < iter; i++) {
		rangeBoard |= tileMask;

		//Same team piece is on this space
		if (tileMask & gameBoard->getTeamBitBoard(color)) {
			rangeBoard ^= tileMask;

			break;
		} else if (tileMask & gameBoard->getTeamBitBoard(!color)) {
			cache.attackList[cache.listLen] = { pos.column, pos.row };
			cache.listLen++;
			
			break;
		}

		tileMask = shiftFunct(tileMask);
	};

	return rangeBoard;
}
