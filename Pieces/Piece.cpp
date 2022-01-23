#include <cstdint>

#include "Piece.hpp"

/*Pos Piece::getPos(Bitboard piece) {
		//Maybe be memory conservative
		//for deep move generation
		//Start one out of bounds because of pre-increment and pre-decrement
		uint8_t row = 0, column = 7;

		//Note: the calculatd row and column are endian dependent
		//Consider calculating beforehand

		//Using a binary search would result in
		//a quicker search.
		for (size_t mask = 0xFF; piece & mask == 0x00; mask <<= 8) {
			row++;
		}

		for (uint8_t mask = 0x01 << row; piece & mask == 0x00; mask <<= 1) {
			column--;
		}

		return { row, column };
}*/

Pos Piece::getPos(Bitboard piece) {
		/*Maybe be memory conservative
		for deep move generation*/
		//Start one out of bounds because of pre-increment and pre-decrement
		uint8_t row = 0, column = 7;

		//Note: the calculatd row and column are endian dependent
		//Consider calculating beforehand

		/*Using a binary search would result in
		a quicker search.*/
		uint64_t n = 0b1;

		int i = 0;
		for (; n != piece; i++, n<<=1);

		return { 7 - (i / 8), i % 8 };
}