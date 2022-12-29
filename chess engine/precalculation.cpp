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

void initLeaperPiece() {
	initPawnAttack(); 
	initKnightAttack(); 
	initKingAttack(); 
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
	0xa168041010224880, 0x400102020020885, 0x212001220042403, 0x20900041108c, 0x400000049082100, 0x111110105100308, 0x22010108410402, 0x200c100228c10a80,
	0x91020885040090, 0x80000c88900d0000, 0x2003002020400, 0x800e100284140002, 0x6311401040228, 0x2040440209102440, 0x1102923002200165, 0x1011020082020910,
	0x8002080827804118, 0x44008082022100, 0x400812000041, 0x2000040c1811e404, 0x80a2940208000101, 0x2401008250002000, 0x34042a40048840, 0x1040028010500,
	0x40100204c8121100, 0x881010200040a02, 0x40008020020260, 0x8008a080a1680200, 0x2010242100081, 0x8582400080500, 0xc224202004040400, 0x1824009005220100,
	0x4004084641011041, 0x88004002011580, 0x840080802000, 0x42011000802400c, 0x1204100009104080, 0x1010010a020641, 0x20210124084600, 0xc01100020103c208,
	0x2133000411821020, 0x10200202102200, 0x8021004820180000, 0x4009204404008019, 0x4018102100c40080, 0x340c6001040104, 0x9009020010c00, 0x2440908401081209,
	0x48089808088404, 0x1220110080465, 0x408020210580380, 0x45c00800200, 0x1080801002004, 0x8002102c11004201, 0x81301010030940, 0x8c02008200901400,
	0x4020910780203, 0x4012080404006004, 0x42040c6040000006, 0x4609140101088100, 0x129200820200a471, 0x510060820418829, 0x20201502510040,
};

//second set of magic number (in case) 
/*
0x40040822862081,
0xa168041010224880, 0x8010141024304420, 0x850000c804208209, 0x2400115284c20a00, 0x100420c021080800, 0x100310402010480, 0x22010108410402, 0x1010300200425028,
0x4044408022444, 0x18200202820010, 0x81001082022481, 0x20804202a080080, 0x40004200908000, 0x4885a80d100080, 0x860990400200, 0x802024046000100,
0xd48010802018090, 0x4402600040802100, 0x160401008803101, 0x800062011004800, 0x4082090001800, 0x8028a1002201100, 0x418110084500a100, 0x19450020010c00,
0x2008222040048818, 0x20010040160800, 0x810048200082200, 0x2285400808008200, 0x8804229000080024, 0x80822000080800, 0x1004442200403a20, 0xc0010440120a0084,
0x404140008410400, 0x4010108001004128, 0x85010002104014, 0x480a040008010820, 0x822050040010, 0x10102004440080, 0x260310584041800, 0x2210811050441020,
0x1208401011009, 0x8084210068c004, 0x829400a0000c, 0x40042008042100c0, 0x4190000220220022, 0x9008020202d80201, 0xeac0c0020c0400, 0xc10082412010,
0x104008208224020, 0x2100008211400024, 0x2324240420008040, 0x820a02000400, 0x2118104030101, 0xc0287000828104, 0x400484108601, 0x182008400821080,
0x7009084130080800, 0x84240440c00008, 0x161104180402002, 0x20a80a002100c04a, 0xc08008408801000, 0x2820010421004828, 0x40502008025080a8,
*/

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

//generate maskBishopAttack for rookAttack table with magic index 
void maskBishopAttack(int index) {
	//initialize occupancy 
	uint64_t occupancy = maskBishopOccupancy(position[index]);

	int numCombinations = (1 << numBit(occupancy));

	//rookAttack[index][magicIndex] = something; 

	for (int i = 0; i < numCombinations; ++i) {
		uint64_t relOccupancy = setOccupancyCombination(i, numBit(occupancy), occupancy);

		int magicIndex = relOccupancy * bishopMagicNum[index] >> (64 - numBit(occupancy));
		bishopAttack[index][magicIndex] = maskBishopAttackRT(position[index], relOccupancy);
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
	0x8a80104000800020ULL, 0x140002000100040ULL, 0x2801880a0017001ULL, 0x100081001000420ULL, 0x200020010080420ULL, 0x3001c0002010008ULL, 0x8480008002000100ULL, 0x2080088004402900ULL,
	0x800098204000ULL, 0x2024401000200040ULL,
	0x100802000801000ULL,
	0x120800800801000ULL,
	0x208808088000400ULL,
	0x2802200800400ULL,
	0x2200800100020080ULL,
	0x801000060821100ULL,
	0x80044006422000ULL,
	0x100808020004000ULL,
	0x12108a0010204200ULL,
	0x140848010000802ULL,
	0x481828014002800ULL,
	0x8094004002004100ULL,
	0x4010040010010802ULL,
	0x20008806104ULL,
	0x100400080208000ULL,
	0x2040002120081000ULL,
	0x21200680100081ULL,
	0x20100080080080ULL,
	0x2000a00200410ULL,
	0x20080800400ULL,
	0x80088400100102ULL,
	0x80004600042881ULL,
	0x4040008040800020ULL,
	0x440003000200801ULL,
	0x4200011004500ULL,
	0x188020010100100ULL,
	0x14800401802800ULL,
	0x2080040080800200ULL,
	0x124080204001001ULL,
	0x200046502000484ULL,
	0x480400080088020ULL,
	0x1000422010034000ULL,
	0x30200100110040ULL,
	0x100021010009ULL,
	0x2002080100110004ULL,
	0x202008004008002ULL,
	0x20020004010100ULL,
	0x2048440040820001ULL,
	0x101002200408200ULL,
	0x40802000401080ULL,
	0x4008142004410100ULL,
	0x2060820c0120200ULL,
	0x1001004080100ULL,
	0x20c020080040080ULL,
	0x2935610830022400ULL,
	0x44440041009200ULL,
	0x280001040802101ULL,
	0x2100190040002085ULL,
	0x80c0084100102001ULL,
	0x4024081001000421ULL,
	0x20030a0244872ULL,
	0x12001008414402ULL,
	0x2006104900a0804ULL,
	0x1004081002402ULL
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

//generate maskRookAttack for rookAttack table with magic index 
void maskRookAttack(int index) {

}

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
	uint64_t bitboard = 0x0ULL;

	//result bitboard 
	uint64_t attack = 0x0;

	//set pieces on board 
	setBit(bitboard, square);


	//up and down 
	for (int i = 1; 8 * i != 64 && bitboard << 8 * i ; ++i) {
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


/*
==================
magic numbers 
==================
*/

uint64_t setOccupancyCombination(int index, int numBits, uint64_t occupancy) {

	//occupancy map 
	uint64_t occupancyCombination = 0x0;

	//loop over range of bits for attackmask 

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
