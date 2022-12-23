#pragma once
#include <vector>
#include <iostream>

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
};