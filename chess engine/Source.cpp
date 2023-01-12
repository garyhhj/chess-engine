#include "BitBoard.h"

#include "precalculation.h"
#include "macro.h"
#include "debug.h"
#include "time.h"

#include <iostream>
#include <vector>
#include <string>

#include <chrono>


/*
==================
main driver
==================
*/

using namespace std; 

int main() {
	BitBoard board; 
	
	
	initSliderPieces(); 
	initLeaperPiece(); 

	//set some attacking pieces 
	string fen1 = "8/p7/8/8/8/8/8/8 b - - ";
	string fenStart = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b KQkq - 0 1 ";
	string fenTricky = "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1 ";
	string fenK = "rnbqkb1r/pp1p1pPp/8/2p1pP2/1P1P4/3P3P/P1P1P3/RNBQKBNR w KQkq e6 0 1";
	string fenCmk = "r2q1rk1/ppp2ppp/2n1bn2/2b1p3/3pP3/3P1NPP/PPP1NPB1/R1BQ1RK1 b - - 0 9 ";
	string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RN2K2R b KQkq - 0 1 ";


	auto startTimer = std::chrono::high_resolution_clock::now(); 

	//create move list 
	moveList ml; 
	uint32_t movelist[512]; 
	
	//load board states 
	board.parseFen(fenStart); 
	board.printBoard(); 

	
	board.generateMove(ml, movelist); 
	board.printMoveList(ml, movelist); 

	/*
	cout << endl << endl; 
	cout << "before the while loop" << endl; 
	cout << endl << endl; 

	int i = 0; 
	while (i != board.moveListEnd) {
		board.storeState(); 
		board.printBoard(); 

		board.makeMove(board.moveList[i]); 
		board.printBoard(); 
		
		std::string s; 
		std::getline(cin, s); 
		++i; 

		board.restoreState(); 
	}
	*/


	auto endTimer = std::chrono::high_resolution_clock::now(); 
	std::cout << "Milliseconds: " << std::chrono::duration_cast<std::chrono::milliseconds>(endTimer - startTimer).count() << std::endl;
}



/*
//sides (colors)
enum : int {
	white,
	black,
	both,
};

//pieces 
enum : int {
	//white 
	wPawn,
	wKnight,//(n)  
	wBishop,
	wRook,
	wQueen,
	wKing,

	//black 
	bPawn,
	bKnight,//(N) 
	bBishop,
	bRook,
	bQueen,
	bKing,
};
*/



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