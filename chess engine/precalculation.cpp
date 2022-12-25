#include <iostream>
#include "macro.h"
#include "debug.h"

/*
==================
attack
==================
*/


/*
==================
pawn 
==================
*/


//pawn attack table [sides][position index]
uint64_t pawnAttack[2][64];

uint64_t maskPawnAttack(int side, uint64_t square) {
	//piece bitboard 
	uint64_t bitboard = 0x0;

	//result bitboard 
	uint64_t attack = 0x0;

	//set pieces on board 
	setBit(bitboard, square);

	//white pawn 
	if (!side) {
		if (bitboard & NOTFILE_A) attack |= (bitboard << 9); 
		if (bitboard & NOTFILE_H) attack |= (bitboard << 7); 
	}

	//black pawn 
	else {
		if (bitboard & NOTFILE_A) attack |= (bitboard >> 7);
		if (bitboard & NOTFILE_H) attack |= (bitboard >> 9); 
	}

	return attack;
}

void initPawnAttack() {
	for (int i = 0; i < 64; ++i) {
		pawnAttack[white][i] = maskPawnAttack(white, position[i]); 
		pawnAttack[black][i] = maskPawnAttack(black, position[i]); 
	}
}


/*
==================
knight 
==================
*/


//knight attack table [position index] 
uint64_t knightAttack[64];

uint64_t maskKnightAttack(uint64_t square) {
	//piece bitboard 
	uint64_t bitboard = 0x0;

	//result bitboard 
	uint64_t attack = 0x0;

	//set pieces on board 
	setBit(bitboard, square);

	//upwards and downwards L 
	if (bitboard & NOTFILE_A) attack |= (bitboard << 17);
	if (bitboard & NOTFILE_H) attack |= (bitboard << 15);

	if (bitboard & NOTFILE_A) attack |= (bitboard >> 15);
	if (bitboard & NOTFILE_H) attack |= (bitboard >> 17);

	//sideways L 
	if (bitboard & NOTFILE_AB) attack |= (bitboard << 10);
	if (bitboard & NOTFILE_AB) attack |= (bitboard >> 6);

	if (bitboard & NOTFILE_GH) attack |= (bitboard << 6);
	if (bitboard & NOTFILE_GH) attack |= (bitboard >> 10); 


	return attack;
}

void initKnightAttack() {
	for (int i = 0; i < 64; ++i) {
		knightAttack[i] = maskKnightAttack(position[i]); 
	}
}


/*
==================
king
==================
*/

//king attack table [position index] 
uint64_t kingAttack[64];

uint64_t maskKingAttack(uint64_t square) {
	//piece bitboard 
	uint64_t bitboard = 0x0;

	//result bitboard 
	uint64_t attack = 0x0;

	//set pieces on board 
	setBit(bitboard, square);

	//up and down
	attack |= (bitboard << 8);
	attack |= (bitboard >> 8); 

	//left and right 
	if (bitboard & NOTFILE_A) attack |= (bitboard << 1); 
	if (bitboard & NOTFILE_H) attack |= (bitboard >> 1); 

	return attack;
}

void initKingAttack() {
	for (int i = 0; i < 64; ++i) {
		kingAttack[i] = maskKingAttack(position[i]); 
	}
}


/*
==================
bishop
==================
*/

//bishop occupancy table [position index] 
uint64_t bishopOccupancy[64]; 

uint64_t maskBishopOccupancy(uint64_t square) {
	//piece bitboard 
	uint64_t bitboard = 0x0;

	//result bitboard 
	uint64_t attack = 0x0;

	//set pieces on board 
	setBit(bitboard, square);

	//bottom left to top right diagonal 
	for (int i = 1; bitboard << 7 * i & NOTFILE_AH_NOTRANK_12; ++i) attack |= bitboard << 7 * i; 
	for (int i = 1; bitboard >> 7 * i & NOTFILE_AH_NOTRANK_12; ++i) attack |= bitboard >> 7 * i; 

	//bottom right to top left diagonal 
	for (int i = 1; bitboard << 9 * i & NOTFILE_AH_NOTRANK_12; ++i) attack |= bitboard << 9 * i; 
	for (int i = 1; bitboard >> 9 * i & NOTFILE_AH_NOTRANK_12; ++i) attack |= bitboard >> 9 * i; 

	return attack;
}

void initBishopOccupancy() {
	for (int i = 0; i < 64; ++i) {
		bishopOccupancy[i] = maskBishopOccupancy(position[i]); 
	}
}

uint64_t maskBishopAttackRT(uint64_t square, uint64_t block) {
	//piece bitboard 
	uint64_t bitboard = 0x0;

	//result bitboard 
	uint64_t attack = 0x0;

	//set pieces on board 
	setBit(bitboard, square);

	//bottom left to top right diagonal 
	for (int i = 1; bitboard << 7 * i & NOTFILE_A; ++i) {
		attack |= bitboard << 7 * i;
		if (bitboard << 7 * i & block) break; 
	}

	for (int i = 1; bitboard >> 7 * i & NOTFILE_H; ++i) {
		attack |= bitboard >> 7 * i;
		if (bitboard >> 7 * i & block) break; 
	}


	//bottom right to top left diagonal 
	for (int i = 1; bitboard << 9 * i & NOTFILE_H; ++i) {
		attack |= bitboard << 9 * i;
		if (bitboard << 9 * i & block) break; 
	}

	for (int i = 1; bitboard >> 9 * i & NOTFILE_A; ++i) {
		attack |= bitboard >> 9 * i;
		if (bitboard >> 9 * i & block) break; 
	}


	return attack; 
}


/*
==================
rook
==================
*/

//rook occupancy table [position index] 
uint64_t rookOccupancy[64]; 

uint64_t maskRookOccupancy(uint64_t square) {
	//piece bitboard 
	uint64_t bitboard = 0x0;

	//result bitboard 
	uint64_t attack = 0x0;

	//set pieces on board 
	setBit(bitboard, square);

	//up and down
	for (int i = 1; bitboard << 8 * i & NOTRANK_8; ++i) attack |= bitboard << 8 * i; 
	for (int i = 1; bitboard >> 8 * i & NOTRANK_1; ++i) attack |= bitboard >> 8 * i; 

	//left and right 
	for (int i = 1; bitboard << 1 * i & NOTFILE_A && bitboard << 1 * i & NOTFILE_H; ++i) attack |= bitboard << 1 * i;
	for (int i = 1; bitboard >> 1 * i & NOTFILE_H && bitboard >> 1 * i & NOTFILE_A; ++i) attack |= bitboard >> 1 * i; 


	return attack; 
}

void initRookOccupancy() {
	for (int i = 0; i < 64; ++i) {
		rookOccupancy[i] = maskRookOccupancy(position[i]); 
	}
}

