#pragma once
#include <stdint.h>

/*
=====================
pre-calculated tables
=====================
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


//bishop attack table [position index]
//uint64_t bishopAttack[64]; 
extern uint64_t maskBishopAttack(uint64_t square);


//rook attack table [position index] 
//uint64_t rookAttack[64]; 
extern uint64_t maskRookAttack(uint64_t square);
