#include <cstdint>
#include <iostream>

#pragma once

//Guess this is it..?
//This is one short class!

/*Not sure if I should've made this
note here or somewhere else, but I
don't know where else to put it:

There's actually no reason to 
pass by reference if compiling for
a 64-bit processor, because the size of
a pointer is 64 bits anyway! Though, I'm
not sure if that's how it works exactly.
*/



//800DB CLOUD!


typedef uint64_t Bitboard;
//STUPID HORSE I JUST FELL OUT OF THE PORSCHE



std::ostream& outBitBoard(std::ostream& os, Bitboard board);
