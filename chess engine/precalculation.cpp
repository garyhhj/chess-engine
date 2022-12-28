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
	0x1010549228402,
	0x2000011002080084, 0x11004802040005, 0x406002014300842, 0x104a00080440a012, 0x2001200095004009, 0x882004883210112, 0x100c020800417, 0x41048c0200,
	0x4106002144080600, 0x800a800a00040080, 0x426000420109a00, 0x8000680310008080, 0x822008060401600, 0x406400088200080, 0x202208001104100, 0x501224008e460001,
	0x4802010802640010, 0x400102040080104, 0x2011001008030004, 0x1001009000090020, 0x201e420080320020, 0x9869008040010020, 0x810308040028008, 0x220081020001c4,
	0x2000101704000a08, 0x216000802009004, 0x28820400800800, 0x2012002046001008, 0x60450231002000, 0x405024001002080, 0x800400030800084, 0x5060010824c,
	0x242100010012003c, 0x4800c0080120080, 0x9004040080080081, 0x1200b00100100, 0x800910100402000, 0x24a00040100040, 0x8500802080024000, 0x202020004004087,
	0x440021702248, 0x540080800c000200, 0x2088008004028088, 0x808008001002, 0x828020053000, 0x802000c0100222c0, 0x281808004c00020, 0x8006000225009044,
	0x9005001402000100, 0x40800600440080, 0x24808084000800, 0x200801002802800, 0xa2002056008042, 0x1003040008101, 0x401002080010240, 0x280104063000480,
	0x9000c0200058300, 0x400881020040012, 0x4580080007801400, 0xc800c0800100082, 0x80200080900088, 0x840002000405008, 0x80014000802034,
};

//second set of magic numbers (in case) 
/*
0x1010549228402,
0x2000011002080084, 0x8012004824011022, 0x9202002005881002, 0x8010210408100101, 0x820040081022, 0x804012400081a103, 0x8004852200104502, 0x10040a41200,
0x1404308802014400, 0x402000408100200, 0x8001040080280280, 0x408081000210100, 0x4200200100401100, 0xa820200040008080, 0x2000210050800100, 0x200204846c020009,
0x88084102840010, 0x8000040002008080, 0x202000890060020, 0x1001000090020, 0x2020004021010012, 0x9150500020084000, 0x8002400080018028, 0x209000041001082,
0xa000080144003002, 0x8004040080800200, 0x18002004040040, 0x801002009001000, 0x802000801000, 0x1000442002c01000, 0x2080004001402000, 0x4200008421,
0x41000100020004, 0x9024008080040200, 0x100080080040080, 0x4080100100082101, 0x1101004700200110, 0x400400080200080, 0x8c40400080208000, 0x44008600010882c4,
0x280808002000100, 0x184808004010200, 0x122020008100520, 0x848010000802, 0x8810820010420820, 0x100808020004000, 0x800228004804000, 0x40280018022d300,
0x8029010402000100, 0x62000408020010, 0x800400800800, 0x200808010000800, 0x2004200108024, 0x1000400020100048, 0xd000800020804010, 0x200010200402894,
0x280008001000200, 0x100010008040002, 0x4200201008040200, 0x2200104200080420, 0x0, 0x40400020001000, 0x3880004000201080,
*/

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
	//initialize occupancy 
	uint64_t occupancy = maskRookOccupancy(position[index]); 

	int numCombinations = (1 << numBit(occupancy)); 
	
	//rookAttack[index][magicIndex] = something; 

	for (int i = 0; i < numCombinations; ++i) {
		uint64_t relOccupancy = setOccupancyCombination(i, numCombinations, occupancy); 

		int magicIndex = relOccupancy * rookMagicNum[index] >> (64 - numBit(occupancy)); 
		
		rookAttack[index][magicIndex] = maskRookAttackRT(position[index], relOccupancy); 
	}
}

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

uint64_t setOccupancyCombination(int index, int numBits, uint64_t attackMask) {

	//occupancy map 
	uint64_t occupancy = 0x0; 

	//loop over range of bits for attackmask 

	int initNumBits = numBits; 
	for (int numBit = 0; numBit < numBits; ++numBit) {
		//index of lsb of attackMask 
		int lsbIndex = lsbBitIndex(attackMask);

		//pop lsb in attackMask 
		popBit(attackMask, position[lsbIndex]);

		//mask occupancy
		if (index & (1 << numBit)) {
			occupancy |= position[lsbIndex]; 
		}
	}

	return occupancy; 
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

uint64_t verifyMagicNum(uint64_t square, bool isRook, bool isBishop, int numBits) {

	//relevant occupancy 
	uint64_t relOccupancy[4096];

	//attack map corresponding to relOccupancy 
	uint64_t attackMap[4096]; 

	int numCombination = (1 << numBits);

	uint64_t attackMask = 0x0; 
	if (isRook) {
		attackMask = maskRookOccupancy(square); 
	}
	else if (isBishop) {
		attackMask = maskBishopOccupancy(square); 
	}

	//initialize relOccupancy and attackMap 
	for (int index = 0; index < numCombination; ++index) {

		//calculate relevant occupancy  
		relOccupancy[index] = setOccupancyCombination(index, numBit(attackMask), attackMask);

		//calculate attack map for rook or bishop 
		if (isRook) {
			attackMap[index] = maskRookAttackRT(square, relOccupancy[index]);
		}
		else {//if (isBishop) {
			attackMap[index] = maskBishopAttackRT(square, relOccupancy[index]);
		}

	}

	//generate and verify magic number 
	uint64_t visited[4096];
	for (int i = 0; i < 1000000; ++i) {
		//generate magic num 
		uint64_t magicNum = generateMagicNumCandidate(); 

		//reject non useful magic num 
		if (numBit((attackMask * magicNum) & 0xFF00000000000000) < 6) continue;

		//fill visited array with 0 
		std::fill_n(visited, 4096, 0); 

		//fail flag 
		bool fail = false; 
		for (int index = 0; index < numCombination; ++index) {
			uint64_t magicIndex = (relOccupancy[index] * magicNum) >> (64 - numBits); 

			//no collsion 
			if (!visited[magicIndex]) {
				visited[magicIndex] = attackMap[index];
			}
			//collision 
			else {
				fail = true; 
				break; 
			}
		}

		if (!fail) {
			return magicNum; 
		}
	}
	
	//0 indicates no valid magic number found; 
	return 0; 
}