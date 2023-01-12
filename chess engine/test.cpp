#include "test.h"
#include "BitBoard.h"
#include <iostream>

//something to generate different nodes 

unsigned long long peft(int depth) {
	moveList ml; 
	uint32_t movelist[512]; 

	int numMoves = 0; 


	if (depth == 0) {
		return 1; 
	}

	//generate moves 
	board.generateMove(ml, movelist); 
	
	//loop through moves 
	for (int i = 0; i < ml.index; ++i) {

		//move is legal 
		if (board.makeMove(movelist[i])) {
			
			//need to be a local copy pffft 

		}

		//if move is legal: make that make, and then call peft with one less depth 
		//restore board after that move 
		//shoot restore board might not work LMAO 

	}
	

	//returns number of leaf nodes 
	return numMoves; 
}