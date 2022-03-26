#include <cstdint>
#include "../Gameboard.hpp"

Pieces::Color operator!(Pieces::Color color) {
	return color == Pieces::Color::Black ? Pieces::Color::White : Pieces::Color::Black;
}

void Piece::genStraightMoveData() {
	Bitboard rangeBoard = 0x00;
	rangeBoard |= genValidRange([](Bitboard b) { return b << 8; }, 7 - pos.row);

	//THE PAGAN WINTER!

	
	return;
}

void Piece::genDiagonalMoveData() { 

	return; 
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
