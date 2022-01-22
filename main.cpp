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

	return 0;
}