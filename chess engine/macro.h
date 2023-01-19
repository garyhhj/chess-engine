#pragma once
#include <stdint.h>
#include <string>

/*
=====================
bit macros constexpr 
=====================
*/

constexpr extern bool getBit(const uint64_t bitBoard, const int index);
constexpr extern void setBit(uint64_t& bitBoard, const uint64_t square);
constexpr extern void popBit(uint64_t& bitBoard, const uint64_t square);

constexpr extern int numBit(uint64_t bitboard);
constexpr extern int lsbBitIndex(uint64_t bitboard);


/*
=====================
bit macros constants
=====================
*/

//coordinates on chess board (position) 
const extern uint64_t a8;// = 0x8000000000000000;
const extern uint64_t b8;// = a8 >> 1;
const extern uint64_t c8;// = a8 >> 2;
const extern uint64_t d8;// = a8 >> 3;
const extern uint64_t e8;// = a8 >> 4;
const extern uint64_t f8;// = a8 >> 5;
const extern uint64_t g8;// = a8 >> 6;
const extern uint64_t h8;// = a8 >> 7;

const extern uint64_t a7;// = 0x0080000000000000;
const extern uint64_t b7;// = a7 >> 1;
const extern uint64_t c7;// = a7 >> 2;
const extern uint64_t d7;// = a7 >> 3;
const extern uint64_t e7;// = a7 >> 4;
const extern uint64_t f7;// = a7 >> 5;
const extern uint64_t g7;// = a7 >> 6;
const extern uint64_t h7;// = a7 >> 7;

const extern uint64_t a6;// = 0x0000800000000000;
const extern uint64_t b6;// = a6 >> 1;
const extern uint64_t c6;// = a6 >> 2;
const extern uint64_t d6;// = a6 >> 3;
const extern uint64_t e6;// = a6 >> 4;
const extern uint64_t f6;// = a6 >> 5;
const extern uint64_t g6;// = a6 >> 6;
const extern uint64_t h6;// = a6 >> 7;

const extern uint64_t a5;// = 0x0000008000000000;
const extern uint64_t b5;// = a5 >> 1;
const extern uint64_t c5;// = a5 >> 2;
const extern uint64_t d5;// = a5 >> 3;
const extern uint64_t e5;// = a5 >> 4;
const extern uint64_t f5;// = a5 >> 5;
const extern uint64_t g5;// = a5 >> 6;
const extern uint64_t h5;// = a5 >> 7;

const extern uint64_t a4;// = 0x0000000080000000;
const extern uint64_t b4;// = a4 >> 1;
const extern uint64_t c4;// = a4 >> 2;
const extern uint64_t d4;// = a4 >> 3;
const extern uint64_t e4;// = a4 >> 4;
const extern uint64_t f4;// = a4 >> 5;
const extern uint64_t g4;// = a4 >> 6;
const extern uint64_t h4;// = a4 >> 7;

const extern uint64_t a3;// = 0x0000000000800000;
const extern uint64_t b3;// = a3 >> 1;
const extern uint64_t c3;// = a3 >> 2;
const extern uint64_t d3;// = a3 >> 3;
const extern uint64_t e3;// = a3 >> 4;
const extern uint64_t f3;// = a3 >> 5;
const extern uint64_t g3;// = a3 >> 6;
const extern uint64_t h3;// = a3 >> 7;

const extern uint64_t a2;// = 0x0000000000008000;
const extern uint64_t b2;// = a2 >> 1;
const extern uint64_t c2;// = a2 >> 2;
const extern uint64_t d2;// = a2 >> 3;
const extern uint64_t e2;// = a2 >> 4;
const extern uint64_t f2;// = a2 >> 5;
const extern uint64_t g2;// = a2 >> 6;
const extern uint64_t h2;// = a2 >> 7;

const extern uint64_t a1;// = 0x0000000000000080;
const extern uint64_t b1;// = a1 >> 1;
const extern uint64_t c1;// = a1 >> 2;
const extern uint64_t d1;// = a1 >> 3;
const extern uint64_t e1;// = a1 >> 4;
const extern uint64_t f1;// = a1 >> 5;
const extern uint64_t g1;// = a1 >> 6;
const extern uint64_t h1;// = a1 >> 7;

const extern uint64_t z0;// = 0; (invalid square) 


//chess coordinates (positions) indexed into array 
const extern uint64_t position[65];/*= {
	a8, b8, c8, d8, e8, f8, g8, h8,
	a7, b7, c7, d7, e7, f7, g7, h7,
	a6, b6, c6, d6, e6, f6, g6, h6,
	a5, b5, c5, d5, e5, f5, g5, h5,
	a4, b4, c4, d4, e4, f4, g4, h4,
	a3, b3, c3, d3, e3, f3, g3, h3,
	a2, b2, c2, d2, e2, f2, g2, h2,
	a1, b1, c1, d1, e1, f1, g1, h1,
	z0,
};
*/

//chess coodinates (position) index to string 
const extern std::string positionStr[65]; /* = {
	"a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8",
	"a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7",
	"a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6",
	"a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5",
	"a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4",
	"a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3",
	"a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2",
	"a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1",
	"",
};
*/

//chess coordinates(position) to index 
const extern int A8;// = 0;
const extern int B8;// = A8 + 1;
const extern int C8;// = A8 + 2;
const extern int D8;// = A8 + 3;
const extern int E8;// = A8 + 4;
const extern int F8;// = A8 + 5;
const extern int G8;// = A8 + 6;
const extern int H8;// = A8 + 7;

const extern int A7;// = 8;
const extern int B7;// = A7 + 1;
const extern int C7;// = A7 + 2;
const extern int D7;// = A7 + 3;
const extern int E7;// = A7 + 4;
const extern int F7;// = A7 + 5;
const extern int G7;// = A7 + 6;
const extern int H7;// = A7 + 7;

const extern int A6;// = 16;
const extern int B6;// = A6 + 1;
const extern int C6;// = A6 + 2;
const extern int D6;// = A6 + 3;
const extern int E6;// = A6 + 4;
const extern int F6;// = A6 + 5;
const extern int G6;// = A6 + 6;
const extern int H6;// = A6 + 7;

const extern int A5;// = 24;
const extern int B5;// = A5 + 1;
const extern int C5;// = A5 + 2;
const extern int D5;// = A5 + 3;
const extern int E5;// = A5 + 4;
const extern int F5;// = A5 + 5;
const extern int G5;// = A5 + 6;
const extern int H5;// = A5 + 7;

const extern int A4;// = 32;
const extern int B4;// = A4 + 1;
const extern int C4;// = A4 + 2;
const extern int D4;// = A4 + 3;
const extern int E4;// = A4 + 4;
const extern int F4;// = A4 + 5;
const extern int G4;// = A4 + 6;
const extern int H4;// = A4 + 7;

const extern int A3;// = 40;
const extern int B3;// = A3 + 1;
const extern int C3;// = A3 + 2;
const extern int D3;// = A3 + 3;
const extern int E3;// = A3 + 4;
const extern int F3;// = A3 + 5;
const extern int G3;// = A3 + 6;
const extern int H3;// = A3 + 7;

const extern int A2;// = 48;
const extern int B2;// = A2 + 1;
const extern int C2;// = A2 + 2;
const extern int D2;// = A2 + 3;
const extern int E2;// = A2 + 4;
const extern int F2;// = A2 + 5;
const extern int G2;// = A2 + 6;
const extern int H2;// = A2 + 7;

const extern int A1;// = 56;
const extern int B1;// = A1 + 1;
const extern int C1;// = A1 + 2;
const extern int D1;// = A1 + 3;
const extern int E1;// = A1 + 4;
const extern int F1;// = A1 + 5;
const extern int G1;// = A1 + 6;
const extern int H1;// = A1 + 7;





/*
=====================
enumerations 
=====================
*/

//sides (colors)
enum : int {
	white,
	black,
	both, 
};

//pieces 
enum : int {
	//white 
	wPawn,
	wKnight,//(N)  
	wBishop,
	wRook,
	wQueen,
	wKing,

	//black 
	bPawn,
	bKnight,//(n) 
	bBishop,
	bRook,
	bQueen,
	bKing,

	//no piece 
	noPiece, 
};

extern const std::string pieceStr[13];/* = {
	"wPawn", "wKnight", "wBishop", "wRook", "wQueen", "wKing", 
	"bPawn", "bKnight", "bBishop", "bRook", "bQueen", "bKing",
	"noPiece",
}
*/

//castling right (bit encoded) 
/*
1000 => white king side castle
0100 => white queen side castle
0010 => black king side castle
0001 => black queen side castle
*/
enum : uint32_t {
	wkc = 0b1000,
	wqc = 0b0100,
	bkc = 0b0010, 
	bqc = 0b0001, 
};

// castling rights update constants
extern const int castleRights[64];/* = {
	 7, 15, 15, 15,  3, 15, 15, 11,
	15, 15, 15, 15, 15, 15, 15, 15,
	15, 15, 15, 15, 15, 15, 15, 15,
	15, 15, 15, 15, 15, 15, 15, 15,
	15, 15, 15, 15, 15, 15, 15, 15,
	15, 15, 15, 15, 15, 15, 15, 15,
	15, 15, 15, 15, 15, 15, 15, 15,
	13, 15, 15, 15, 12, 15, 15, 14
};*/

/*
=====================
file constants 
=====================
*/

 
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

const extern uint64_t NOTRANK_1;// = 0xffffffffffffff00;
const extern uint64_t NOTRANK_2;// = 0xffffffffffff00ff;  
const extern uint64_t NOTRANK_7;// = 0xff00ffffffffffff; 
const extern uint64_t NOTRANK_8;// = 0x00ffffffffffffff;

const extern uint64_t NOTFILE_AH_NOTRANK_12;// = 0x007e7e7e7e7e7e00;

/*
=====================
misc
=====================
*/

//pieces from enum to letter repesentation 
extern const char piecesLetter[12];


/*
=====================
evaluation
=====================
*/

extern const int materialScore[12];/* = {
	100,      // white pawn score
	300,      // white knight scrore
	350,      // white bishop score
	500,      // white rook score
   1000,      // white queen score
  10000,      // white king score
   -100,      // black pawn score
   -300,      // black knight scrore
   -350,      // black bishop score
   -500,      // black rook score
  -1000,      // black queen score
 -10000,      // black king score
};*/



/*
==================
positional scores
==================
*/


// pawn positional score
extern const int wpawnScore[64]; /* = {
	90,  90,  90,  90,  90,  90,  90,  90,
	30,  30,  30,  40,  40,  30,  30,  30,
	20,  20,  20,  30,  30,  30,  20,  20,
	10,  10,  10,  20,  20,  10,  10,  10,
	 5,   5,  10,  20,  20,   5,   5,   5,
	 0,   0,   0,   5,   5,   0,   0,   0,
	 0,   0,   0, -10, -10,   0,   0,   0,
	 0,   0,   0,   0,   0,   0,   0,   0
}; */

extern const int bpawnScore[64];/* = {
	 0,   0,   0,   0,   0,   0,   0,   0,
	 0,   0,   0, -10, -10,   0,   0,   0, 
	 0,   0,   0,   5,   5,   0,   0,   0, 
	 5,   5,   5,  20,  20,  10,   5,   5, 
	10,  10,  10,  20,  20,  10,  10,  10, 
	20,  20,  30,  30,  30,  20,  20,  20, 
	30,  30,  30,  40,  40,  30,  30,  30,  
	90,  90,  90,  90,  90,  90,  90,  90
}; */



// knight positional score
extern const int wknightScore[64];/* = {
	-5,   0,   0,   0,   0,   0,   0,  -5,
	-5,   0,   0,  10,  10,   0,   0,  -5,
	-5,   5,  20,  20,  20,  20,   5,  -5,
	-5,  10,  20,  30,  30,  20,  10,  -5,
	-5,  10,  20,  30,  30,  20,  10,  -5,
	-5,   5,  20,  10,  10,  20,   5,  -5,
	-5,   0,   0,   0,   0,   0,   0,  -5,
	-5, -10,   0,   0,   0,   0, -10,  -5
}; */

extern const int bknightScore[64];/* = {

	-5, -10,   0,   0,   0,   0, -10,  -5,
	-5,   0,   0,   0,   0,   0,   0,  -5,
	-5,   5,  20,  10,  10,  20,   5,  -5,
	-5,  10,  20,  30,  30,  20,  10,  -5,
	-5,  10,  20,  30,  30,  20,  10,  -5,
	-5,   5,  20,  20,  20,  20,   5,  -5,
	-5,   0,   0,  10,  10,   0,   0,  -5,
	-5,   0,   0,   0,   0,   0,   0,  -5
};*/


// bishop positional score
extern const int wbishopScore[64];/* = {
	 0,   0,   0,   0,   0,   0,   0,   0,
	 0,   0,   0,   0,   0,   0,   0,   0,
	 0,   0,   0,  10,  10,   0,   0,   0,
	 0,   0,  10,  20,  20,  10,   0,   0,
	 0,   0,  10,  20,  20,  10,   0,   0,
	 0,  10,   0,   0,   0,   0,  10,   0,
	 0,  30,   0,   0,   0,   0,  30,   0,
	 0,   0, -10,   0,   0, -10,   0,   0

};*/


extern const int bbishopScore[64];/* = {
	 0,   0, -10,   0,   0, -10,   0,   0,
	 0,  30,   0,   0,   0,   0,  30,   0,
	 0,  10,   0,   0,   0,   0,  10,   0,
	 0,   0,  10,  20,  20,  10,   0,   0,
	 0,   0,  10,  20,  20,  10,   0,   0,
	 0,   0,   0,  10,  10,   0,   0,   0,
	 0,   0,   0,   0,   0,   0,   0,   0,
	 0,   0,   0,   0,   0,   0,   0,   0

};*/


// rook positional score
extern const int wrookScore[64];/* = {
	50,  50,  50,  50,  50,  50,  50,  50,
	50,  50,  50,  50,  50,  50,  50,  50,
	 0,   0,  10,  20,  20,  10,   0,   0,
	 0,   0,  10,  20,  20,  10,   0,   0,
	 0,   0,  10,  20,  20,  10,   0,   0,
	 0,   0,  10,  20,  20,  10,   0,   0,
	 0,   0,  10,  20,  20,  10,   0,   0,
	 0,   0,   0,  20,  20,   0,   0,   0

};*/

extern const int bbrookScore[64];/* = {
	 0,   0,   0,  20,  20,   0,   0,   0,
	 0,   0,  10,  20,  20,  10,   0,   0,
	 0,   0,  10,  20,  20,  10,   0,   0,
	 0,   0,  10,  20,  20,  10,   0,   0,
	 0,   0,  10,  20,  20,  10,   0,   0,
	 0,   0,  10,  20,  20,  10,   0,   0,
	50,  50,  50,  50,  50,  50,  50,  50,
	50,  50,  50,  50,  50,  50,  50,  50

};*/


// king positional score
extern const int wkingScore[64];/* = {
	 0,   0,   0,   0,   0,   0,   0,   0,
	 0,   0,   5,   5,   5,   5,   0,   0,
	 0,   5,   5,  10,  10,   5,   5,   0,
	 0,   5,  10,  20,  20,  10,   5,   0,
	 0,   5,  10,  20,  20,  10,   5,   0,
	 0,   0,   5,  10,  10,   5,   0,   0,
	 0,   5,   5,  -5,  -5,   0,   5,   0,
	 0,   0,   5,   0, -15,   0,  10,   0
};*/

extern const int bkingScore[64];/* = {
	 0,  10,   0, -15,   0,   5,   0,   0,
	 0,   5,   0,  -5,  -5,   5,   5,   0,
	 0,   0,   5,  10,  10,   5,   0,   0,
	 0,   5,  10,  20,  20,  10,   5,   0,
	 0,   5,  10,  20,  20,  10,   5,   0,
	 0,   5,   5,  10,  10,   5,   5,   0,
	 0,   0,   5,   5,   5,   5,   0,   0,
	 0,   0,   0,   0,   0,   0,   0,   0
};*/

