#include "BitBoard.h"

#include "precalculation.h"
#include "macro.h"
#include "debug.h"

#include <iostream>
#include <vector>
#include <string>


/*
==================
main driver
==================
*/

using namespace std; 

int main() {
	BitBoard board; 
	
	//initializing occupancy table

	//for (int i = 0; i < 64; ++i) {
		//auto meow = verifyMagicNumBishop(i); 
		//cout << "0x" << hex << meow << ", " << endl; 
	//}

	//initalize bishop attacks 
	for (int i = 0; i < 64; ++i) {
		maskBishopAttack(i); 
	}

	
	//for (int i = 0; i < 64; ++i) {
	//	maskRookAttack(i); 
	//}


	//test the function :) 
	
	//generate some random occupancy 
	for (int i = 0; i < 64; ++i) {
		auto occ = maskBishopOccupancy(position[i]); 
		int numBits = numBit(occ); 
		occ &= generateRandomUint64(); 
		
		cout << "PRINTING I: " << i << endl; 
		printBoard(occ); 

		int magicIndex = (occ * bishopMagicNum[i]) >> (64 - numBits);
		printBoard(bishopAttack[i][magicIndex]); 
	}
	//print occupancy 

	//print the board gotten from the magic index 
	
	

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