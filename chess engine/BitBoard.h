#pragma once
#include <vector>
#include <iostream>

/*
==================
bit macros
==================
*/
//when square is zero it does something 
constexpr bool getBit(const uint64_t bitBoard, const int square){
	return bitBoard & (0x8000000000000000 >> square);
}

constexpr void setBit(uint64_t& bitBoard, const int square) { 
	bitBoard |= (0x8000000000000000 >> square);
}

constexpr void popBit(uint64_t& bitBoard, const int square) {
	bitBoard &= ~(0x8000000000000000 >> square);
}

//chess square coordinate to index 
enum {
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
enum {
	white, 
	black, 
};

//file constants 
/*
NOTAFILE example: 
8   0  1  1  1  1  1  1  1
7   0  1  1  1  1  1  1  1
6   0  1  1  1  1  1  1  1
5   0  1  1  1  1  1  1  1
4   0  1  1  1  1  1  1  1
3   0  1  1  1  1  1  1  1
2   0  1  1  1  1  1  1  1
1   0  1  1  1  1  1  1  1

a  b  c  d  e  f  g  h
*/

const uint64_t NOTAFILE = 0x7f7f7f7f7f7f7f7f; 
const uint64_t NOTBFILE = 0xbfbfbfbfbfbfbfbf;
const uint64_t NOTCFILE = 0xdfdfdfdfdfdfdfdf; 
const uint64_t NOTDFILE = 0xefefefefefefefef;

const uint64_t NOTEFILE = 0xf7f7f7f7f7f7f7f7; 
const uint64_t NOTFFILE = 0xfbfbfbfbfbfbfbfb; 
const uint64_t NOTGFILE = 0xfdfdfdfdfdfdfdfd; 
const uint64_t NOTHFILE = 0xfefefefefefefefe;


/*
==================
bit board
==================
*/

class BitBoard {
public:
	uint64_t bitBoard;
	std::vector<uint64_t> pieces;

	//constructor 
	BitBoard();
	void printBoard();
	void printBoard(uint64_t bitBoard); 
};