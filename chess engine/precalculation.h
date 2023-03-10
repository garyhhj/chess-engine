#pragma once
#include <stdint.h>

/*
=====================
pre-calculated tables
=====================
*/

/*
==================
initialization
==================
*/
//initialization 
extern void initLeaperPiece(); 
extern void initSliderPieces();


/*
==================
leaper pieces 
==================
*/
//pawn attack table [sides][position index]
extern uint64_t pawnAttack[2][64];
extern uint64_t maskPawnAttack(int side, uint64_t square);
extern void initPawnAttack(); 


//knight attack table [position index] 
extern uint64_t knightAttack[64];
extern uint64_t maskKnightAttack(uint64_t square);
extern void initKnightAttack(); 


//king attack table [position index] 
extern uint64_t kingAttack[64];
extern uint64_t maskKingAttack(uint64_t square);
extern void initKingAttack();

/*
==================
slider pieces 
==================
*/
//bishop attack table [position index][magic index]
extern uint64_t bishopAttack[64][512];
//bishop occupancy table [position index]
extern uint64_t bishopOccupancy[64];
//bishop occupancy bit count for bishop at position index [position index] 
extern const int bishopOccupancyCount[64];
//rook magic number table [position index] 
extern uint64_t bishopMagicNum[64];

extern uint64_t maskBishopAttack(int index, uint64_t occupancy);
extern void initBishopAttackIndex(int index); 
extern uint64_t maskBishopOccupancy(uint64_t square);
extern void initBishopOccupancy();
extern uint64_t maskBishopAttackRT(uint64_t square, uint64_t block);
extern uint64_t verifyMagicNumBishop(int index);
extern void initBishopAttack();





//rook attack table [position index][magic index]
extern uint64_t rookAttack[64][4096];
//rook occupancy table [position index] 
extern uint64_t rookOccupancy[64];
//rook occupancy bit count for rook at position index [position index] 
extern const int rookOccupancyCount[64];
//rook magic number table [position index] 
extern uint64_t rookMagicNum[64];

extern uint64_t maskRookAttack(int index, uint64_t occupancy);
extern void initRookAttackIndex(int index);
extern uint64_t maskRookOccupancy(uint64_t square);
extern void initRookOccupancy();
extern uint64_t maskRookAttackRT(uint64_t square, uint64_t block);
extern uint64_t verifyMagicNumRook(int index);
extern void initRookAttack();


extern uint64_t maskQueenAttack(int index, uint64_t occupancy);




/*
=====================
magic numbers 
=====================
*/
//generate magic number 
extern uint64_t occupancyCombination(int index, int numBits, uint64_t occupancy);

extern uint32_t state;
extern uint32_t generateRandomUint32();
extern uint64_t generateRandomUint64();
extern uint64_t generateMagicNumCandidate();
