#include <iostream>
#include <stdint.h>
#include "debug.h"
#include "macro.h"


/*
==================
	  debug
==================
*/


void printBoards(uint64_t bitBoard) {
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
