#include "test.h"
#include "BitBoard.h"
#include <iostream>

//something to generate different nodes 


//initialize chess board 
extern BitBoard board;

unsigned long long perft(int depth) {
	moveList ml; 
	uint32_t movelist[512]; 
	boardState state; 

	int numNodes = 0; 


	if (depth == 0) {
		return 1; 
	}

	//generate moves 
	board.generateMove(ml, movelist); 
	
	//loop through moves 
	for (int i = 0; i < ml.index; ++i) {

		//move is legal 
		if (board.makeMove(movelist[i])) {
			board.storeState(state); 
			numNodes += perft(depth - 1); 
			board.restoreState(state); 
		}
	}
	

	//returns number of leaf nodes 
	return numNodes; 
}