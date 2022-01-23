#include <iostream>
#include "Pieces.hpp"

int main() {
	std::string const version = "0.0.1";

	std::cout << "JulianneChess\n\n" <<
	"Version: " << version << "\n\n";

	std::cout << 
	"   |\\_" <<   "      -----------------\n" <<
  	"  /  .\\_" << "   <  Horsey go MOOO!  >\n" <<
 	" |   ___)" << "  / -----------------\n" <<
 	" |    \\\n" <<
 	" |  =  |\n" <<
 	" /_____\\\n" <<
	"[_______]" << std::endl;


	Pieces::Knight testPiece;	
	uint64_t pos = 0b0000000000100000000000000000000000000000000000000000000000000000;
	
	/*  

	0 1 2 3 4 5 6 7

7	0 0 0 0 0 0 0 0
6	0 0 1 0 0 0 0 0 
5	0 0 0 0 0 0 0 0 
4	0 0 0 0 0 0 0 0 
3	0 0 0 0 0 0 0 0 
2	0 0 0 0 0 0 0 0 
1	0 0 0 0 0 0 0 0 
0	0 0 0 0 0 0 0 0  


	0b0000000000100000000000000000000000000000000000000000000000000000

	0b0000000000000000000000000000000000001000000000000000000000000000

	*/

	Pos p = testPiece.getPos(pos);
	std::cout << (int) p.column << '\n' << (int) p.row << std::endl;

	return 0;
}