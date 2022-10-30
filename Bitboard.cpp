
#include "Bitboard.hpp"
#include <sstream>

//HAND CRUSHED BY A MALLET!

//Just fix this later lol
//I know, the interface is kinda dumb
std::ostream& outBitBoard(std::ostream& os, Bitboard board, bool debugBoard) {

	for (int i = 7; i >= 0; i--) {
		os << (debugBoard ? i : i+1) << "   ";
		
		for (int j = 7; j >= 0; j--) {
			os << (board >> (8*i + j) & 0b1) << ' ';
		}

		os << std::endl;
	}

	os << "\n    ";

	for (int i = 0; i <= 7; i++) {
		os << (char) (debugBoard ? '0'+i : ('A'+i)) << ' ';
	}

	os << '\n' << std::endl;

	return os;
}