#include <iostream>
#include "macro.h"
#include "debug.h"

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


	//white pawn 
	if (!side) {
		if (square & NOTFILE_H) {
			attack |= (bitboard << 9);
			printBoard(attack); 
		}
		if (square & NOTFILE_A) {
			attack |= (bitboard << 7);
			printBoard(attack); 
		}
	}

	//black pawn 
	else {
		attack |= (bitboard >> 9); 
		attack |= (bitboard >> 7); 
	}


	return attack;
}
