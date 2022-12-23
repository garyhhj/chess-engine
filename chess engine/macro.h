#pragma once
#include <stdint.h>

/*
=====================
bit macros constexpr 
=====================
*/

constexpr extern bool getBit(const uint64_t bitBoard, const int square);
constexpr extern void setBit(uint64_t& bitBoard, const int square);
constexpr extern void popBit(uint64_t& bitBoard, const int square); 

/*
=====================
bit macros constants
=====================
*/

//chess square coordinate to index 
enum : int {
	a8, b8, c8, d8, e8, f8, g8, h8,
	a7, b7, c7, d7, e7, f7, g7, h7,
	a6, b6, c6, d6, e6, f6, g6, h6,
	a5, b5, c5, d5, e5, f5, g5, h5,
	a4, b4, c4, d4, e4, f4, g4, h4,
	a3, b3, c3, d3, e3, f3, g3, h3,
	a2, b2, c2, d2, e2, f2, g2, h2,
	a1, b1, c1, d1, e1, f1, g1, h1,
};



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

//sides
enum : int {
	white,
	black,
};



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

const extern uint64_t NOTFILE_A;// = 0x7f7f7f7f7f7f7f7f;
const extern uint64_t NOTFILE_B;// = 0xbfbfbfbfbfbfbfbf;
const extern uint64_t NOTFILE_C;// = 0xdfdfdfdfdfdfdfdf;
const extern uint64_t NOTFILE_D;// = 0xefefefefefefefef;

const extern uint64_t NOTFILE_E;// = 0xf7f7f7f7f7f7f7f7;
const extern uint64_t NOTFILE_F;// = 0xfbfbfbfbfbfbfbfb;
const extern uint64_t NOTFILE_G;// = 0xfdfdfdfdfdfdfdfd;
const extern uint64_t NOTFILE_H;// = 0xfefefefefefefefe;

const extern uint64_t NOTFILE_AB;// = 0x3f3f3f3f3f3f3f3f;
const extern uint64_t NOTFILE_GH;// = 0xfcfcfcfcfcfcfcfc;
