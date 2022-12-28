#include "BitBoard.h"

#include "precalculation.h"
#include "macro.h"
#include "debug.h"

#include <iostream>
#include <vector>


/*
==================
main driver
==================
*/

using namespace std; 

int main() {
	BitBoard board; 
	
	//initializing occupancy table 
	initBishopOccupancy(); 
	
	
	//initialize magic attack table for rook 
	for (int i = 0; i < 64; ++i) {
		maskRookAttack(i); 
	}
	
	

	//testing 
	uint64_t occupancy = generateRandomUint64() & maskRookOccupancy(a3);

	int magicIndex = (occupancy * rookMagicNum[36]) >> (64 - numBit(maskRookOccupancy(e4)));
	uint64_t atk = rookAttack[36][magicIndex]; 

	printBoard(occupancy); 
	printBoard(atk); 
}


/*
"a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8",
"a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7",
"a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6",
"a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5",
"a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4",
"a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3",
"a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2",
"a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1",
*/