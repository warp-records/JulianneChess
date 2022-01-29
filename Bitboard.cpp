
#include "Bitboard.hpp"
#include <sstream>

//HAND CRUSHED BY A MALLET!

//Just fix this later
std::ostream& outBitBoard(std::ostream& os, Bitboard board) {

	for (int i = 7; i >= 0; i--) {
		os << (char) ('A' + i) << "   ";
		
		for (int j = 7; j >= 0; j--) {
			os << (board >> (8*i + j) & 0b1) << ' ';
		}

		os << std::endl;
	}

	os << "\n    ";

	for (int i = 0; i < 8; i++) {
		os << i << ' ';
	}

	os << '\n' << std::endl;

	return os;
}
