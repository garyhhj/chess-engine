#include <iostream>
#include <algorithm>
#include "macro.h"
#include "debug.h"
#include "precalculation.h"

/*
==================
attack
==================
*/


/*
==================
initialization 
==================
*/

//leaper pieces 
void initLeaperPiece() {
	initPawnAttack(); 
	initKnightAttack(); 
	initKingAttack(); 
}

//slider pieces 
void initSliderPieces() {
	//bishop 
	initBishopOccupancy();
	initBishopAttack();

	//rook 
	initRookOccupancy(); 
	initRookAttack();
}


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

	//upper corners 
	if (bitboard & NOTFILE_A) attack |= (bitboard << 9);
	if (bitboard & NOTFILE_H) attack |= (bitboard << 7); 

	//lower corners 
	if (bitboard & NOTFILE_A) attack |= (bitboard >> 7);
	if (bitboard & NOTFILE_H) attack |= (bitboard >> 9); 

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

//bishop attack table [position index][magic index]
uint64_t bishopAttack[64][512];

//bishop occupancy table [position index] 
uint64_t bishopOccupancy[64]; 
uint64_t bishopMagicNum[64] = {
	0x40040822862081,
	0xa168041010224880,
	0x400102020020885,
	0x212001220042403,
	0x20900041108c,
	0x400000049082100,
	0x111110105100308,
	0x22010108410402,
	0x200c100228c10a80,
	0x91020885040090,
	0x80000c88900d0000,
	0x2003002020400,
	0x800e100284140002,
	0x6311401040228,
	0x2040440209102440,
	0x1102923002200165,
	0x1011020082020910,
	0x8002080827804118,
	0x44008082022100,
	0x400812000041,
	0x2000040c1811e404,
	0x80a2940208000101,
	0x2401008250002000,
	0x34042a40048840,
	0x1040028010500,
	0x40100204c8121100,
	0x881010200040a02,
	0x40008020020260,
	0x8008a080a1680200,
	0x2010242100081,
	0x8582400080500,
	0xc224202004040400,
	0x1824009005220100,
	0x4004084641011041,
	0x88004002011580,
	0x840080802000,
	0x42011000802400c,
	0x1204100009104080,
	0x1010010a020641,
	0x20210124084600,
	0xc01100020103c208,
	0x2133000411821020,
	0x10200202102200,
	0x8021004820180000,
	0x4009204404008019,
	0x4018102100c40080,
	0x340c6001040104,
	0x9009020010c00,
	0x2440908401081209,
	0x48089808088404,
	0x1220110080465,
	0x408020210580380,
	0x45c00800200,
	0x1080801002004,
	0x8002102c11004201,
	0x81301010030940,
	0x8c02008200901400,
	0x2081a23101154,
	0xa410900420520809,
	0x4004242000030048,
	0x204241a80000420,
	0x211802044e048220,
	0x310340810882000,
	0x221204040c004600,
};


//bishop occupancy bit count for bishop at position index [position index] 
const int bishopOccupancyCount[64] = {
	6, 5, 5, 5, 5, 5, 5, 6,
	5, 5, 5, 5, 5, 5, 5, 5,
	5, 5, 7, 7, 7, 7, 5, 5,
	5, 5, 7, 9, 9, 7, 5, 5,
	5, 5, 7, 9, 9, 7, 5, 5,
	5, 5, 7, 7, 7, 7, 5, 5,
	5, 5, 5, 5, 5, 5, 5, 5,
	6, 5, 5, 5, 5, 5, 5, 6,
};

uint64_t maskBishopAttack(int index, uint64_t occupancy) {
	uint64_t relOccupancy = maskBishopOccupancy(position[index]) & occupancy;
	int magicIndex = (relOccupancy * bishopMagicNum[index]) >> (64 - bishopOccupancyCount[index]);
	return bishopAttack[index][magicIndex]; 
}

//generate maskBishopAttack for bishopAttack table with magic index 
void initBishopAttackIndex(int index) {
	//initilaize bitboard 
	uint64_t bitboard = position[index];

	uint64_t allRelOccupancy = maskBishopOccupancy(bitboard);

	int numberOfBits = numBit(allRelOccupancy);
	int numberOfBitsP2 = (1 << numberOfBits);

	//generate all bishop attacks occupancy
	uint64_t possibleAtk[4096];
	uint64_t possibleOccupancy[4096];
	for (int i = 0; i < numberOfBitsP2; ++i) {
		possibleOccupancy[i] = occupancyCombination(i, numberOfBits, allRelOccupancy);
		possibleAtk[i] = maskBishopAttackRT(bitboard, possibleOccupancy[i]);
	}
	
	//populate bishop attack table 
	for (int i = 0; i < numberOfBitsP2; ++i) {
		int magicIndex = (possibleOccupancy[i] * bishopMagicNum[index]) >> (64 - numberOfBits);
		bishopAttack[index][magicIndex] = possibleAtk[i]; 
	}
}

void initBishopAttack() {
	for (int i = 0; i < 64; ++i) {
		initBishopAttackIndex(i); 
	}
}


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


uint64_t verifyMagicNumBishop(int index) {
	//initilaize bitboard 
	uint64_t bitboard = position[index];

	uint64_t allRelOccupancy = maskBishopOccupancy(bitboard);

	int numberOfBits = numBit(allRelOccupancy);
	int numberOfBitsP2 = (1 << numberOfBits);

	//generate all bishop attacks occupancy
	uint64_t possibleAtk[4096];
	uint64_t possibleOccupancy[4096];
	for (int i = 0; i < numberOfBitsP2; ++i) {
		possibleOccupancy[i] = occupancyCombination(i, numberOfBits, allRelOccupancy);
		possibleAtk[i] = maskBishopAttackRT(bitboard, possibleOccupancy[i]);

		using namespace std;
		//cout << "PRINTING I : " << i << endl; 
		//printBoard(possibleOccupancy[i]); 
		//printBoard(possibleAtk[i]); 
	}

	//generate and try magic number
	for (int trial = 0; trial < 100000000; ++trial) {
		uint64_t magicNum = generateMagicNumCandidate();

		//array to keep track of collisions 
		uint64_t visited[4096];
		std::fill_n(visited, 4096, 0);

		//fail flag
		bool fail = false;
		for (int i = 0; i < numberOfBitsP2; ++i) {
			int magicIndex = (possibleOccupancy[i] * magicNum) >> (64 - numberOfBits);

			if (visited[magicIndex] == 0) {
				visited[magicIndex] = possibleAtk[i];
			}
			else if (visited[magicIndex] != possibleAtk[i]) {
				fail = true;
				break;
			}

		}

		if (fail) {
			continue;
		}
		else {
			return magicNum;
		}
	}

	//return 0 for fail ; 
	return 0;
}

/*
==================
rook
==================
*/

//rook attack table [position index][magic index]
uint64_t rookAttack[64][4096];

//rook occupancy table [position index] 
uint64_t rookOccupancy[64]; 
uint64_t rookMagicNum[64] = {
	0x1010549228402,
	0x2000011002080084,
	0x11004802040005,
	0x406002014300842,
	0x104a00080440a012,
	0x2001200095004009,
	0x882004883210112,
	0x100c020800417,
	0x41048c0200,
	0x4106002144080600,
	0x800a800a00040080,
	0x426000420109a00,
	0x8000680310008080,
	0x822008060401600,
	0x406400088200080,
	0x202208001104100,
	0x501224008e460001,
	0x4802010802640010,
	0x400102040080104,
	0x2011001008030004,
	0x1001009000090020,
	0x201e420080320020,
	0x9869008040010020,
	0x810308040028008,
	0x220081020001c4,
	0x2000101704000a08,
	0x216000802009004,
	0x28820400800800,
	0x2012002046001008,
	0x60450231002000,
	0x405024001002080,
	0x800400030800084,
	0x5060010824c,
	0x242100010012003c,
	0x4800c0080120080,
	0x9004040080080081,
	0x1200b00100100,
	0x800910100402000,
	0x24a00040100040,
	0x8500802080024000,
	0x202020004004087,
	0x440021702248,
	0x540080800c000200,
	0x2088008004028088,
	0x808008001002,
	0x828020053000,
	0x802000c0100222c0,
	0x281808004c00020,
	0x8006000225009044,
	0x9005001402000100,
	0x40800600440080,
	0x24808084000800,
	0x200801002802800,
	0xa2002056008042,
	0x1003040008101,
	0x401002080010240,
	0x280104063000480,
	0x9000c0200058300,
	0x400881020040012,
	0x4580080007801400,
	0xc800c0800100082,
	0x80200080900088,
	0x840002000405008,
	0x80014000802034,
};


//rook occupancy bit count for bishop at position index [position index] 
const int rookOccupancyCount[64] = {
	12, 11, 11, 11, 11, 11, 11, 12,
	11, 10, 10, 10, 10, 10, 10, 11,
	11, 10, 10, 10, 10, 10, 10, 11,
	11, 10, 10, 10, 10, 10, 10, 11,
	11, 10, 10, 10, 10, 10, 10, 11,
	11, 10, 10, 10, 10, 10, 10, 11,
	11, 10, 10, 10, 10, 10, 10, 11,
	12, 11, 11, 11, 11, 11, 11, 12,
};

uint64_t maskRookAttack(int index, uint64_t occupancy) {
	uint64_t relOccupancy = maskRookOccupancy(position[index]) & occupancy;
	int magicIndex = (relOccupancy * rookMagicNum[index]) >> (64 - rookOccupancyCount[index]);
	return rookAttack[index][magicIndex];
}

//generate maskRookAttack for rookAttack table with magic index 
void initRookAttackIndex(int index) {
	//initilaize bitboard 
	uint64_t bitboard = position[index];

	uint64_t allRelOccupancy = maskRookOccupancy(bitboard);

	int numberOfBits = numBit(allRelOccupancy);
	int numberOfBitsP2 = (1 << numberOfBits);

	//generate all rook attacks occupancy
	uint64_t possibleAtk[4096];
	uint64_t possibleOccupancy[4096];
	for (int i = 0; i < numberOfBitsP2; ++i) {
		possibleOccupancy[i] = occupancyCombination(i, numberOfBits, allRelOccupancy);
		possibleAtk[i] = maskRookAttackRT(bitboard, possibleOccupancy[i]); 
	}

	//populate attack table 
	for (int i = 0; i < numberOfBitsP2; ++i) {
		int magicIndex = (possibleOccupancy[i] * rookMagicNum[index]) >> (64 - numberOfBits); 

		rookAttack[index][magicIndex] = possibleAtk[i]; 
	}
}

void initRookAttack() {
	for (int i = 0; i < 64; ++i) {
		initRookAttackIndex(i);
	}
}

//returns occupancy for rook 
uint64_t maskRookOccupancy(uint64_t square) {
	//piece bitboard 
	uint64_t bitboard = 0x0;

	//result bitboard 
	uint64_t occupancy = 0x0;

	//set pieces on board 
	setBit(bitboard, square);

	//up and down 
	for(int i = 1; bitboard << 8 * i & NOTRANK_8; ++i) occupancy |= bitboard << 8 * i;
	for (int i = 1; bitboard >> 8 * i & NOTRANK_1; ++i) occupancy |= bitboard >> 8 * i; 
	
	//left anf right 
	for (int i = 1; bitboard << 1 * i & NOTFILE_A && bitboard << 1 * i & NOTFILE_H; ++i) occupancy |= bitboard << 1 * i; 
	for (int i = 1; bitboard >> 1 * i & NOTFILE_H && bitboard >> 1 * i & NOTFILE_A; ++i) occupancy |= bitboard >> 1 * i; 

	return occupancy; 
}

void initRookOccupancy() {
	for (int i = 0; i < 64; ++i) {
		rookOccupancy[i] = maskRookOccupancy(position[i]); 
	}
}

uint64_t maskRookAttackRT(uint64_t square, uint64_t block) {
	//piece bitboard 
	uint64_t bitboard = 0x0;

	//result bitboard 
	uint64_t attack = 0x0;

	//set pieces on board 
	setBit(bitboard, square);


	//up and down 
	for (int i = 1; 8 * i != 64 && bitboard << 8 * i; ++i) {
		attack |= bitboard << 8 * i; 
		if (bitboard << 8 * i & block) break; 
	}
	for (int i = 1; 8 * i != 64 && bitboard >> 8 * i; ++i) {
		attack |= bitboard >> 8 * i; 
		if (bitboard >> 8 * i & block) break; 
	}

	//left and right 
	for (int i = 1; bitboard << 1 * i & NOTFILE_H; ++i) {
		attack |= bitboard << 1 * i; 
		if (bitboard << 1 * i & block) break; 
	}
	for (int i = 1; bitboard >> 1 * i & NOTFILE_A; ++i) {
		attack |= bitboard >> 1 * i; 
		if (bitboard >> 1 * i & block) break; 
	}

	return attack; 
}

uint64_t verifyMagicNumRook(int index) {
	//initilaize bitboard 
	uint64_t bitboard = position[index]; 

	uint64_t allRelOccupancy = maskRookOccupancy(bitboard); 

	int numberOfBits = numBit(allRelOccupancy); 
	int numberOfBitsP2 = (1 << numberOfBits); 

	//generate all rook attacks occupancy
	uint64_t possibleAtk[4096]; 
	uint64_t possibleOccupancy[4096]; 
	for (int i = 0; i < numberOfBitsP2; ++i) {
		possibleOccupancy[i] = occupancyCombination(i, numberOfBits, allRelOccupancy); 
		possibleAtk[i] = maskRookAttackRT(bitboard, possibleOccupancy[i]); 

		using namespace std; 
		//cout << "PRINTING I : " << i << endl; 
		//printBoard(possibleOccupancy[i]); 
		//printBoard(possibleAtk[i]); 
	}

	//generate and try magic number
	for (int trial = 0; trial < 100000000; ++trial) {
		uint64_t magicNum = generateMagicNumCandidate(); 
		
		//array to keep track of collisions 
		uint64_t visited[4096]; 
		std::fill_n(visited, 4096, 0); 
		
		//fail flag
		bool fail = false; 
		for (int i = 0; i < numberOfBitsP2; ++i) {
			int magicIndex = (possibleOccupancy[i] * magicNum) >> (64 - numberOfBits); 

			if (visited[magicIndex] == 0) {
				visited[magicIndex] = possibleAtk[i]; 
			}
			else if (visited[magicIndex] != possibleAtk[i]) {
				fail = true; 
				break; 
			}
			
		}

		if (fail) {
			continue; 
		}
		else {
			return magicNum; 
		}
	}

	//return 0 for fail ; 
	return 0; 
}

/*
==================
queen 
==================
*/
//rely on rook and bishop magic numbers/functions 

uint64_t maskQueenAttack(int index, uint64_t occupancy) {
	uint64_t attack = 0x0; 
	attack |= maskRookAttack(index, occupancy); 
	attack |= maskBishopAttack(index, occupancy); 

	return attack; 
}



/*
==================
magic numbers 
==================
*/

//bitmask (kinda) to find all combinations 
uint64_t occupancyCombination(int index, int numBits, uint64_t occupancy) {

	//occupancy map 
	uint64_t occupancyCombination = 0x0;

	//loop over range of bits for occupancy 
	int initNumBits = numBits;
	for (int numBit = 0; numBit < numBits; ++numBit) {
		//index of lsb of attackMask 
		int lsbIndex = lsbBitIndex(occupancy);

		//pop lsb in attackMask 
		popBit(occupancy, position[lsbIndex]);

		//mask occupancy
		if (index & (1 << numBit)) {
			occupancyCombination |= position[lsbIndex];
		}
	}

	return occupancyCombination;
}

//xor shift random number generator for uint32
uint32_t state = 1804289383; 
uint32_t generateRandomUint32() {
	//defining next state 
	uint32_t nxtState = state; 

	//xor shifts 
	nxtState ^= nxtState << 13; 
	nxtState ^= nxtState >> 17; 
	nxtState ^= nxtState << 5;

	//storing next state 
	state = nxtState; 

	return nxtState; 
}

//generate random uint64 
uint64_t generateRandomUint64() {
	//defining numbers; 
	uint64_t num1, num2, num3, num4; 

	num1 = generateRandomUint32() & 0xffff; //I feel like the and is redundant 
	num2 = generateRandomUint32() & 0xffff; 
	num3 = generateRandomUint32() & 0xffff; 
	num4 = generateRandomUint32() & 0xffff; 

	return num1 | num2 << 16 | num3 << 32 | num4 << 48; 
}

//generate candidate magic number 
uint64_t generateMagicNumCandidate() {
	return generateRandomUint64() & generateRandomUint64() & generateRandomUint64(); 
}
