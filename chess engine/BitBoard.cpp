#include "BitBoard.h"
#include "macro.h"
#include "precalculation.h"
#include <iostream>


/*
 ==================================
            Chess board
 ==================================
 */

 /*
                             WHITE PIECES
         Pawns                  Knights              Bishops

   8  0 0 0 0 0 0 0 0    8  0 0 0 0 0 0 0 0    8  0 0 0 0 0 0 0 0
   7  0 0 0 0 0 0 0 0    7  0 0 0 0 0 0 0 0    7  0 0 0 0 0 0 0 0
   6  0 0 0 0 0 0 0 0    6  0 0 0 0 0 0 0 0    6  0 0 0 0 0 0 0 0
   5  0 0 0 0 0 0 0 0    5  0 0 0 0 0 0 0 0    5  0 0 0 0 0 0 0 0
   4  0 0 0 0 0 0 0 0    4  0 0 0 0 0 0 0 0    4  0 0 0 0 0 0 0 0
   3  0 0 0 0 0 0 0 0    3  0 0 0 0 0 0 0 0    3  0 0 0 0 0 0 0 0
   2  1 1 1 1 1 1 1 1    2  0 0 0 0 0 0 0 0    2  0 0 0 0 0 0 0 0
   1  0 0 0 0 0 0 0 0    1  0 1 0 0 0 0 1 0    1  0 0 1 0 0 1 0 0
      a b c d e f g h       a b c d e f g h       a b c d e f g h
          Rooks                 Queens                 King
   8  0 0 0 0 0 0 0 0    8  0 0 0 0 0 0 0 0    8  0 0 0 0 0 0 0 0
   7  0 0 0 0 0 0 0 0    7  0 0 0 0 0 0 0 0    7  0 0 0 0 0 0 0 0
   6  0 0 0 0 0 0 0 0    6  0 0 0 0 0 0 0 0    6  0 0 0 0 0 0 0 0
   5  0 0 0 0 0 0 0 0    5  0 0 0 0 0 0 0 0    5  0 0 0 0 0 0 0 0
   4  0 0 0 0 0 0 0 0    4  0 0 0 0 0 0 0 0    4  0 0 0 0 0 0 0 0
   3  0 0 0 0 0 0 0 0    3  0 0 0 0 0 0 0 0    3  0 0 0 0 0 0 0 0
   2  0 0 0 0 0 0 0 0    2  0 0 0 0 0 0 0 0    2  0 0 0 0 0 0 0 0
   1  1 0 0 0 0 0 0 1    1  0 0 0 1 0 0 0 0    1  0 0 0 0 1 0 0 0
      a b c d e f g h       a b c d e f g h       a b c d e f g h


                             BLACK PIECES
         Pawns                  Knights              Bishops

   8  0 0 0 0 0 0 0 0    8  0 1 0 0 0 0 1 0    8  0 0 1 0 0 1 0 0
   7  1 1 1 1 1 1 1 1    7  0 0 0 0 0 0 0 0    7  0 0 0 0 0 0 0 0
   6  0 0 0 0 0 0 0 0    6  0 0 0 0 0 0 0 0    6  0 0 0 0 0 0 0 0
   5  0 0 0 0 0 0 0 0    5  0 0 0 0 0 0 0 0    5  0 0 0 0 0 0 0 0
   4  0 0 0 0 0 0 0 0    4  0 0 0 0 0 0 0 0    4  0 0 0 0 0 0 0 0
   3  0 0 0 0 0 0 0 0    3  0 0 0 0 0 0 0 0    3  0 0 0 0 0 0 0 0
   2  0 0 0 0 0 0 0 0    2  0 0 0 0 0 0 0 0    2  0 0 0 0 0 0 0 0
   1  0 0 0 0 0 0 0 0    1  0 0 0 0 0 0 0 0    1  0 0 0 0 0 0 0 0
      a b c d e f g h       a b c d e f g h       a b c d e f g h
          Rooks                 Queens                 King
   8  1 0 0 0 0 0 0 1    8  0 0 0 1 0 0 0 0    8  0 0 0 0 1 0 0 0
   7  0 0 0 0 0 0 0 0    7  0 0 0 0 0 0 0 0    7  0 0 0 0 0 0 0 0
   6  0 0 0 0 0 0 0 0    6  0 0 0 0 0 0 0 0    6  0 0 0 0 0 0 0 0
   5  0 0 0 0 0 0 0 0    5  0 0 0 0 0 0 0 0    5  0 0 0 0 0 0 0 0
   4  0 0 0 0 0 0 0 0    4  0 0 0 0 0 0 0 0    4  0 0 0 0 0 0 0 0
   3  0 0 0 0 0 0 0 0    3  0 0 0 0 0 0 0 0    3  0 0 0 0 0 0 0 0
   2  0 0 0 0 0 0 0 0    2  0 0 0 0 0 0 0 0    2  0 0 0 0 0 0 0 0
   1  0 0 0 0 0 0 0 0    1  0 0 0 0 0 0 0 0    1  0 0 0 0 0 0 0 0
      a b c d e f g h       a b c d e f g h       a b c d e f g h


                              OCCUPANCIES

      White occupancy       Black occupancy       All occupancies
   8  0 0 0 0 0 0 0 0    8  1 1 1 1 1 1 1 1    8  1 1 1 1 1 1 1 1
   7  0 0 0 0 0 0 0 0    7  1 1 1 1 1 1 1 1    7  1 1 1 1 1 1 1 1
   6  0 0 0 0 0 0 0 0    6  0 0 0 0 0 0 0 0    6  0 0 0 0 0 0 0 0
   5  0 0 0 0 0 0 0 0    5  0 0 0 0 0 0 0 0    5  0 0 0 0 0 0 0 0
   4  0 0 0 0 0 0 0 0    4  0 0 0 0 0 0 0 0    4  0 0 0 0 0 0 0 0
   3  0 0 0 0 0 0 0 0    3  0 0 0 0 0 0 0 0    3  0 0 0 0 0 0 0 0
   2  1 1 1 1 1 1 1 1    2  0 0 0 0 0 0 0 0    2  1 1 1 1 1 1 1 1
   1  1 1 1 1 1 1 1 1    1  0 0 0 0 0 0 0 0    1  1 1 1 1 1 1 1 1
 */

/*
==================
constructor 
==================
*/
BitBoard::BitBoard() :
	pieces{ //white pieces 
		~NOTRANK_2,//wPawn
		0x0 | b1 | g1, //wKnight; 
		0x0 | c1 | f1, //wBishop
		0x0 | a1 | h1, //wRook
		0x0 | d1, //wQueen 
		0x0 | e1, //wKing 

		//black pieces 
		~NOTRANK_7, //bPawn 
		0x0 | b8 | g8, //bKnight 
		0x0 | c8 | f8, //bBishop
		0x0 | a8 | h8, //bRook
		0x0 | d8, //bQueen 
		0x0 | e8, //bKing 
	},

	occupancy{
		0x0 | ~NOTRANK_1 | ~NOTRANK_2, //white 
		0x0 | ~NOTRANK_8 | ~NOTRANK_7, //black 
		0x0 | ~NOTRANK_8 | ~NOTRANK_7 | ~NOTRANK_1 | ~NOTRANK_2, //both 
	},

	side(white),

	enpassant(64),

	castle(15),

	moveListIndex(0),
	moveListBegin(0), 
	moveListEnd(1)
{	}


/*
==================
debug 
==================
*/
void BitBoard::printBoard() {
	using namespace std;

	for (int rank = 0; rank < 8; ++rank) {
		cout << 8 - rank << "  ";
		for (int file = 0; file < 8; ++file) {
			//gets square
			int index = 8 * rank + file; 
			uint64_t square = position[index]; 

			//loops over all bitboards and checks for pieces 
			char pieceAscii = '.';
			for (int i = wPawn; i <= bKing; ++i) {
				if (this->pieces[i] & square) {
					pieceAscii = piecesLetter[i]; 
				}
			}

			//printing piece 
			cout << pieceAscii << ' '; 
		}
		cout << '\n'; 
	}
	cout << '\n'; 
	cout << "   a b c d e f g h " << '\n'; 

	//printing side to move 
	cout << "   side:     " << (!this->side ? "white" : "black") << '\n';

	//printing enpassent bit
	cout << "   enpassant: " << positionStr[this->enpassant] << '\n';

	//printing castling rights
	cout << "   castling: "; 
	
	cout << (this->castle & wkc ? 'K' : '-'); 
	cout << (this->castle & wqc ? 'Q' : '-'); 
	cout << (this->castle & bkc ? 'k' : '-'); 
	cout << (this->castle & bqc ? 'q' : '-'); 
	cout << '\n' << endl;
}

/*
reset board state to all zeros when possible 
side: white
enpassant: none 
castle: none
*/
void BitBoard::reset() {
	//reset pieces
	std::fill_n(this->pieces, 12, 0);

	//reset occupancies 
	std::fill_n(this->occupancy, 3, 0); 

	//reset side to white 
	this->side = white; 

	//reset enpassant 
	this->enpassant = 64; 

	//reset castling 
	this->castle = 0; 
}




void BitBoard::parseFen(std::string& fen) {
	//reset the current board state
	this->reset(); 

	//parse table 
	int index = 0; 
	int positionIndex = 0; 
	while (fen[index] != ' ') {

		uint64_t square = position[positionIndex]; 
		
		//black pieces 
		if ('a' <= fen[index] && fen[index] <= 'z') {
			//check which piece and initialize 
			switch (fen[index]) {
			case 'p': 
				this->pieces[bPawn] |= square; 
				break; 
			case 'n': 
				this->pieces[bKnight] |= square;
				break; 
			case 'b': 
				this->pieces[bBishop] |= square;
				break; 
			case 'r': 
				this->pieces[bRook] |= square; 
				break; 
			case 'q': 
				this->pieces[bQueen] |= square;
				break; 
			case 'k': 
				this->pieces[bKing] |= square;
				break; 
			}

			//increment index 
			++positionIndex; 

			//then set occupancy 
			this->occupancy[black] |= square; 
			this->occupancy[both] |= square; 
		}

		//white pieces 
		else if ('A' <= fen[index] && fen[index] <= 'Z') {
			//check which pieces and initialize
			switch (fen[index]) {
			case 'P':
				this->pieces[wPawn] |= square;
				break; 
			case 'N':
				this->pieces[wKnight] |= square;
				break; 
			case 'B':
				this->pieces[wBishop] |= square;
				break; 
			case 'R':
				this->pieces[wRook] |= square;
				break; 
			case 'Q':
				this->pieces[wQueen] |= square;
				break; 
			case 'K':
				this->pieces[wKing] |= square;
				break;
			}

			//increment index 
			++positionIndex;

			//then set occupancy 
			this->occupancy[white] |= square;
			this->occupancy[both] |= square;
		}

		//numbers 
		else if ('0' <= fen[index] && fen[index] <= '9') {
			int count = fen[index] - '0'; 
			positionIndex += count; 
		}
		++index; 
	}
	++index; 

	//initialize side to move 
	if (fen[index] == 'b') side = black;
	else side = white; 
	++index; 
	++index; 

	//castling rights 
	while (fen[index] != ' ') {
		switch (fen[index]) {
		case 'K': 
			this->castle |= wkc; 
			break; 
		case 'Q': 
			this->castle |= wqc;
			break; 
		case 'k': 
			this->castle |= bkc;
			break;
		case 'q': 
			this->castle |= bqc;
			break; 
		}
		++index; 
	}
	++index; 


	//enpassant square
	std::string enpassantSquare = ""; 
	while (fen[index] != ' ') {
		enpassantSquare += fen[index]; 
		++index; 
	}
	if (enpassantSquare.size() == 2) {
		int rank = (enpassantSquare[1] - '0');
		int file = enpassantSquare[0] - 'a'; 

		this->enpassant = 8 * (8 - rank) + file;
	}

}

/*
 ====================
 is attacked 
 ====================
 */

//attacked at position index by while on side to move 
bool BitBoard::isAttacked(int index, int side) {
	
	//attacked by pawn (black then white) 
	if (side == white && (pawnAttack[white][index] & pieces[bPawn])) return true; 
	if (side == black && (pawnAttack[black][index] & pieces[wPawn])) return true; 
	
	//knight attack 
	if (side == white && (knightAttack[index] & pieces[bKnight])) return true; 
	if (side == black && (knightAttack[index] & pieces[wKnight])) return true; 

	//bishop attack 
	if (side == white && (maskBishopAttack(index, occupancy[both]) & pieces[bBishop])) return true;
	if (side == black && (maskBishopAttack(index, occupancy[both]) & pieces[wBishop])) return true; 

	//rook attack 
	if (side == white && (maskRookAttack(index, occupancy[both]) & pieces[bRook])) return true; 
	if (side == black && (maskRookAttack(index, occupancy[both]) & pieces[wRook])) return true; 

	//queen attack 
	if (side == white && (maskQueenAttack(index, occupancy[both]) & pieces[bQueen])) return true; 
	if (side == black && (maskQueenAttack(index, occupancy[both]) & pieces[wQueen])) return true; 


	return false; 
}


uint64_t BitBoard::allAttacked(int side) {
	uint64_t attacked = 0x0; 

	for (int i = 0; i < 64; ++i) {
		if (isAttacked(i, side)) {
			setBit(attacked, position[i]); 
		}
	}

	return attacked; 
}


/*
 ====================
 move generation
 ====================
 */

void BitBoard::generateMove() {
	//source and target index
	int source, target; 

	//white side 
	if (side == white) {
		
		
		//white pawn moves 
		wPawnPush(); 
		wPawnDoublePush(); 
		
		
		//not sure can we generate moves 

		//if we and with the blockers 
		//we have the source squares for each piece 


	}

	//black side 
	else {
		bPawnPush();
		bPawnDoublePush(); 
	}


	return; 
}

/*
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
};
*/


uint64_t BitBoard::wPawnPush() {
	uint64_t pawnPosition = (pieces[wPawn] << 8) & ~occupancy[both];

	//iterate through the position and print 
	using namespace std; 
	for (int i = 0; i < 48; ++i) {
		if (pawnPosition & position[i]) {
			cout << "pawn push: " << positionStr[i + 8] << positionStr[i] << '\n'; 
		}
	}
	cout << flush; 
	return pawnPosition; 
}

uint64_t BitBoard::wPawnDoublePush() {
	uint64_t pawnPosition = ((pieces[wPawn] & ~NOTRANK_2) << 16) & ~occupancy[both] & ~(occupancy[both] << 8);

	//iterate through the position and print
	using namespace std; 
	for (int i = 0; i < 40; ++i) {
		if (pawnPosition & position[i]) {
			cout << "pawn doublepush: " << positionStr[i + 16] << positionStr[i] << '\n'; 
		}
	}
	cout << flush; 
	return pawnPosition; 
}

uint64_t BitBoard::wPawnCapture() {
	//white pawn capture 

	uint64_t captures = 0x0; 
	
	
	//iterate over all the captures 
	int numberOfPawns = numBit(pieces[wPawn]); 
	for (int i = 0; i < 64; ++i) {
		
		//pawn at position[i]
		if (pieces[wPawn] & position[i]) {
			//todo: bitwise or to get captured position 
		}
	}
	
}


uint64_t BitBoard::bPawnPush() {
	uint64_t pawnPosition = (pieces[bPawn] << 8) & ~occupancy[both];

	//iterate through the position and print 
	using namespace std;
	for (int i = 0; i < 48; ++i) {
		if (pawnPosition & position[i]) {
			cout << "pawn push: " << positionStr[i + 8] << positionStr[i] << '\n';
		}
	}
	cout << flush;
	return pawnPosition;
}

uint64_t BitBoard::bPawnDoublePush() {
	uint64_t pawnPosition = ((pieces[bPawn] & ~NOTRANK_2) << 16) & ~occupancy[both] & ~(occupancy[both] << 8);

	//iterate through the position and print
	using namespace std;
	for (int i = 0; i < 40; ++i) {
		if (pawnPosition & position[i]) {
			cout << "pawn doublepush: " << positionStr[i + 16] << positionStr[i] << '\n';
		}
	}
	cout << flush;
	return pawnPosition;
}


/*
 =======================
 encode and decode move
 =======================
 */


 /*
		  binary move bits                               hexidecimal constants

	0000 0000 0000 0000 0011 1111    source square       0x3f
	0000 0000 0000 1111 1100 0000    target square       0xfc0
	0000 0000 1111 0000 0000 0000    piece               0xf000
	0000 1111 0000 0000 0000 0000    promoted piece      0xf0000
	0001 0000 0000 0000 0000 0000    capture flag        0x100000
	0010 0000 0000 0000 0000 0000    double push flag    0x200000
	0100 0000 0000 0000 0000 0000    enpassant flag      0x400000
	1000 0000 0000 0000 0000 0000    castling flag       0x800000
 */


constexpr uint32_t BitBoard::encodeMove(int sourceIndex, int targetIndex, int pieces, int promotePieces, int capture, int doublePush, int enpassant, int castle) {
	uint32_t encodedMove = 0x0; 
	encodedMove |= sourceIndex; 
	encodedMove |= (targetIndex << 6); 
	encodedMove |= (pieces << 12); 
	encodedMove |= (promotePieces << 16); 
	encodedMove |= (doublePush << 17); 
	encodedMove |= (enpassant << 18); 
	encodedMove |= (castle << 19); 

	return encodedMove; 
}

void BitBoard::addMove(uint32_t move) {
	moveList[moveListIndex] = move;
	++moveListIndex; 
	++moveListEnd; 
}

void BitBoard::removeMove() {
	--moveListIndex; 
	--moveListEnd; 
}

void BitBoard::removeMoveAll() {
	moveListIndex = 0; 
	moveListEnd = 1; 
}






