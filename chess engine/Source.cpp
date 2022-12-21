#include <iostream>
#include <vector>

/*
==================
bit macros 
==================
*/

constexpr bool getBit(uint64_t exists, int square) {
	return (exists >> square) & 0x1;
}
/*
==================
bit board 
==================
*/



class BitBoard {
	//need a bit board for each piece 

	//need a convention on which element of piece is which piece in chess 

	//1 - top rook 
	//2 - knight 
	//3 - bishop 
	//
public:

	uint64_t exists; 
	std::vector<uint64_t> pieces; 

	//constructor 
	BitBoard() : 
		exists{0x4}, 
		pieces{
		0x8000000000000000 >> 0, 0x8000000000000000 >> 1, 0x8000000000000000 >> 2, 0x8000000000000000 >> 3, 0x8000000000000000 >> 4, 0x8000000000000000 >> 5, 0x8000000000000000 >> 6, 0x8000000000000000 >> 7, 
		0x8000000000000000 >> 8, 0x8000000000000000 >> 9, 0x8000000000000000 >> 10, 0x8000000000000000 >> 11, 0x8000000000000000 >> 12, 0x8000000000000000 >> 13, 0x8000000000000000 >> 14, 0x8000000000000000 >> 15, 
		0x0000000000000001 << 15, 0x0000000000000001 << 14, 0x0000000000000001 << 13, 0x0000000000000001 << 12, 0x0000000000000001 << 11, 0x0000000000000001 << 10, 0x0000000000000001 << 9, 0x0000000000000001 << 8,
		0x0000000000000001 << 7, 0x0000000000000001 << 6, 0x0000000000000001 << 5, 0x0000000000000001 << 4, 0x0000000000000001 << 3, 0x0000000000000001 << 2, 0x0000000000000001 << 1, 0x0000000000000001 << 0
	} {}

	//moving 
	void moveHorizontal(int index, int shift) {
		//can you shift a negative number of bits? 

		if (shift < 0) {
			shift *= -1;
			pieces[index] >>= shift;
		}
		else {
			pieces[index] <<= shift; 
		}
	}

	void moveVeritcal(int index, int shift) {
		//shift by 8 times? 

	}

	void moveDiagonally(int index, int shift) {
		//shift by 7 time? 
	}

	//generating knights movement will be weird 
	//shift right then diagonal 
	//somethign like combining shifting vertically and diagonally 

	void printBoard(); 


	
};

void BitBoard::printBoard() {
	using namespace std; 
	for (int rank = 0; rank < 8; ++rank) {
		for (int file = 0; file < 8; ++file) {
			int square = rank * 8 + file; 

			cout << (getBit(exists, square) ? " 1 " : " 0 ");
		}
		cout << endl; 
	}
}

using namespace std; 

int main() {
	BitBoard board; 
	board.printBoard(); 

}