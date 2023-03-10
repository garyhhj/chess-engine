#include "test.h"
#include "BitBoard.h"
#include "macro.h"
#include <iostream>
#include <chrono>

//something to generate different nodes 


//initialize chess board 
extern BitBoard board;

unsigned long long perftTest(int depth) {
	auto startTime = std::chrono::high_resolution_clock::now(); 
	
	moveList ml; 
	uint32_t movelist[512]; 
	boardState state;
	board.storeState(state);

	unsigned long long numNodes = 0; 

	board.generateMove(ml, movelist); 

	for (int i = 0; i < ml.index; ++i) {

		//if move is illegal 
		if (!board.makeMove(movelist[i])) {
			board.restoreState(state);
			continue;
		}
		board.restoreState(state);
		//store state 

		//call perft 
		board.makeMove(movelist[i]);
		//board.printBoard(); 
		unsigned long long currNodes = perft(depth - 1);
		numNodes += currNodes;

		//print result 
		std::cout << positionStr[board.decodeMoveSourceIndex(movelist[i])] << " " << positionStr[board.decodeMoveTargetIndex(movelist[i])];
		if (board.decodeMovePromotePiece(movelist[i]) != noPiece) {
			//print piece 
			int piece = board.decodeMovePromotePiece(movelist[i]);
			if (piece == bKnight || piece == wKnight) std::cout << "n";
			else if (piece == bBishop || piece == bBishop) std::cout << "b";
			else if (piece == bRook || piece == wRook) std::cout << "r";
			else if (piece == bQueen || piece == bQueen) std::cout << "q"; 
		}
		std::cout << " | " << currNodes << '\n';

		board.restoreState(state); 
	}

	auto endTime = std::chrono::high_resolution_clock::now(); 
	std::cout << "time taken: " << std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count() << "milliseconds" << '\n';
	
	return numNodes; 
}

unsigned long long perft(int depth) {
	moveList ml; 
	uint32_t movelist[512]; 
	boardState state; 
	board.storeState(state); 

	unsigned long long numNodes = 0; 


	if (depth == 0) {
		return 1; 
	}

	//generate moves 
	board.generateMove(ml, movelist); 
	
	//loop through moves 
	for (int i = 0; i < ml.index; ++i) {
		
		//illegal state 
		if (!board.makeMove(movelist[i])) {
			board.restoreState(state); 
			continue; 
		}
		board.restoreState(state); 

		board.makeMove(movelist[i]); 
		numNodes += perft(depth - 1); 
		board.restoreState(state); 
	}
	

	//returns number of leaf nodes 
	return numNodes; 
}