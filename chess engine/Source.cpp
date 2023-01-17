#include "BitBoard.h"
#include "precalculation.h"
#include "macro.h"
#include "debug.h"
#include "time.h"
#include "test.h"

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

BitBoard board;

int main() {
	
	
	
	initSliderPieces(); 
	initLeaperPiece(); 

	//set some attacking pieces 
	string fen1 = "8/p7/8/8/8/8/8/8 b - - ";
	string fenStart = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1 ";
	string fenTricky = "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1 ";
	string fenK = "rnbqkb1r/pp1p1pPp/8/2p1pP2/1P1P4/3P3P/P1P1P3/RNBQKBNR w KQkq e6 0 1";
	string fenCmk = "r2q1rk1/ppp2ppp/2n1bn2/2b1p3/3pP3/3P1NPP/PPP1NPB1/R1BQ1RK1 b - - 0 9 ";
	string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RN2K2R b KQkq - 0 1 ";


	string fenEnpassant = "8/8/8/5p2/8/8/8/8 b w - f6 ";


	
	//load board states 
	board.parseFen(fenTricky); 
	board.printBoard(); 

	
	/*
	//move list 
	moveList ml; 
	uint32_t movelist[512]; 
	board.generateMove(ml, movelist); 
	board.printMoveList(ml, movelist); 

	//make move 
	cout << "making move: "; 
	int index = 0; 
	board.printMove(movelist[index]); 
	board.
	(movelist[index]);
	board.printBoard(); 
	
	
	//new move list 
	moveList ml1; 
	uint32_t movelist1[512]; 
	board.generateMove(ml1, movelist1); 
	board.printMoveList(ml1, movelist1); 
	*/

	
	moveList ml; 
	uint32_t movelist[512]; 
	board.generateMove(ml, movelist); 
	//board.printMoveList(ml, movelist); 
	board.makeMove(movelist[36]); 
	board.printBoard(); 
	
	
	
	moveList ml1; 
	uint32_t movelist1[512]; 
	board.generateMove(ml1, movelist1); 
	//board.printMoveList(ml1, movelist1); 
	board.makeMove(movelist1[42]); 
	board.printBoard(); 
	cout << endl << endl; 
	//*/

	moveList ml2;
	uint32_t movelist2[512]; 
	board.generateMove(ml2, movelist2); 
	board.printMoveList(ml2, movelist2); 

	board.makeMove(movelist2[0]); //d5d6
	board.printBoard(); 


	cout << perftTest(1) << '\n'; 
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