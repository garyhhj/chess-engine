#include "BitBoard.h"
#include <iostream>

/*
==================
constructor 
==================
*/
BitBoard::BitBoard() { 
	bitBoard = 0x0000000000000000; 
}


/*
==================
debug 
==================
*/
void BitBoard::printBoard() {
	using namespace std;

	//print board 
	for (int rank = 0; rank < 8; ++rank) {
		cout << 8 - rank << "  ";
		for (int file = 0; file < 8; ++file) {
			int square = rank * 8 + file;

			cout << (getBit(bitBoard, square) ? " 1 " : " 0 ");
		}
		cout << '\n';
	}
	cout << '\n';
	cout << "    " << "a  b  c  d  e  f  g  h" << '\n';

	//print board as unsigned decimal 
	cout << "    " << "Bitboard: 0x" << hex << bitBoard << dec << '\n'; 
	cout << endl; 

}

void BitBoard::printBoard(uint64_t bbitBoard) {
	using namespace std;

	//print board 
	for (int rank = 0; rank < 8; ++rank) {
		cout << 8 - rank << "  ";
		for (int file = 0; file < 8; ++file) {
			int square = rank * 8 + file;

			cout << (getBit(bbitBoard, square) ? " 1 " : " 0 ");
		}
		cout << '\n';
	}
	cout << '\n';
	cout << "    " << "a  b  c  d  e  f  g  h" << '\n';

	//print board as unsigned decimal 
	cout << "    " << "Bitboard: 0x" << hex << bbitBoard << dec << '\n';
	cout << endl;

}


/*
==================
attack
==================
*/

//pawn attack table [side][square]

uint64_t pawnAttack[2][64]; 

uint64_t maskPawnAttack(int side, int square) {
	//piece bitboard 
	uint64_t bitboard = 0x0; 

	//result bitboard 
	uint64_t attack = 0x0; 

	//set pieces on board 
	setBit(bitboard, square); 

	BitBoard a; 
	a.printBoard(bitboard); 

	//white pawn 
	if (!side) {
		
	}

	//black pawn 
	else {

	}


	return attack; 
}



