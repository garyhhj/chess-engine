#include "BitBoard.h"
#include "macro.h"
#include "precalculation.h"
#include "debug.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>

//initialize chess board 
extern BitBoard board;
extern bool debug; 

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
	ply(0)
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

void BitBoard::printBoard(uint64_t bitBoard) {
	using namespace std;

	//print board 
	for (int rank = 0; rank < 8; ++rank) {
		cout << 8 - rank << "  ";
		for (int file = 0; file < 8; ++file) {
			int square = rank * 8 + file;

			cout << (getBit(bitBoard, square) ? " 1 " : " 0 ");
		}
		cout << '\n';
	}
	cout << '\n';
	cout << "    " << "a  b  c  d  e  f  g  h" << '\n';

	//print board as unsigned decimal 
	cout << "    " << "Bitboard: 0x" << hex << bitBoard << dec << '\n';
	cout << endl;
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
 move generation
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

	//king attack 
	if (side == white && (kingAttack[index] & pieces[bKing])) return true;
	if (side == black && (kingAttack[index] & pieces[wKing])) return true;

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


void BitBoard::generateMove(moveList& ml, uint32_t* moveList) {
	//white side 
	if (side == white) {
		wPawnPush(ml, moveList);
		wPawnDoublePush(ml, moveList);
		wPawnCapture(ml, moveList);

		wKnightMove(ml, moveList);
		wKingMove(ml, moveList);

		wBishopMove(ml, moveList);
		wRookMove(ml, moveList);
		wQueenMove(ml, moveList);

		wEnpassantMove(ml, moveList);
		wCastleMove(ml, moveList);
	}

	//black side 
	else {
		bPawnPush(ml, moveList);
		bPawnDoublePush(ml, moveList);
		bPawnCapture(ml, moveList);

		bKnightMove(ml, moveList);
		bKingMove(ml, moveList);

		bBishopMove(ml, moveList);
		bRookMove(ml, moveList);
		bQueenMove(ml, moveList);

		bEnpassantMove(ml, moveList);
		bCastleMove(ml, moveList);
	}

	return; 
}



/*
 ==========
 pawn
 ==========
 */

uint64_t BitBoard::wPawnPush(moveList& ml, uint32_t* moveList) {
	//pawn position after pawn push 
	uint64_t pawnPosition = (pieces[wPawn] << 8) & ~occupancy[both];

	//iterate through the position and print 
	using namespace std; 

	//pawn push with promotion
	for (int i = 0; i < 8; ++i) {
		if (pawnPosition & position[i]) {
			//cout << "pawn push promotion: " << positionStr[i + 8] << positionStr[i] << '\n'; 

			//encode move and push to movelist 
			addMove(ml, moveList, encodeMove(i + 8, i, wPawn, wQueen, 0, 0, 0, 0)); 
			addMove(ml, moveList, encodeMove(i + 8, i, wPawn, wRook, 0, 0, 0, 0));
			addMove(ml, moveList, encodeMove(i + 8, i, wPawn, wBishop, 0, 0, 0, 0));
			addMove(ml, moveList, encodeMove(i + 8, i, wPawn, wKnight, 0, 0, 0, 0));

		}
	}

	//pawn push without promotion
	for (int i = 8; i < 48; ++i) {
		if (pawnPosition & position[i]) {
			//cout << "pawn push: " << positionStr[i + 8] << positionStr[i] << '\n'; 
			
			//encode move and push to move list 
			addMove(ml, moveList, encodeMove(i + 8, i, wPawn, noPiece, 0, 0, 0, 0)); 
		}
	}
	return pawnPosition; 
}

uint64_t BitBoard::wPawnDoublePush(moveList& ml, uint32_t* moveList) {
	//pawn position after double pawn push 
	uint64_t pawnPosition = ((pieces[wPawn] & ~NOTRANK_2) << 16) & ~occupancy[both] & ~(occupancy[both] << 8);
 

	//iterate through the position and print
	using namespace std; 
	for (int i = 32; i < 40; ++i) {
		if (pawnPosition & position[i]) {
			//cout << "pawn doublepush: " << positionStr[i + 16] << positionStr[i] << '\n'; 

			//encode move and push to move list 
			addMove(ml, moveList, encodeMove(i + 16, i, wPawn, noPiece, 0, 1, 0, 0)); 
		}
	}
	return pawnPosition; 
}

uint64_t BitBoard::wPawnCapture(moveList& ml, uint32_t* moveList) {
	//white pawn capture 
	uint64_t captures = 0x0; 

	//captures with promotion 
	using namespace std; 
	for (int i = 8; i < 16; ++i) {
		uint64_t captures = pawnAttack[white][i] & occupancy[black]; 
		if ((position[i] & pieces[wPawn]) && captures) {

			int numBits = numBit(captures); 
			while (numBits--) {
				int index = lsbBitIndex(captures); 

				//cout << "pawn capture promotion: " << positionStr[i] << positionStr[index] << '\n'; 
				addMove(ml, moveList, encodeMove(i, index, wPawn, wQueen, 1, 0, 0, 0)); 
				addMove(ml, moveList, encodeMove(i, index, wPawn, wRook, 1, 0, 0, 0));
				addMove(ml, moveList, encodeMove(i, index, wPawn, wBishop, 1, 0, 0, 0));
				addMove(ml, moveList, encodeMove(i, index, wPawn, wKnight, 1, 0, 0, 0));

				captures &= captures - 1; 
			}
		}
	}

	//captures without promotion 
	for (int i = 16; i < 56; ++i) {
		uint64_t captures = pawnAttack[white][i] & occupancy[black]; 
		if ((position[i] & pieces[wPawn]) && captures) {

			int numBits = numBit(captures); 
			while (numBits--) {
				int index = lsbBitIndex(captures); 

				//cout << "pawn capture: " << positionStr[i] << positionStr[index] << '\n'; 
				addMove(ml, moveList, encodeMove(i, index, wPawn, noPiece, 1, 0, 0, 0)); 

				captures &= captures - 1; 
			}
		}
	}
	
	return captures; 
}



uint64_t BitBoard::bPawnPush(moveList& ml, uint32_t* moveList) {
	
	//pawn position after pawn push 
	uint64_t pawnPosition = (pieces[bPawn] >> 8) & ~occupancy[both];

	//iterate through the position and print 
	using namespace std;

	//pawn push with promotion
	for (int i = 56; i < 64; ++i) {
		if (pawnPosition & position[i]) {
			//cout << "pawn push promotion: " << positionStr[i - 8] << positionStr[i] << '\n';

			//encode move and push to movelist 
			addMove(ml, moveList, encodeMove(i - 8, i, bPawn, bQueen, 0, 0, 0, 0));
			addMove(ml, moveList, encodeMove(i - 8, i, bPawn, bRook, 0, 0, 0, 0));
			addMove(ml, moveList, encodeMove(i - 8, i, bPawn, bBishop, 0, 0, 0, 0));
			addMove(ml, moveList, encodeMove(i - 8, i, bPawn, bKnight, 0, 0, 0, 0));
		}
	}

	//pawn push without promotion
	for (int i = 16; i < 56; ++i) {
		if (pawnPosition & position[i]) {
			//cout << "pawn push: " << positionStr[i - 8] << positionStr[i] << '\n';

			//encode move and push to move list 
			addMove(ml, moveList, encodeMove(i - 8, i, bPawn, noPiece, 0, 0, 0, 0));
		}
	}
	return pawnPosition;
}

uint64_t BitBoard::bPawnDoublePush(moveList& ml, uint32_t* moveList) {
	//pawn position after double pawn push 
	uint64_t pawnPosition = ((pieces[bPawn] & ~NOTRANK_7) >> 16) & ~occupancy[both] & ~(occupancy[both] >> 8);


	//iterate through the position and print
	using namespace std;
	for (int i = 24; i < 32; ++i) {
		if (pawnPosition & position[i]) {
			//cout << "pawn doublepush: " << positionStr[i - 16] << positionStr[i] << '\n';

			//encode move and push to move list 
			addMove(ml, moveList, encodeMove(i - 16, i, bPawn, noPiece, 0, 1, 0, 0));
		}
	}
	return pawnPosition;
}

uint64_t BitBoard::bPawnCapture(moveList& ml, uint32_t* moveList) {
	//white pawn capture 
	uint64_t captures = 0x0;

	//captures with promotion 
	using namespace std;
	for (int i = 48; i < 56; ++i) {
		uint64_t captures = pawnAttack[black][i] & occupancy[white];
		if ((position[i] & pieces[bPawn]) && captures) {

			int numBits = numBit(captures);
			while (numBits--) {
				int index = lsbBitIndex(captures);

				//cout << "pawn capture promotion: " << positionStr[i] << positionStr[index] << '\n';
				addMove(ml, moveList, encodeMove(i, index, bPawn, bQueen, 1, 0, 0, 0));
				addMove(ml, moveList, encodeMove(i, index, bPawn, bRook, 1, 0, 0, 0));
				addMove(ml, moveList, encodeMove(i, index, bPawn, bBishop, 1, 0, 0, 0));
				addMove(ml, moveList, encodeMove(i, index, bPawn, bKnight, 1, 0, 0, 0));

				captures &= captures - 1;
			}
		}
	}

	//captures without promotion 
	for (int i = 8; i < 48; ++i) {
		uint64_t captures = pawnAttack[black][i] & occupancy[white];
		if ((position[i] & pieces[bPawn]) && captures) {

			int numBits = numBit(captures);
			while (numBits--) {
				int index = lsbBitIndex(captures);

				//cout << "pawn capture: " << positionStr[i] << positionStr[index] << '\n';
				addMove(ml, moveList, encodeMove(i, index, bPawn, noPiece, 1, 0, 0, 0));

				captures &= captures - 1;
			}
		}
	}

	return captures;
}


/*	
 ==========
 knight 
 ==========
 */


uint64_t BitBoard::wKnightMove(moveList& ml, uint32_t* moveList) {
	uint64_t moves = 0x0; 
	
	uint64_t knightOccupancy = pieces[wKnight]; 

	using namespace std; 
	//iterate through knights 
	while (knightOccupancy) {
		
		int sourceIndex = lsbBitIndex(knightOccupancy); 

		//iterate through knight moves with captures 
		uint64_t knightMoveCapture = knightAttack[sourceIndex] & occupancy[black]; 
		while (knightMoveCapture) {
			int targetIndex = lsbBitIndex(knightMoveCapture); 

			//cout << "knight capture: " << positionStr[sourceIndex] << positionStr[targetIndex] << '\n';
			addMove(ml, moveList, encodeMove(sourceIndex, targetIndex, wKnight, noPiece, 1, 0, 0, 0)); 

			knightMoveCapture &= knightMoveCapture - 1; 
		}

		//iterate through knight moves without captures 
		uint64_t knightMoveNoCapture = knightAttack[sourceIndex] & ~occupancy[both]; 
		while (knightMoveNoCapture) {
			int targetIndex = lsbBitIndex(knightMoveNoCapture); 

			//cout << "knight move: " << positionStr[sourceIndex] << positionStr[targetIndex] << '\n'; 
			addMove(ml, moveList, encodeMove(sourceIndex, targetIndex, wKnight, noPiece, 0, 0, 0, 0)); 

			knightMoveNoCapture &= knightMoveNoCapture - 1; 
		}


		knightOccupancy &= knightOccupancy - 1; 
	}

	return moves; 
}


uint64_t BitBoard::bKnightMove(moveList& ml, uint32_t* moveList) {
	uint64_t moves = 0x0;

	uint64_t knightOccupancy = pieces[bKnight];

	using namespace std;
	//iterate through knights 
	while (knightOccupancy) {

		int sourceIndex = lsbBitIndex(knightOccupancy);

		//iterate through knight moves with captures 
		uint64_t knightMoveCapture = knightAttack[sourceIndex] & occupancy[white];
		while (knightMoveCapture) {
			int targetIndex = lsbBitIndex(knightMoveCapture);

			//cout << "knight capture: " << positionStr[sourceIndex] << positionStr[targetIndex] << '\n';
			addMove(ml, moveList, encodeMove(sourceIndex, targetIndex, bKnight, noPiece, 1, 0, 0, 0));

			knightMoveCapture &= knightMoveCapture - 1;
		}

		//iterate through knight moves without captures 
		uint64_t knightMoveNoCapture = knightAttack[sourceIndex] & ~occupancy[both];
		while (knightMoveNoCapture) {
			int targetIndex = lsbBitIndex(knightMoveNoCapture);

			//cout << "knight move: " << positionStr[sourceIndex] << positionStr[targetIndex] << '\n';
			addMove(ml, moveList, encodeMove(sourceIndex, targetIndex, bKnight, noPiece, 0, 0, 0, 0));

			knightMoveNoCapture &= knightMoveNoCapture - 1;
		}


		knightOccupancy &= knightOccupancy - 1;
	}

	return moves;
}


/*
 ==========
 king
 ==========
 */

uint64_t BitBoard::wKingMove(moveList& ml, uint32_t* moveList) {
	//return if there is no king 
	if (!pieces[wKing]) return 0x0; 
	uint64_t moves = 0x0; 

	int sourceIndex = lsbBitIndex(pieces[wKing]); 

	//captures 
	using namespace std; 
	uint64_t kingMoveCapture = kingAttack[sourceIndex] & occupancy[black]; 
	while (kingMoveCapture) {
		int targetIndex = lsbBitIndex(kingMoveCapture); 

		//cout << "king capture: " << positionStr[sourceIndex] << positionStr[targetIndex] << '\n'; 
		addMove(ml, moveList, encodeMove(sourceIndex, targetIndex, wKing, noPiece, 1, 0, 0, 0)); 

		kingMoveCapture &= kingMoveCapture - 1; 
	}

	//non captures 
	uint64_t kingMoveNoCapture = kingAttack[sourceIndex] & ~occupancy[both]; 
	while (kingMoveNoCapture) {
		int targetIndex = lsbBitIndex(kingMoveNoCapture); 

		//cout << "king move: " << positionStr[sourceIndex] << positionStr[targetIndex] << '\n'; 
		addMove(ml, moveList, encodeMove(sourceIndex, targetIndex, wKing, noPiece, 0, 0, 0, 0)); 

		kingMoveNoCapture &= kingMoveNoCapture - 1; 
	}
	return moves; 
}

uint64_t BitBoard::bKingMove(moveList& ml, uint32_t* moveList) {
	//return if there is no king 
	if (!pieces[bKing]) return 0x0; 

	uint64_t moves = 0x0;

	int sourceIndex = lsbBitIndex(pieces[bKing]);

	//captures 
	using namespace std;
	uint64_t kingMoveCapture = kingAttack[sourceIndex] & occupancy[white];
	while (kingMoveCapture) {
		int targetIndex = lsbBitIndex(kingMoveCapture);

		//cout << "king capture: " << positionStr[sourceIndex] << positionStr[targetIndex] << '\n';
		addMove(ml, moveList, encodeMove(sourceIndex, targetIndex, bKing, noPiece, 1, 0, 0, 0));

		kingMoveCapture &= kingMoveCapture - 1;
	}

	//non captures 
	uint64_t kingMoveNoCapture = kingAttack[sourceIndex] & ~occupancy[both];
	while (kingMoveNoCapture) {
		int targetIndex = lsbBitIndex(kingMoveNoCapture);

		//cout << "king move: " << positionStr[sourceIndex] << positionStr[targetIndex] << '\n';
		addMove(ml, moveList, encodeMove(sourceIndex, targetIndex, bKing, noPiece, 0, 0, 0, 0));

		kingMoveNoCapture &= kingMoveNoCapture - 1;
	}
	return moves;
}


/*
 ==========
 bishop
 ==========
 */

uint64_t BitBoard::wBishopMove(moveList& ml, uint32_t* moveList) {
	uint64_t move = 0x0; 
	
	uint64_t bishopPositions = pieces[wBishop]; 

	using namespace std; 
	while (bishopPositions) {
		int index = lsbBitIndex(bishopPositions); 

		int magicIndex = ((occupancy[both] & bishopOccupancy[index]) * bishopMagicNum[index]) >> (64 - bishopOccupancyCount[index]);
		uint64_t bishopMoves = bishopAttack[index][magicIndex]; 

		//captures 
		uint64_t bishopMovesCaptures = bishopMoves & occupancy[black]; 
		while (bishopMovesCaptures) {
			int targetIndex = lsbBitIndex(bishopMovesCaptures); 

			//cout << "bishop capture: " << positionStr[index] << positionStr[targetIndex] << '\n'; 
			addMove(ml, moveList, encodeMove(index, targetIndex, wBishop, noPiece, 1, 0, 0, 0)); 

			bishopMovesCaptures &= bishopMovesCaptures - 1; 
		}

		//non captures 
		uint64_t bishopMovesNoCapture = bishopMoves & ~occupancy[both]; 
		while (bishopMovesNoCapture) {
			int targetIndex = lsbBitIndex(bishopMovesNoCapture); 

			//cout << "bishop move: " << positionStr[index] << positionStr[targetIndex] << '\n'; 
			addMove(ml, moveList, encodeMove(index, targetIndex, wBishop, noPiece, 0, 0, 0, 0)); 

			bishopMovesNoCapture &= bishopMovesNoCapture - 1; 
		}

		bishopPositions &= bishopPositions - 1; 
	}

	return move; 
}

uint64_t BitBoard::bBishopMove(moveList& ml, uint32_t* moveList) {
	uint64_t move = 0x0;

	uint64_t bishopPositions = pieces[bBishop];

	using namespace std;
	while (bishopPositions) {
		int index = lsbBitIndex(bishopPositions);

		int magicIndex = ((occupancy[both] & bishopOccupancy[index]) * bishopMagicNum[index]) >> (64 - bishopOccupancyCount[index]);
		uint64_t bishopMoves = bishopAttack[index][magicIndex];

		//captures 
		uint64_t bishopMovesCaptures = bishopMoves & occupancy[white];
		while (bishopMovesCaptures) {
			int targetIndex = lsbBitIndex(bishopMovesCaptures);

			//cout << "bishop capture: " << positionStr[index] << positionStr[targetIndex] << '\n';
			addMove(ml, moveList, encodeMove(index, targetIndex, bBishop, noPiece, 1, 0, 0, 0));

			bishopMovesCaptures &= bishopMovesCaptures - 1;
		}

		//non captures 
		uint64_t bishopMovesNoCapture = bishopMoves & ~occupancy[both];
		while (bishopMovesNoCapture) {
			int targetIndex = lsbBitIndex(bishopMovesNoCapture);

			//cout << "bishop move: " << positionStr[index] << positionStr[targetIndex] << '\n';
			addMove(ml, moveList, encodeMove(index, targetIndex, bBishop, noPiece, 0, 0, 0, 0));

			bishopMovesNoCapture &= bishopMovesNoCapture - 1;
		}

		bishopPositions &= bishopPositions - 1;
	}

	return move;
}


/*
 ==========
 rook
 ==========
 */

uint64_t BitBoard::wRookMove(moveList& ml, uint32_t* moveList) {
	uint64_t move = 0x0; 

	uint64_t rookPosition = pieces[wRook]; 

	using namespace std; 
	while (rookPosition) {
		int index = lsbBitIndex(rookPosition); 

		int magicIndex = ((occupancy[both] & rookOccupancy[index]) * rookMagicNum[index]) >> (64 - rookOccupancyCount[index]); 

		uint64_t rookMoves = rookAttack[index][magicIndex]; 
		
		//captures
		uint64_t rookMovesCapture = rookMoves & occupancy[black]; 
		while (rookMovesCapture) {
			int targetIndex = lsbBitIndex(rookMovesCapture); 

			//cout << "rook capture: " << positionStr[index] << positionStr[targetIndex] << '\n'; 
			addMove(ml, moveList, encodeMove(index, targetIndex, wRook, noPiece, 1, 0, 0, 0)); 

			rookMovesCapture &= rookMovesCapture - 1; 
		}

		//no captures 
		uint64_t rookMovesNoCapture = rookMoves & ~occupancy[both]; 
		while (rookMovesNoCapture) {
			int targetIndex = lsbBitIndex(rookMovesNoCapture); 

			//cout << "rook move: " << positionStr[index] << positionStr[targetIndex] << '\n'; 
			addMove(ml, moveList, encodeMove(index, targetIndex, wRook, noPiece, 0, 0, 0, 0)); 

			rookMovesNoCapture &= rookMovesNoCapture - 1; 
		}

		rookPosition &= rookPosition - 1; 
	}



	return move; 
}


uint64_t BitBoard::bRookMove(moveList& ml, uint32_t* moveList) {
	uint64_t move = 0x0;

	uint64_t rookPosition = pieces[bRook];

	using namespace std;
	while (rookPosition) {
		int index = lsbBitIndex(rookPosition);

		int magicIndex = ((occupancy[both] & rookOccupancy[index]) * rookMagicNum[index]) >> (64 - rookOccupancyCount[index]);

		uint64_t rookMoves = rookAttack[index][magicIndex];

		//captures
		uint64_t rookMovesCapture = rookMoves & occupancy[white];
		while (rookMovesCapture) {
			int targetIndex = lsbBitIndex(rookMovesCapture);

			//cout << "rook capture: " << positionStr[index] << positionStr[targetIndex] << '\n';
			addMove(ml, moveList, encodeMove(index, targetIndex, bRook, noPiece, 1, 0, 0, 0));

			rookMovesCapture &= rookMovesCapture - 1;
		}

		//no captures 
		uint64_t rookMovesNoCapture = rookMoves & ~occupancy[both];
		while (rookMovesNoCapture) {
			int targetIndex = lsbBitIndex(rookMovesNoCapture);

			//cout << "rook move: " << positionStr[index] << positionStr[targetIndex] << '\n';
			addMove(ml, moveList, encodeMove(index, targetIndex, bRook, noPiece, 0, 0, 0, 0));

			rookMovesNoCapture &= rookMovesNoCapture - 1;
		}

		rookPosition &= rookPosition - 1;
	}



	return move;
}


/*
 ==========
 queen
 ==========
 */

uint64_t BitBoard::wQueenMove(moveList& ml, uint32_t* moveList) {
	uint64_t move = 0x0; 

	uint64_t queenPosition = pieces[wQueen]; 
	using namespace std; 
	while (queenPosition) {
		
		int index = lsbBitIndex(queenPosition); 

		uint64_t queenMoves = maskQueenAttack(index, occupancy[both]); 

		//captures 
		uint64_t queenMovesCapture = queenMoves & occupancy[black]; 
		while (queenMovesCapture) {
			int targetIndex = lsbBitIndex(queenMovesCapture); 

			//cout << "queen capture: " << positionStr[index] << positionStr[targetIndex] << '\n'; 
			addMove(ml, moveList, encodeMove(index, targetIndex, wQueen, noPiece, 1, 0, 0, 0)); 

			queenMovesCapture &= queenMovesCapture - 1; 
		}

		//no captures 
		uint64_t queenMovesNoCaptures = queenMoves & ~occupancy[both]; 
		while (queenMovesNoCaptures) {
			int targetIndex = lsbBitIndex(queenMovesNoCaptures); 

			//cout << "queen move: " << positionStr[index] << positionStr[targetIndex] << '\n'; 
			addMove(ml, moveList, encodeMove(index, targetIndex, wQueen, noPiece, 0, 0, 0, 0)); 

			queenMovesNoCaptures &= queenMovesNoCaptures - 1; 
		}
		

		queenPosition &= queenPosition - 1; 
	}

	return move; 
}

uint64_t BitBoard::bQueenMove(moveList& ml, uint32_t* moveList) {
	uint64_t move = 0x0;

	uint64_t queenPosition = pieces[bQueen];
	using namespace std;
	while (queenPosition) {

		int index = lsbBitIndex(queenPosition);

		uint64_t queenMoves = maskQueenAttack(index, occupancy[both]);

		//captures 
		uint64_t queenMovesCapture = queenMoves & occupancy[white];
		while (queenMovesCapture) {
			int targetIndex = lsbBitIndex(queenMovesCapture);

			//cout << "queen capture: " << positionStr[index] << positionStr[targetIndex] << '\n';
			addMove(ml, moveList, encodeMove(index, targetIndex, bQueen, noPiece, 1, 0, 0, 0));

			queenMovesCapture &= queenMovesCapture - 1;
		}

		//no captures 
		uint64_t queenMovesNoCaptures = queenMoves & ~occupancy[both];
		while (queenMovesNoCaptures) {
			int targetIndex = lsbBitIndex(queenMovesNoCaptures);

			//cout << "queen move: " << positionStr[index] << positionStr[targetIndex] << '\n';
			addMove(ml, moveList, encodeMove(index, targetIndex, bQueen, noPiece, 0, 0, 0, 0));

			queenMovesNoCaptures &= queenMovesNoCaptures - 1;
		}


		queenPosition &= queenPosition - 1;
	}

	return move;
}

/*
 ==========
 enpassant
 ==========
 */

uint64_t BitBoard::wEnpassantMove(moveList& ml, uint32_t* moveList) {
	uint64_t move = 0x0; 

	using namespace std; 
	//enpassant square exists 
	if (enpassant != 64) {
		//targetIndex = enpassant; 

		uint64_t pawnSourcePositions = pawnAttack[black][enpassant] & pieces[wPawn]; 
		while (pawnSourcePositions) {
			int sourceIndex = lsbBitIndex(pawnSourcePositions); 

			//cout << "enpassant capture: " << positionStr[sourceIndex] << positionStr[enpassant] << '\n';
			addMove(ml, moveList, encodeMove(sourceIndex, enpassant, wPawn, noPiece, 1, 0, 1, 0)); 

			pawnSourcePositions &= pawnSourcePositions - 1; 
		}

	}

	return move; 
}


uint64_t BitBoard::bEnpassantMove(moveList& ml, uint32_t* moveList) {
	uint64_t move = 0x0;

	using namespace std;
	//enpassant square exists 
	if (enpassant != 64) {
		//targetIndex = enpassant; 

		uint64_t pawnSourcePositions = pawnAttack[white][enpassant] & pieces[bPawn];
		while (pawnSourcePositions) {
			int sourceIndex = lsbBitIndex(pawnSourcePositions);

			//cout << "enpassant capture: " << positionStr[sourceIndex] << positionStr[enpassant] << '\n';
			addMove(ml, moveList, encodeMove(sourceIndex, enpassant, bPawn, noPiece, 1, 0, 1, 0));
			
			pawnSourcePositions &= pawnSourcePositions - 1;
		}

	}

	return move;
}

/*
 ==========
 castle
 ==========
 */

//cannot castle while you are in check 
//can not castle through a check or land in a check 

//can not have pieces between the king or rook 

//rook and king can not move already - must be first move for both pieces 

uint64_t BitBoard::wCastleMove(moveList& ml, uint32_t* moveList) {
	uint64_t move = 0x0; 

	using namespace std; 
	//king side castle 
	if ((castle & wkc) &&						
		//e1 f1 and g1 not attacked 
		(!isAttacked(60, white) && !isAttacked(61, white) && !isAttacked(62, white)) &&
		//f1 and g1 not occupied 
		(f1 & ~occupancy[both]) && (g1 & ~occupancy[both])) {

		//cout << "castle: " << positionStr[60] << positionStr[62] << '\n'; 
		addMove(ml, moveList, encodeMove(60, 62, wKing, noPiece, 0, 0, 0, 1)); 

	}

	//queen side castle 
	if ((castle & wqc) &&
		//e1 d1 and c1 not attacked 
		(!isAttacked(60, white) && !isAttacked(59, white) && !isAttacked(58, white)) && 
		//d1 c1 and b1 are empty 
		(d1 & ~occupancy[both]) && (c1 & ~occupancy[both]) && (b1 & ~occupancy[both])
		){

		//cout << "castle: " << positionStr[60] << positionStr[58] << '\n';
		addMove(ml, moveList, encodeMove(60, 58, wKing, noPiece, 0, 0, 0, 1)); 

	}

	return move; 
}

uint64_t BitBoard::bCastleMove(moveList& ml, uint32_t* moveList) {
	uint64_t move = 0x0;

	using namespace std;
	//king side castle 
	if ((castle & bkc) &&
		//e8 f8 and g8 not attacked 
		(!isAttacked(4, black) && !isAttacked(5, black) && !isAttacked(6, black)) &&
		//f8 and g8 not occupied 
		(f8 & ~occupancy[both]) && (g8 & ~occupancy[both])) {

		//cout << "castle: " << positionStr[4] << positionStr[6] << '\n';
		addMove(ml, moveList, encodeMove(4, 6, bKing, noPiece, 0, 0, 0, 1));

	}

	//queen side castle 
	if ((castle & bqc) &&
		//e8 d8 and c8 not attacked 
		(!isAttacked(4, black) && !isAttacked(3, black) && !isAttacked(2, black)) &&
		//d8 c8 and b8 are empty 
		(d8 & ~occupancy[both]) && (c8 & ~occupancy[both]) && (b8 & ~occupancy[both])
		) {

		//cout << "castle: " << positionStr[4] << positionStr[2] << '\n';
		addMove(ml, moveList, encodeMove(4, 2, bKing, noPiece, 0, 0, 0, 1));

	}

	return move;
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

 /*
  =========
  encode 
  =========
  */

constexpr uint32_t BitBoard::encodeMove(int sourceIndex, int targetIndex, int piece, int promotePiece, int capture, int doublePush, int enpassant, int castle) {
	uint32_t encodedMove = 0x0; 
	encodedMove |= sourceIndex; 
	encodedMove |= (targetIndex << 6); 
	encodedMove |= (piece << 12); 
	encodedMove |= (promotePiece << 16); 
	encodedMove |= (capture << 20); 
	encodedMove |= (doublePush << 21); 
	encodedMove |= (enpassant << 22); 
	encodedMove |= (castle << 23); 

	return encodedMove; 
}

  /*
  =========
  decode
  =========
  */

constexpr int BitBoard::decodeMoveSourceIndex(uint32_t move) { return (move & 0x3f); }
constexpr int BitBoard::decodeMoveTargetIndex(uint32_t move) { return (move & 0xfc0) >> 6; }
constexpr int BitBoard::decodeMovePiece(uint32_t move) { return (move & 0xf000) >> 12; }
constexpr int BitBoard::decodeMovePromotePiece(uint32_t move) { return (move & 0xf0000) >> 16; }

constexpr int BitBoard::decodeMoveCapture(uint32_t move) { return (move & 0x100000) >> 20; }
constexpr int BitBoard::decodeMoveDoublePush(uint32_t move) { return (move & 0x200000) >> 21;  }
constexpr int BitBoard::decodeMoveEnpassant(uint32_t move) { return (move & 0x400000) >> 22; }
constexpr int BitBoard::decodeMoveCastle(uint32_t move) { return (move & 0x800000) >> 23;  }


  /*
  =============
   move list 
  ============
  */

void BitBoard::addMove(moveList& ml, uint32_t* moveList, uint32_t move) {
	moveList[ml.index] = move; 
	ml.index++;
}

void BitBoard::removeMove(moveList& ml) {
	ml.index--;
}

void BitBoard::removeMoveAll(moveList& ml) {
	ml.index = 0;
}

void BitBoard::printMove(uint32_t move) {
	using namespace std;
	cout << "move: ";

	

	//sourceIndex
	cout << "(SI)" << positionStr[decodeMoveSourceIndex(move)] << " ";

	//targetIndex 
	cout << "(TI)" << positionStr[decodeMoveTargetIndex(move)] << " ";

	//piece 
	cout << pieceStr[decodeMovePiece(move)] << " ";

	//padding 
	int padding = 8 - pieceStr[decodeMovePiece(move)].size();
	while (padding--) cout << " ";

	//promote piece 
	cout << pieceStr[decodeMovePromotePiece(move)] << " ";

	//padding 
	padding = 10 - pieceStr[decodeMovePromotePiece(move)].size();
	while (padding--) cout << " ";
	cout << "| ";

	//capture 
	if (decodeMoveCapture(move)) cout << "c ";
	else cout << "- ";

	//double push 
	if (decodeMoveDoublePush(move)) {
		cout << "dp ";
	}
	else cout << "-- ";

	//enpassant 
	if (decodeMoveEnpassant(move)) cout << "e ";
	else cout << "- ";

	//castle 
	if (decodeMoveCastle(move)) cout << "c";
	else cout << "-";

	cout << '\n';
}
void BitBoard::printMoveList(const moveList ml, const uint32_t* moveList) {
	int it = 0;
	while (it != ml.index) {
		std::cout << it << ": ";
		printMove(moveList[it]);
		++it;
	}

	std::cout << "number of moves: " << ml.index << '\n';
	std::cout << std::flush;
}




/*
 =====================
 preserve board state
 =====================
 */


void BitBoard::storeState(boardState& prevState) {
	//populate prevState member variable 
	std::copy_n(pieces, 12, prevState.pieces); 
	std::copy_n(occupancy, 3, prevState.occupancy); 

	prevState.side = this->side; 
	prevState.enpassant = this->enpassant; 
	prevState.castle = this->castle; 
}

void BitBoard::restoreState(boardState& prevState) {
	//populate class with info from prevState 
	std::copy_n(prevState.pieces, 12, pieces);
	std::copy_n(prevState.occupancy, 3, occupancy);

	this->side = prevState.side; 
	this->enpassant = prevState.enpassant; 
	this->castle = prevState.castle; 
}


/*
 =====================
 make move
 =====================
 */

bool isQuietMove() {
	return true; 
}

/*
false-> pseudo legal move
true -> legal move 
*/
bool BitBoard::makeMove(uint32_t move) {
	int dsourceIndex = decodeMoveSourceIndex(move);
	int dtargetIndex = decodeMoveTargetIndex(move);
	int dpiece = decodeMovePiece(move);
	int dpromotePiece = decodeMovePromotePiece(move);
	int dcapture = decodeMoveCapture(move);
	int ddoublePush = decodeMoveDoublePush(move);
	int denpassant = decodeMoveEnpassant(move);
	int dcastle = decodeMoveCastle(move);

	//cout move
	//using namespace std; 
	//cout << "printing move: "; 
	//printMove(move); 


	if (denpassant) {

		//move pawn to correct 
		pieces[dpiece] &= ~position[dsourceIndex];
		pieces[dpiece] |= position[dtargetIndex];

		//change occupancy 
		occupancy[side] &= ~position[dsourceIndex];
		occupancy[side] |= position[dtargetIndex];

		occupancy[both] &= ~position[dsourceIndex];
		occupancy[both] |= position[dtargetIndex];

		//remove piece captured 
		if (side == white) {
			pieces[bPawn] &= ~position[dtargetIndex + 8]; 

			occupancy[black] &= ~position[dtargetIndex + 8];
			occupancy[both] &= ~position[dtargetIndex + 8]; 
		}
		else {
			pieces[wPawn] &= ~position[dtargetIndex - 8]; 

			occupancy[white] &= ~position[dtargetIndex - 8]; 
			occupancy[both] &= ~position[dtargetIndex - 8]; 
		}

		//reset enpassan square 
		this->enpassant = 64; 
	}
	else if (dcapture) {
		//move piece to correct square 
		pieces[dpiece] &= ~position[dsourceIndex];
		pieces[dpiece] |= position[dtargetIndex];

		//change occupancy 
		occupancy[side] &= ~position[dsourceIndex];
		occupancy[side] |= position[dtargetIndex];

		occupancy[both] &= ~position[dsourceIndex];
		occupancy[both] |= position[dtargetIndex];
		
		//remove capture piece 
		if (side == white) {
			//remove black captured piece 
			occupancy[black] &= ~position[dtargetIndex];

			for (int i = bPawn; i <= bKing; ++i) {
				pieces[i] &= ~position[dtargetIndex]; 
			}
		}
		else {
			//remove white cpature piece 
			occupancy[white] &= ~position[dtargetIndex];

			for (int i = wPawn; i <= wKing; ++i) {
				pieces[i] &= ~position[dtargetIndex]; 
			}
		}
	}
	else if (ddoublePush) {
		//move piece to correct square 
		pieces[dpiece] &= ~position[dsourceIndex];
		pieces[dpiece] |= position[dtargetIndex];

		//change occupancy 
		occupancy[side] &= ~position[dsourceIndex];
		occupancy[side] |= position[dtargetIndex];

		occupancy[both] &= ~position[dsourceIndex];
		occupancy[both] |= position[dtargetIndex];
	}
	else if(dcastle) {

		int dcastleFlag; 
		//queen side 
		if (dtargetIndex < dsourceIndex) {
			dcastleFlag = (side == white ? wqc : bqc); 
		}
		//king side castle 
		else {
			dcastleFlag = (side == white ? wkc : bkc); 
		}
		
		//move the kings
		pieces[dpiece] &= ~position[dsourceIndex];
		pieces[dpiece] |= position[dtargetIndex];

		//change occupancy 
		occupancy[side] &= ~position[dsourceIndex];
		occupancy[side] |= position[dtargetIndex];

		occupancy[both] &= ~position[dsourceIndex];
		occupancy[both] |= position[dtargetIndex];

		//move the rooks 
		if (dcastleFlag == wqc) {
			pieces[wRook] &= ~position[A1]; 
			pieces[wRook] |= position[D1]; 

			occupancy[white] &= ~position[A1]; 
			occupancy[white] |= position[D1]; 

			occupancy[both] &= ~position[A1]; 
			occupancy[both] |= position[D1];
		}
		else if (dcastleFlag == bqc) {
			pieces[bRook] &= ~position[A8]; 
			pieces[bRook] |= position[D8]; 

			occupancy[black] &= ~position[A8]; 
			occupancy[black] |= position[D8]; 

			occupancy[both] &= ~position[A8]; 
			occupancy[both] |= position[D8]; 
		}
		else if (dcastleFlag == wkc) {
			pieces[wRook] &= ~position[H1]; 
			pieces[wRook] |= position[F1]; 

			occupancy[white] &= ~position[H1]; 
			occupancy[white] |= position[F1]; 

			occupancy[both] &= ~position[H1]; 
			occupancy[both] |= position[F1]; 
		}
		else {
			pieces[bRook] &= ~position[H8];
			pieces[bRook] |= position[F8]; 

			occupancy[black] &= ~position[H8]; 
			occupancy[black] |= position[F8]; 

			occupancy[both] &= ~position[H8]; 
			occupancy[both] |= position[F8]; 
		}
	
	}
	else {
		pieces[dpiece] &= ~position[dsourceIndex];
		pieces[dpiece] |= position[dtargetIndex];

		//change occupancy 
		occupancy[side] &= ~position[dsourceIndex];
		occupancy[side] |= position[dtargetIndex];

		occupancy[both] &= ~position[dsourceIndex];
		occupancy[both] |= position[dtargetIndex];
	}

	//flags for some of the different branches 
	
	if (ddoublePush) {
		this->enpassant = dtargetIndex + (side == white ? 8 : -8);
	}
	else if (dpromotePiece != noPiece) {
		pieces[dpiece] &= ~position[dtargetIndex];
		pieces[dpromotePiece] |= position[dtargetIndex];

		this->enpassant = 64; 
	}
	else {
		this->enpassant = 64; 
	}

	//return false if move is pseudo legal
	if ((side == white && isAttacked(lsbBitIndex(pieces[wKing]), white)) ||
		(side == black && isAttacked(lsbBitIndex(pieces[bKing]), black))) {
		return false;
	}

	//castle flags 
	castle &= castleRights[dsourceIndex]; 
	castle &= castleRights[dtargetIndex]; 

	//promotions 

	//sides 
	if (this->side == white) this->side = black;
	else this->side = white; 



	return true; 
}



/*
 =====================
 UCI 
 =====================
 */

//parses moves eg.(e7e8q)
uint32_t BitBoard::parseMove(const std::string& move) {

	//parse move for sourceIndex, targetIndex, promotionPiece 
	int sourceIndex = (8 - (move[1] - '0')) * 8 + (move[0] - 'a');
	int targetIndex = (8 - (move[3] - '0')) * 8 + (move[2] - 'a');

	int promotionPiece = noPiece; 
	if (move.size() == 5) {
		if (move[4] == 'b') promotionPiece = (side == white ? wBishop : bBishop);
		else if (move[4] == 'n') promotionPiece = (side == white ? wKnight : bKnight);
		else if (move[4] == 'r') promotionPiece = (side == white ? wRook : bRook);
		else if (move[4] == 'q') promotionPiece = (side == white ? wQueen : bQueen); 
	}

	moveList ml; 
	uint32_t movelist[256]; 
	board.generateMove(ml, movelist);

	for (int i = 0; i < ml.index; ++i) {
		//matching move 
		int mlSourceIndex = board.decodeMoveSourceIndex(movelist[i]);
		int mlTargetIndex = board.decodeMoveTargetIndex(movelist[i]); 
		int mlPromotionPiece = board.decodeMovePromotePiece(movelist[i]); 

		if (mlSourceIndex == sourceIndex && mlTargetIndex == targetIndex && mlPromotionPiece == promotionPiece) {
			
			//if move is legal 
			boardState state; 
			board.storeState(state); 
			if (board.makeMove(movelist[i])) {
				board.restoreState(state);
				return movelist[i]; 
			}
		}

	}

	//return false (illegal move or move doesn't exist) 
	return 0; 
}

/*
	parses UCI positions commands

	Example UCI commands to init position on chess board

	// init start position
	position startpos

	// init start position and make the moves on chess board
	position startpos moves e2e4 e7e5

	// init position from FEN string
	position fen r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1

	// init position from fen string and make moves on chess board
	position fen r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1 moves e2a6 e8g8
*/
void BitBoard::parsePosition(const std::string& command) {
	using namespace std; 
	stringstream ss(command);
	string word; 
	while (ss >> word) {

		//if word is position
		if (word == "position") {
			continue; 
		}

		//if word is starting position
		else if (word == "startpos") {
			string fenStart = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1 ";
			board.parseFen(fenStart);
		}

		//if word is "fen"
		else if (word == "fen") {
			
			//initialize fen strin g
			string fen = ""; 
			int count = 6; 
			while (count--) {
				ss >> word;
				fen += word;
				fen += " ";
			}
			
			board.parseFen(fen); 
		}

		//if word is "moves" 
		else if (word == "moves") {
			while (ss >> word) {
				//verify legal move and execute moves 
				uint32_t move = board.parseMove(word); 
				if (move) {
					board.makeMove(move); 
				}
			}
		}
	}

	cout << '\n'; 
	board.printBoard();
}

/*
	parse UCI "go" command

	Example UCI commands to make engine search for the best move

	// fixed depth search
	go depth 64
*/
void BitBoard::parseGo(const std::string& command) {
	using namespace std; 

	//default search depth 
	int depth = 1; 

	stringstream ss(command);
	
	string word; 
	while (ss >> word) {
		if (word == "go") {
			continue; 
		}

		else if (word == "depth") {
			ss >> depth; 
		}
	}
	

	//search position depth 
	//cout << "searching depth of " << depth << '\n'; 
	
	
	searchPosition(depth);
}

void BitBoard::uciLoop() {
	using namespace std; 

	//print engine info
	cout << "id name meowmi\n"; 
	cout << "id name yarh\n"; 
	cout << "uciok\n"; 
	cout << flush; 

	//flushes buffer 
	cout << flush; 

	//game loop 
	while (true) {
		//flushes buffer 
		cout << flush; 

		//gets input 
		string line; 
		getline(cin, line); 
		
		stringstream command(line); 

		//gets first word of input 
		string word; 
		command >> word; 


		//parse "isready"
		if (word == "isready") {
			cout << "readyok\n"; 
			continue; 
		}

		//parse "position"
		else if (word == "position") {
			parsePosition(line); 
		}

		//parse "ucinewgame" 
		else if (word == "ucinewgame") {
			parsePosition("position startpos"); 
		}

		//parse "go"
		else if (word == "go") {
			parseGo(line); 
		}

		//parse "quit"
		else if (word == "quit") {
			//exit main loop 
			break; 
		}

		//parse "uci"
		else if (word == "uci") {
			//print engine info 
			cout << "id name meowmi\n";
			cout << "id name yarh\n";
			cout << "uciok\n";
		}
		
	}
}



/*
 =====================
 search position
 =====================
 */

void BitBoard::sortMoveDescending(moveList ml, uint32_t* movelist) {

	//print result before sorting 
	for (int i = 0; i < ml.index; ++i) {
		printMoveAlgebraicNotation(movelist[i]);
		std::cout << " score: " << getMoveScore(movelist[i]) << "\n";
	}
	using namespace std; 
	cout << "\n";

	std::sort(movelist, movelist + ml.index, [](uint32_t a, uint32_t b) {
		return board.getMoveScore(a) > board.getMoveScore(b);
		});
	
	//print to check result 
	for (int i = 0; i < ml.index; ++i) {
		printMoveAlgebraicNotation(movelist[i]); 
		std::cout << " score: " << getMoveScore(movelist[i]) << "\n"; 
	}
}


int BitBoard::getMoveScore(uint32_t move) {
	using namespace std; 

	int sourcePiece = decodeMovePiece(move);
	int targetPiece = noPiece; 
	//move is capture 
	if (decodeMoveCapture(move)) {
		//get targetPiece
		int targetIndex = decodeMoveTargetIndex(move);
		for (int piece = wPawn; piece <= bKing; ++piece) {
			


			if (pieces[piece] & position[targetIndex]) {
				targetPiece = piece; 
				break; 
			}
		}


		//enpassant piece 
		if (targetPiece == noPiece) {
			targetPiece = (side == white ? bPawn : wPawn); 
		}

		//get score 
		return mvvLva[sourcePiece][targetPiece]; 
	}
	//non capture moves 
	else {

	}

	return 0; 
}


/*
assumes no legal moves available 
return checkmate or stalemate score 
*/
int BitBoard::getCheckmateStalemateScore() {
	//index for king 
	int kingIndex = lsbBitIndex(pieces[(side == white ? wKing : bKing)]);

	//check mate 
	if (isAttacked(kingIndex, side)) {
		return -49000 + ply;
	}
	//stalemate 
	else {
		return 0;
	}
}

//prints move in algebraic notation ex. "e2e4"
void BitBoard::printMoveAlgebraicNotation(uint32_t move) {
	using namespace std; 

	//prints source and target index 
	cout << positionStr[decodeMoveSourceIndex(move)]; 
	cout << positionStr[decodeMoveTargetIndex(move)]; 

	//prints promotion piece 
	if (decodeMovePromotePiece(move) != noPiece) {
		int piece = decodeMovePromotePiece(move); 
		if (piece == wKnight || piece == bKnight) cout << "n";
		else if (piece == wBishop || piece == bBishop) cout << "b";
		else if (piece == wRook || piece == bRook) cout << "r";
		else if (piece == wQueen || piece == bQueen) cout << "q"; 
	}
}


//outputs best move after searching a certain "depth"
void BitBoard::searchPosition(int depth) {
	using namespace std; 

	//search for best move 
	int score = negamaxSearch(-50000, 50000, depth, 0); 

	//cout info to gui 
	cout << "info "; 
	cout << "depth " << depth << " "; 
	cout << "score cp " << score << "\n"; 

	//cout final decision of move to gui 
	cout << "bestmove ";
	printMoveAlgebraicNotation(bestMove); 
	cout << "\n"; 
}

/*
* alpha is min score 
* beta is max score 
* depth is depth of search 
*/
int BitBoard::negamaxSearch(int alpha, int beta, int depth, uint32_t move) {
	
	//base case 
	if (depth == 0) {


		int score = quiescenceSearch(alpha, beta);

		if (debug) {
			using namespace std; 
			cout << "searching move: "; 
			printMoveAlgebraicNotation(move); 
			cout << " score: " << score << endl; 
		}


		return score; 
	}

	uint32_t bestMoveSofar; 
	int oldAlpha = alpha; 
	int legalMoveCount = 0; 

	//store current board state	
	boardState state; 
	storeState(state); 

	//generate moves 
	moveList ml; 
	uint32_t movelist[256]; 
	generateMove(ml, movelist); 

	//iterate through moves 
	for (int i = 0; i < ml.index; ++i) {

		//skip illegal moves 
		if (!makeMove(movelist[i])) {
			restoreState(state); 
			continue; 
		}
		restoreState(state); 

		//increment half move counter and legalMoveCount
		++ply; 
		++legalMoveCount; 

		//search child node
		makeMove(movelist[i]);

		if (debug) {
			using namespace std;
			cout << "searching move: ";
			printMoveAlgebraicNotation(movelist[i]);
		}
		
		int score = -negamaxSearch(-beta, -alpha, depth - 1, movelist[i]);
		
		


		//restore state 
		restoreState(state); 
		--ply; 
		
		//reject or keep branch/moves 

		//node (move) fails high 
		if (score >= beta) {
			return beta; 
		}

		//found better move 
		if (score > alpha) {
			
			//PV node 
			alpha = score;

			if (ply == 0)
				bestMoveSofar = movelist[i];
		}
	}

	//debug 
	if (debug) {
		using namespace std; 
		cout << endl; 

		//parent node and child nodes 
		//parent node
		printMoveAlgebraicNotation(move);
		cout << ": "; 

		//child node 
		for (int i = 0; i < ml.index; ++i) {

			//skip illegal moves 
			if (!makeMove(movelist[i])) {
				restoreState(state);
				continue;
			}
			restoreState(state);

			printMoveAlgebraicNotation(movelist[i]); 
			cout << ", "; 

		}
		cout << "\n"; 

		//prints alpha and beta values 
		cout << "alpha(min): " << alpha << " beta(max): " << beta << " oldAlpha: " << oldAlpha << endl;

		cout << endl; 
	}

	//checkmate or stalemate 
	if (!legalMoveCount) {
		return getCheckmateStalemateScore(); 
	}
	

	//update move
	if (oldAlpha != alpha) {
		bestMove = bestMoveSofar;
	}


	//return min value 
	return alpha; 
}

//quiescence search
int BitBoard::quiescenceSearch(int alpha, int beta) {
	int standPat = evaluate(); 
	if (standPat >= beta) {
		return beta; 
	}
	if (standPat > alpha) {
		alpha = standPat; 
	}

	boardState state; 
	storeState(state); 

	//generate moves 
	moveList ml; 
	uint32_t movelist[256];
	generateMove(ml, movelist); 

	//iterate through moves 
	for (int i = 0; i < ml.index; ++i) {

		//skip illegal moves 
		if (!makeMove(movelist[i])) {
			restoreState(state);
			continue;
		}
		restoreState(state);

		//skip non capture moves
		if (!decodeMoveCapture(movelist[i])) {
			restoreState(state); 
			continue; 
		}
		restoreState(state); 
		

		//increment half move counter and legalMoveCount
		++ply;

		//search child node
		makeMove(movelist[i]);

		if (debug) {
			using namespace std;
			cout << "searching move: ";
			printMoveAlgebraicNotation(movelist[i]);
		}

		int score = -quiescenceSearch(-beta, -alpha);


		//restore state 
		restoreState(state);
		--ply;

		//reject or keep branch/moves 

		//node (move) fails high 
		if (score >= beta) {
			return beta;
		}

		//found better move 
		if (score > alpha) {
			//PV node 
			alpha = score;
		}
	}

	return alpha; 
}


/*
 =====================
 evaluate position
 =====================
 */


//evaluate score for material 
int BitBoard::evaluateMaterial() {
	int score = 0; 

	//iterate through piece and sum their material score 
	for (int piece = wPawn; piece <= bKing; ++piece) {
		score += (materialScore[piece] * numBit(pieces[piece]));
	}

	return score; 
}

//evaluate score for piece positioning 
int BitBoard::evaluatePosition() {
	
	using namespace std; 
	int wScore = 0; 
	int bScore = 0; 
	uint64_t piecePosition; 

	//wPawn position scores 
	piecePosition = pieces[wPawn]; 
	while (piecePosition) {
		wScore += wpawnPositionScore[lsbBitIndex(piecePosition)]; 
		piecePosition &= piecePosition - 1; 
	}

	//wKnight position scores 
	piecePosition = pieces[wKnight];
	while (piecePosition) {
		wScore += wknightPositionScore[lsbBitIndex(piecePosition)];
		piecePosition &= piecePosition - 1;
	}

	//wBishop position scores 
	piecePosition = pieces[wBishop];
	while (piecePosition) {
		wScore += wbishopPositionScore[lsbBitIndex(piecePosition)];
		piecePosition &= piecePosition - 1;
	}

	//wRook position scores 
	piecePosition = pieces[wRook];
	while (piecePosition) {
		wScore += wrookPositionScore[lsbBitIndex(piecePosition)];
		piecePosition &= piecePosition - 1;
	}

	//wKing position scores 
	piecePosition = pieces[wKing];
	while (piecePosition) {
		wScore += wkingPositionScore[lsbBitIndex(piecePosition)];
		piecePosition &= piecePosition - 1;
	}


	//bPawn position scores 
	piecePosition = pieces[bPawn];
	while (piecePosition) {
		bScore += bpawnPositionScore[lsbBitIndex(piecePosition)];
		piecePosition &= piecePosition - 1;
	}

	//bKnight position scores 
	piecePosition = pieces[bKnight];
	while (piecePosition) {
		bScore += bknightPositionScore[lsbBitIndex(piecePosition)];
		piecePosition &= piecePosition - 1;
	}

	//bBishop position scores 
	piecePosition = pieces[bBishop];
	while (piecePosition) {
		bScore += bbishopPositionScore[lsbBitIndex(piecePosition)];
		piecePosition &= piecePosition - 1;
	}

	//bRook position scores 
	piecePosition = pieces[bRook];
	while (piecePosition) {
		bScore += brookPositionScore[lsbBitIndex(piecePosition)];
		piecePosition &= piecePosition - 1;
	}

	//bKing position scores 
	piecePosition = pieces[bKing];
	while (piecePosition) {
		bScore += bkingPositionScore[lsbBitIndex(piecePosition)];
		piecePosition &= piecePosition - 1;
	}

	return wScore - bScore; 
}

int BitBoard::evaluate() {
	
	int score = 0;
	
	//call evaluation functions 
	score += evaluateMaterial(); 
	score += evaluatePosition(); 


	//return evaluation based on side 
	return (side == white ? score : -score); 
}
