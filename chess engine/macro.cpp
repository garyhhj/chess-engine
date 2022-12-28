#include "macro.h"
#include <stdint.h>

/*
==================
bit macros
==================
*/

constexpr bool getBit(const uint64_t bitBoard, const int index) {
	return bitBoard & (0x8000000000000000 >> index);
	//return bitBoard & square; 
}

constexpr void setBit(uint64_t& bitBoard, const uint64_t square) {
	//bitBoard |= (0x8000000000000000 >> square);
	bitBoard |= square; 
}

constexpr void popBit(uint64_t& bitBoard, const uint64_t square) {
	//bitBoard &= ~(0x8000000000000000 >> square);
	bitBoard &= ~square; 
}


constexpr int numBit(uint64_t bitboard) {
	int count = 0;

	while (bitboard) {
		++count;

		bitboard &= bitboard - 1;
	}
	return count;
}

//returns index to lsb 
/*
		Index: 58 

8   0  0  0  0  0  0  0  0
7   0  0  0  0  0  0  0  0
6   0  0  0  0  0  0  0  0
5   0  0  0  0  0  0  0  0
4   0  0  0  0  0  0  0  0
3   0  0  0  0  0  0  0  0
2   0  0  0  0  0  0  0  0
1   0  0  1  0  0  0  0  0

	a  b  c  d  e  f  g  h
*/
constexpr int lsbBitIndex(uint64_t bitboard) {

	//make sure bitboard is not zero 
	if (bitboard) {
		return 63 - numBit((bitboard & (~bitboard +1)) - 1); 
	}

	else {
		//invalid index 
		return -1; 
	}
}


/*
=====================
bit macros constants
=====================
*/

//chess square coordinate to index 
const extern uint64_t a8 = 0x8000000000000000;
const extern uint64_t b8 = a8 >> 1;
const extern uint64_t c8 = a8 >> 2;
const extern uint64_t d8 = a8 >> 3;
const extern uint64_t e8 = a8 >> 4;
const extern uint64_t f8 = a8 >> 5;
const extern uint64_t g8 = a8 >> 6;
const extern uint64_t h8 = a8 >> 7;

const extern uint64_t a7 = 0x0080000000000000;
const extern uint64_t b7 = a7 >> 1;
const extern uint64_t c7 = a7 >> 2;
const extern uint64_t d7 = a7 >> 3;
const extern uint64_t e7 = a7 >> 4;
const extern uint64_t f7 = a7 >> 5;
const extern uint64_t g7 = a7 >> 6;
const extern uint64_t h7 = a7 >> 7;

const extern uint64_t a6 = 0x0000800000000000;
const extern uint64_t b6 = a6 >> 1;
const extern uint64_t c6 = a6 >> 2;
const extern uint64_t d6 = a6 >> 3;
const extern uint64_t e6 = a6 >> 4;
const extern uint64_t f6 = a6 >> 5;
const extern uint64_t g6 = a6 >> 6;
const extern uint64_t h6 = a6 >> 7;

const extern uint64_t a5 = 0x0000008000000000;
const extern uint64_t b5 = a5 >> 1;
const extern uint64_t c5 = a5 >> 2;
const extern uint64_t d5 = a5 >> 3;
const extern uint64_t e5 = a5 >> 4;
const extern uint64_t f5 = a5 >> 5;
const extern uint64_t g5 = a5 >> 6;
const extern uint64_t h5 = a5 >> 7;

const extern uint64_t a4 = 0x0000000080000000;
const extern uint64_t b4 = a4 >> 1;
const extern uint64_t c4 = a4 >> 2;
const extern uint64_t d4 = a4 >> 3;
const extern uint64_t e4 = a4 >> 4;
const extern uint64_t f4 = a4 >> 5;
const extern uint64_t g4 = a4 >> 6;
const extern uint64_t h4 = a4 >> 7;

const extern uint64_t a3 = 0x0000000000800000;
const extern uint64_t b3 = a3 >> 1;
const extern uint64_t c3 = a3 >> 2;
const extern uint64_t d3 = a3 >> 3;
const extern uint64_t e3 = a3 >> 4;
const extern uint64_t f3 = a3 >> 5;
const extern uint64_t g3 = a3 >> 6;
const extern uint64_t h3 = a3 >> 7;

const extern uint64_t a2 = 0x0000000000008000;
const extern uint64_t b2 = a2 >> 1;
const extern uint64_t c2 = a2 >> 2;
const extern uint64_t d2 = a2 >> 3;
const extern uint64_t e2 = a2 >> 4;
const extern uint64_t f2 = a2 >> 5;
const extern uint64_t g2 = a2 >> 6;
const extern uint64_t h2 = a2 >> 7;

const extern uint64_t a1 = 0x0000000000000080;
const extern uint64_t b1 = a1 >> 1;
const extern uint64_t c1 = a1 >> 2;
const extern uint64_t d1 = a1 >> 3;
const extern uint64_t e1 = a1 >> 4;
const extern uint64_t f1 = a1 >> 5;
const extern uint64_t g1 = a1 >> 6;
const extern uint64_t h1 = a1 >> 7;

const extern uint64_t position[64] = {
	a8, b8, c8, d8, e8, f8, g8, h8,
	a7, b7, c7, d7, e7, f7, g7, h7,
	a6, b6, c6, d6, e6, f6, g6, h6,
	a5, b5, c5, d5, e5, f5, g5, h5,
	a4, b4, c4, d4, e4, f4, g4, h4,
	a3, b3, c3, d3, e3, f3, g3, h3,
	a2, b2, c2, d2, e2, f2, g2, h2,
	a1, b1, c1, d1, e1, f1, g1, h1,
};



//chess coordinates(position) to index 
const int A8 = 0;
const int B8 = A8 + 1;
const int C8 = A8 + 2;
const int D8 = A8 + 3;
const int E8 = A8 + 4;
const int F8 = A8 + 5;
const int G8 = A8 + 6;
const int H8 = A8 + 7;

const int A7 = 8;
const int B7 = A7 + 1;
const int C7 = A7 + 2;
const int D7 = A7 + 3;
const int E7 = A7 + 4;
const int F7 = A7 + 5;
const int G7 = A7 + 6;
const int H7 = A7 + 7;

const int A6 = 16;
const int B6 = A6 + 1;
const int C6 = A6 + 2;
const int D6 = A6 + 3;
const int E6 = A6 + 4;
const int F6 = A6 + 5;
const int G6 = A6 + 6;
const int H6 = A6 + 7;

const int A5 = 24;
const int B5 = A5 + 1;
const int C5 = A5 + 2;
const int D5 = A5 + 3;
const int E5 = A5 + 4;
const int F5 = A5 + 5;
const int G5 = A5 + 6;
const int H5 = A5 + 7;

const int A4 = 32;
const int B4 = A4 + 1;
const int C4 = A4 + 2;
const int D4 = A4 + 3;
const int E4 = A4 + 4;
const int F4 = A4 + 5;
const int G4 = A4 + 6;
const int H4 = A4 + 7;

const int A3 = 40;
const int B3 = A3 + 1;
const int C3 = A3 + 2;
const int D3 = A3 + 3;
const int E3 = A3 + 4;
const int F3 = A3 + 5;
const int G3 = A3 + 6;
const int H3 = A3 + 7;

const int A2 = 48;
const int B2 = A2 + 1;
const int C2 = A2 + 2;
const int D2 = A2 + 3;
const int E2 = A2 + 4;
const int F2 = A2 + 5;
const int G2 = A2 + 6;
const int H2 = A2 + 7;

const int A1 = 56;
const int B1 = A1 + 1;
const int C1 = A1 + 2;
const int D1 = A1 + 3;
const int E1 = A1 + 4;
const int F1 = A1 + 5;
const int G1 = A1 + 6;
const int H1 = A1 + 7;


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
/*
enum : int{
	white,
	black,
};
*/

//file constants 
/*
		NOT A FILE

8   0  1  1  1  1  1  1  1
7   0  1  1  1  1  1  1  1
6   0  1  1  1  1  1  1  1
5   0  1  1  1  1  1  1  1
4   0  1  1  1  1  1  1  1
3   0  1  1  1  1  1  1  1
2   0  1  1  1  1  1  1  1
1   0  1  1  1  1  1  1  1

	a  b  c  d  e  f  g  h


		NOT B FILE

8   0  1  1  1  1  1  1  1
7   0  1  1  1  1  1  1  1
6   0  1  1  1  1  1  1  1
5   0  1  1  1  1  1  1  1
4   0  1  1  1  1  1  1  1
3   0  1  1  1  1  1  1  1
2   0  1  1  1  1  1  1  1
1   0  1  1  1  1  1  1  1

	a  b  c  d  e  f  g  h

	etc.
*/

const uint64_t NOTFILE_A = 0x7f7f7f7f7f7f7f7f;
const uint64_t NOTFILE_B = 0xbfbfbfbfbfbfbfbf;
const uint64_t NOTFILE_C = 0xdfdfdfdfdfdfdfdf;
const uint64_t NOTFILE_D = 0xefefefefefefefef;

const uint64_t NOTFILE_E = 0xf7f7f7f7f7f7f7f7;
const uint64_t NOTFILE_F = 0xfbfbfbfbfbfbfbfb;
const uint64_t NOTFILE_G = 0xfdfdfdfdfdfdfdfd;
const uint64_t NOTFILE_H = 0xfefefefefefefefe;

const uint64_t NOTFILE_AB = 0x3f3f3f3f3f3f3f3f;
const uint64_t NOTFILE_GH = 0xfcfcfcfcfcfcfcfc;

const uint64_t NOTRANK_1 = 0xffffffffffffff00;
const uint64_t NOTRANK_8 = 0x00ffffffffffffff;

const uint64_t NOTFILE_AH_NOTRANK_12 = 0x007e7e7e7e7e7e00;

