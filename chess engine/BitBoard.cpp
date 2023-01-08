#include "BitBoard.h"
#include "macro.h"
#include "precalculation.h"
#include "debug.h"
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
	moveListEnd(0)
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


void BitBoard::generateMove() {
	//source and target index
	int source, target; 

	//white side 
	if (side == white) {
		
		
		//white pawn moves 
		wPawnPush(); 
		wPawnDoublePush(); 
		wPawnCapture();

		wKnightMove();
		wKingMove();

		wBishopMove(); 	
		wRookMove(); 
		wQueenMove();

		wEnpassantMove(); 
		wCastleMove(); 
	}

	//black side 
	else {
		bPawnPush();
		bPawnDoublePush();
		bPawnCapture(); 

		bKnightMove();
		bKingMove();

		bBishopMove();
		bRookMove();
		bQueenMove();

		bEnpassantMove();
		bCastleMove();
	}

	return; 
}



/*
 ==========
 pawn
 ==========
 */

uint64_t BitBoard::wPawnPush() {
	//pawn position after pawn push 
	uint64_t pawnPosition = (pieces[wPawn] << 8) & ~occupancy[both];

	//iterate through the position and print 
	using namespace std; 

	//pawn push with promotion
	for (int i = 0; i < 8; ++i) {
		if (pawnPosition & position[i]) {
			//cout << "pawn push promotion: " << positionStr[i + 8] << positionStr[i] << '\n'; 

			//todo: function to determine what promotion if necessary 
			
			//encode move and push to movelist 
			addMove(encodeMove(i + 8, i, wPawn, wQueen, 0, 0, 0, 0)); 
		}
	}

	//pawn push without promotion
	for (int i = 8; i < 48; ++i) {
		if (pawnPosition & position[i]) {
			//cout << "pawn push: " << positionStr[i + 8] << positionStr[i] << '\n'; 
			
			//encode move and push to move list 
			addMove(encodeMove(i + 8, i, wPawn, noPiece, 0, 0, 0, 0)); 
		}
	}
	return pawnPosition; 
}

uint64_t BitBoard::wPawnDoublePush() {
	//pawn position after double pawn push 
	uint64_t pawnPosition = ((pieces[wPawn] & ~NOTRANK_2) << 16) & ~occupancy[both] & ~(occupancy[both] << 8);
 

	//iterate through the position and print
	using namespace std; 
	for (int i = 32; i < 40; ++i) {
		if (pawnPosition & position[i]) {
			//cout << "pawn doublepush: " << positionStr[i + 16] << positionStr[i] << '\n'; 

			//encode move and push to move list 
			addMove(encodeMove(i + 16, i, wPawn, noPiece, 0, 0, 0, 0)); 
		}
	}
	return pawnPosition; 
}

uint64_t BitBoard::wPawnCapture() {
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
				addMove(encodeMove(i, index, wPawn, wQueen, 1, 0, 0, 0)); 

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
				addMove(encodeMove(i, index, wPawn, noPiece, 1, 0, 0, 0)); 

				captures &= captures - 1; 
			}
		}
	}
	
	return captures; 
}



uint64_t BitBoard::bPawnPush() {
	//pawn position after pawn push 
	uint64_t pawnPosition = (pieces[bPawn] >> 8) & ~occupancy[both];

	//iterate through the position and print 
	using namespace std;

	//pawn push with promotion
	for (int i = 56; i < 64; ++i) {
		if (pawnPosition & position[i]) {
			//cout << "pawn push promotion: " << positionStr[i - 8] << positionStr[i] << '\n';

			//todo: function to determine what promotion if necessary 

			//encode move and push to movelist 
			addMove(encodeMove(i - 8, i, bPawn, bQueen, 0, 0, 0, 0));
		}
	}

	//pawn push without promotion
	for (int i = 16; i < 56; ++i) {
		if (pawnPosition & position[i]) {
			//cout << "pawn push: " << positionStr[i - 8] << positionStr[i] << '\n';

			//encode move and push to move list 
			addMove(encodeMove(i - 8, i, bPawn, noPiece, 0, 0, 0, 0));
		}
	}
	return pawnPosition;
}

uint64_t BitBoard::bPawnDoublePush() {
	//pawn position after double pawn push 
	//there is a bug here 
	uint64_t pawnPosition = ((pieces[bPawn] & ~NOTRANK_7) >> 16) & ~occupancy[both] & ~(occupancy[both] >> 8);


	//iterate through the position and print
	using namespace std;
	for (int i = 24; i < 32; ++i) {
		if (pawnPosition & position[i]) {
			//cout << "pawn doublepush: " << positionStr[i - 16] << positionStr[i] << '\n';

			//encode move and push to move list 
			addMove(encodeMove(i - 16, i, bPawn, noPiece, 0, 0, 0, 0));
		}
	}
	return pawnPosition;
}

uint64_t BitBoard::bPawnCapture() {
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
				addMove(encodeMove(i, index, bPawn, bQueen, 1, 0, 0, 0));

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
				addMove(encodeMove(i, index, bPawn, noPiece, 1, 0, 0, 0));

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


uint64_t BitBoard::wKnightMove() {
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
			addMove(encodeMove(sourceIndex, targetIndex, wKnight, noPiece, 1, 0, 0, 0)); 

			knightMoveCapture &= knightMoveCapture - 1; 
		}

		//iterate through knight moves without captures 
		uint64_t knightMoveNoCapture = knightAttack[sourceIndex] & ~occupancy[both]; 
		while (knightMoveNoCapture) {
			int targetIndex = lsbBitIndex(knightMoveNoCapture); 

			//cout << "knight move: " << positionStr[sourceIndex] << positionStr[targetIndex] << '\n'; 
			addMove(encodeMove(sourceIndex, targetIndex, wKnight, noPiece, 0, 0, 0, 0)); 

			knightMoveNoCapture &= knightMoveNoCapture - 1; 
		}


		knightOccupancy &= knightOccupancy - 1; 
	}

	return moves; 
}


uint64_t BitBoard::bKnightMove() {
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
			addMove(encodeMove(sourceIndex, targetIndex, bKnight, noPiece, 1, 0, 0, 0));

			knightMoveCapture &= knightMoveCapture - 1;
		}

		//iterate through knight moves without captures 
		uint64_t knightMoveNoCapture = knightAttack[sourceIndex] & ~occupancy[both];
		while (knightMoveNoCapture) {
			int targetIndex = lsbBitIndex(knightMoveNoCapture);

			//cout << "knight move: " << positionStr[sourceIndex] << positionStr[targetIndex] << '\n';
			addMove(encodeMove(sourceIndex, targetIndex, bKnight, noPiece, 0, 0, 0, 0));

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

uint64_t BitBoard::wKingMove() {
	uint64_t moves = 0x0; 

	int sourceIndex = lsbBitIndex(pieces[wKing]); 

	//captures 
	using namespace std; 
	uint64_t kingMoveCapture = kingAttack[sourceIndex] & occupancy[black]; 
	while (kingMoveCapture) {
		int targetIndex = lsbBitIndex(kingMoveCapture); 

		//cout << "king capture: " << positionStr[sourceIndex] << positionStr[targetIndex] << '\n'; 
		addMove(encodeMove(sourceIndex, targetIndex, wKing, noPiece, 1, 0, 0, 0)); 

		kingMoveCapture &= kingMoveCapture - 1; 
	}

	//non captures 
	uint64_t kingMoveNoCapture = kingAttack[sourceIndex] & ~occupancy[both]; 
	while (kingMoveNoCapture) {
		int targetIndex = lsbBitIndex(kingMoveNoCapture); 

		//cout << "king move: " << positionStr[sourceIndex] << positionStr[targetIndex] << '\n'; 
		addMove(encodeMove(sourceIndex, targetIndex, wKing, noPiece, 0, 0, 0, 0)); 

		kingMoveNoCapture &= kingMoveNoCapture - 1; 
	}
	return moves; 
}

uint64_t BitBoard::bKingMove() {
	uint64_t moves = 0x0;

	int sourceIndex = lsbBitIndex(pieces[bKing]);

	//captures 
	using namespace std;
	uint64_t kingMoveCapture = kingAttack[sourceIndex] & occupancy[white];
	while (kingMoveCapture) {
		int targetIndex = lsbBitIndex(kingMoveCapture);

		//cout << "king capture: " << positionStr[sourceIndex] << positionStr[targetIndex] << '\n';
		addMove(encodeMove(sourceIndex, targetIndex, bKing, noPiece, 1, 0, 0, 0));

		kingMoveCapture &= kingMoveCapture - 1;
	}

	//non captures 
	uint64_t kingMoveNoCapture = kingAttack[sourceIndex] & ~occupancy[both];
	while (kingMoveNoCapture) {
		int targetIndex = lsbBitIndex(kingMoveNoCapture);

		//cout << "king move: " << positionStr[sourceIndex] << positionStr[targetIndex] << '\n';
		addMove(encodeMove(sourceIndex, targetIndex, bKing, noPiece, 0, 0, 0, 0));

		kingMoveNoCapture &= kingMoveNoCapture - 1;
	}
	return moves;
}


/*
 ==========
 bishop
 ==========
 */

uint64_t BitBoard::wBishopMove() {
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
			addMove(encodeMove(index, targetIndex, wBishop, noPiece, 1, 0, 0, 0)); 

			bishopMovesCaptures &= bishopMovesCaptures - 1; 
		}

		//non captures 
		uint64_t bishopMovesNoCapture = bishopMoves & ~occupancy[both]; 
		while (bishopMovesNoCapture) {
			int targetIndex = lsbBitIndex(bishopMovesNoCapture); 

			//cout << "bishop move: " << positionStr[index] << positionStr[targetIndex] << '\n'; 
			addMove(encodeMove(index, targetIndex, wBishop, noPiece, 0, 0, 0, 0)); 

			bishopMovesNoCapture &= bishopMovesNoCapture - 1; 
		}

		bishopPositions &= bishopPositions - 1; 
	}

	return move; 
}

uint64_t BitBoard::bBishopMove() {
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
			addMove(encodeMove(index, targetIndex, bBishop, noPiece, 1, 0, 0, 0));

			bishopMovesCaptures &= bishopMovesCaptures - 1;
		}

		//non captures 
		uint64_t bishopMovesNoCapture = bishopMoves & ~occupancy[both];
		while (bishopMovesNoCapture) {
			int targetIndex = lsbBitIndex(bishopMovesNoCapture);

			//cout << "bishop move: " << positionStr[index] << positionStr[targetIndex] << '\n';
			addMove(encodeMove(index, targetIndex, bBishop, noPiece, 0, 0, 0, 0));

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

uint64_t BitBoard::wRookMove() {
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
			addMove(encodeMove(index, targetIndex, wRook, noPiece, 1, 0, 0, 0)); 

			rookMovesCapture &= rookMovesCapture - 1; 
		}

		//no captures 
		uint64_t rookMovesNoCapture = rookMoves & ~occupancy[both]; 
		while (rookMovesNoCapture) {
			int targetIndex = lsbBitIndex(rookMovesNoCapture); 

			//cout << "rook move: " << positionStr[index] << positionStr[targetIndex] << '\n'; 
			addMove(encodeMove(index, targetIndex, wRook, noPiece, 0, 0, 0, 0)); 

			rookMovesNoCapture &= rookMovesNoCapture - 1; 
		}

		rookPosition &= rookPosition - 1; 
	}



	return move; 
}


uint64_t BitBoard::bRookMove() {
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
			addMove(encodeMove(index, targetIndex, bRook, noPiece, 1, 0, 0, 0));

			rookMovesCapture &= rookMovesCapture - 1;
		}

		//no captures 
		uint64_t rookMovesNoCapture = rookMoves & ~occupancy[both];
		while (rookMovesNoCapture) {
			int targetIndex = lsbBitIndex(rookMovesNoCapture);

			//cout << "rook move: " << positionStr[index] << positionStr[targetIndex] << '\n';
			addMove(encodeMove(index, targetIndex, bRook, noPiece, 0, 0, 0, 0));

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

uint64_t BitBoard::wQueenMove() {
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
			addMove(encodeMove(index, targetIndex, wQueen, noPiece, 1, 0, 0, 0)); 

			queenMovesCapture &= queenMovesCapture - 1; 
		}

		//no captures 
		uint64_t queenMovesNoCaptures = queenMoves & ~occupancy[both]; 
		while (queenMovesNoCaptures) {
			int targetIndex = lsbBitIndex(queenMovesNoCaptures); 

			//cout << "queen move: " << positionStr[index] << positionStr[targetIndex] << '\n'; 
			addMove(encodeMove(index, targetIndex, wQueen, noPiece, 0, 0, 0, 0)); 

			queenMovesNoCaptures &= queenMovesNoCaptures - 1; 
		}
		

		queenPosition &= queenPosition - 1; 
	}

	return move; 
}

uint64_t BitBoard::bQueenMove() {
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
			addMove(encodeMove(index, targetIndex, bQueen, noPiece, 1, 0, 0, 0));

			queenMovesCapture &= queenMovesCapture - 1;
		}

		//no captures 
		uint64_t queenMovesNoCaptures = queenMoves & ~occupancy[both];
		while (queenMovesNoCaptures) {
			int targetIndex = lsbBitIndex(queenMovesNoCaptures);

			//cout << "queen move: " << positionStr[index] << positionStr[targetIndex] << '\n';
			addMove(encodeMove(index, targetIndex, bQueen, noPiece, 0, 0, 0, 0));

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

uint64_t BitBoard::wEnpassantMove() {
	uint64_t move = 0x0; 

	using namespace std; 
	//enpassant square exists 
	if (enpassant != 64) {
		//targetIndex = enpassant; 

		uint64_t pawnSourcePositions = pawnAttack[black][enpassant] & pieces[wPawn]; 
		while (pawnSourcePositions) {
			int sourceIndex = lsbBitIndex(pawnSourcePositions); 

			//cout << "enpassant capture: " << positionStr[sourceIndex] << positionStr[enpassant] << '\n';
			addMove(encodeMove(sourceIndex, enpassant, wPawn, noPiece, 1, 0, 1, 0)); 

			pawnSourcePositions &= pawnSourcePositions - 1; 
		}

	}

	return move; 
}


uint64_t BitBoard::bEnpassantMove() {
	uint64_t move = 0x0;

	using namespace std;
	//enpassant square exists 
	if (enpassant != 64) {
		//targetIndex = enpassant; 

		uint64_t pawnSourcePositions = pawnAttack[white][enpassant] & pieces[bPawn];
		while (pawnSourcePositions) {
			int sourceIndex = lsbBitIndex(pawnSourcePositions);

			//cout << "enpassant capture: " << positionStr[sourceIndex] << positionStr[enpassant] << '\n';
			addMove(encodeMove(sourceIndex, enpassant, bPawn, noPiece, 1, 0, 1, 0));
			
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

uint64_t BitBoard::wCastleMove() {
	uint64_t move = 0x0; 

	using namespace std; 
	//king side castle 
	if ((castle & wkc) &&						
		//e1 f1 and g1 not attacked 
		(!isAttacked(60, white) && !isAttacked(61, white) && !isAttacked(62, white)) &&
		//f1 and g1 not occupied 
		(f1 & ~occupancy[both]) && (g1 & ~occupancy[both])) {

		//cout << "castle: " << positionStr[60] << positionStr[62] << '\n'; 
		addMove(encodeMove(60, 62, wKing, noPiece, 0, 0, 0, 1)); 

	}

	//queen side castle 
	if ((castle & wqc) &&
		//e1 d1 and c1 not attacked 
		(!isAttacked(60, white) && !isAttacked(59, white) && !isAttacked(58, white)) && 
		//d1 c1 and b1 are empty 
		(d1 & ~occupancy[both]) && (c1 & ~occupancy[both]) && (b1 & ~occupancy[both])
		){

		//cout << "castle: " << positionStr[60] << positionStr[58] << '\n';
		addMove(encodeMove(60, 58, wKing, noPiece, 0, 0, 0, 1)); 

	}

	return move; 
}

uint64_t BitBoard::bCastleMove() {
	uint64_t move = 0x0;

	using namespace std;
	//king side castle 
	if ((castle & bkc) &&
		//e8 f8 and g8 not attacked 
		(!isAttacked(4, white) && !isAttacked(5, white) && !isAttacked(6, white)) &&
		//f8 and g8 not occupied 
		(f8 & ~occupancy[both]) && (g8 & ~occupancy[both])) {

		//cout << "castle: " << positionStr[4] << positionStr[6] << '\n';
		addMove(encodeMove(4, 6, wKing, noPiece, 0, 0, 0, 1));

	}

	//queen side castle 
	if ((castle & bqc) &&
		//e8 d8 and c8 not attacked 
		(!isAttacked(4, white) && !isAttacked(3, white) && !isAttacked(2, white)) &&
		//d8 c8 and b8 are empty 
		(d8 & ~occupancy[both]) && (c8 & ~occupancy[both]) && (b8 & ~occupancy[both])
		) {

		//cout << "castle: " << positionStr[4] << positionStr[2] << '\n';
		addMove(encodeMove(4, 2, wKing, noPiece, 0, 0, 0, 1));

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
  =========
  other 
  =========
  */


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

void BitBoard::printMove(uint32_t move) {
	//use sstream to format before outputting 

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
	if (decodeMoveDoublePush(move)) cout << "dp ";
	else cout << "-- ";

	//enpassant 
	if (decodeMoveEnpassant(move)) cout << "e ";
	else cout << "- "; 

	//castle 
	if (decodeMoveCastle(move)) cout << "c";
	else cout << "-"; 

	cout << '\n';

}

void BitBoard::printMoveList() {
	int it = 0; 
	while (it != moveListEnd) {
		std::cout << it << ": ";
		printMove(moveList[it]); 
		++it; 
	}

	std::cout << "number of moves: " <<  moveListEnd << '\n';
	std::cout << std::flush; 
}



/*
 =====================
 preserve board state
 =====================
 */


void BitBoard::storeState() {
	//populate prevState member variable 
	std::copy_n(pieces, 12, prevState.pieces); 
	std::copy_n(occupancy, 3, prevState.occupancy); 

	prevState.side = this->side; 
	prevState.enpassant = this->enpassant; 
	prevState.castle = this->castle; 
}

void BitBoard::restoreState() {
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

void BitBoard::makeMove(uint32_t move) {
	//something about quiet move idk 
	//quiet move(no capture, no promotion, no checks) 

	int dsourceIndex = decodeMoveSourceIndex(move);
	int dtargetIndex = decodeMoveTargetIndex(move);
	int dpiece = decodeMovePiece(move);
	int dpromotePiece = decodeMovePromotePiece(move);
	int dcapture = decodeMoveCapture(move);
	int ddoublePush = decodeMoveDoublePush(move);
	int denpassant = decodeMoveEnpassant(move);
	int dcastle = decodeMoveCastle(move);

	//cout the information 
	using namespace std;
	cout << "Make move: " << move << " meowww move info: " << endl; 
	printMove(move); 

	if (side == white) cout << "white" << endl;
	else cout << "black " << endl; 


	if (denpassant) {
		cout << "enpassant" << endl; 
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
			pieces[wPawn] &= ~position[dtargetIndex + 8]; 

			occupancy[white] &= ~position[dtargetIndex - 8]; 
			occupancy[both] &= ~position[dtargetIndex - 8]; 
		}

		//reset enpassan square 
		this->enpassant = 64; 
	}
	else if (dcapture) {
		cout << "calling dcapture: " << endl; 
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
		cout << "calling ddoublePush: " << endl;
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

		int castleFlag; 
		//queen side 
		if (dtargetIndex < dsourceIndex) {
			castleFlag = (side == white ? wqc : bqc); 
		}
		//king side castle 
		else {
			castleFlag = (side == white ? wkc : bkc); 
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
		if (castleFlag == wqc) {
			pieces[wRook] &= ~position[a1]; 
			pieces[wRook] |= position[d1]; 

			occupancy[white] &= ~position[a1]; 
			occupancy[white] |= position[d1]; 

			occupancy[both] &= ~position[a1]; 
			occupancy[both] |= position[d1];
		}
		else if (castleFlag == bqc) {
			pieces[bRook] &= ~position[a8]; 
			pieces[bRook] |= position[d8]; 

			occupancy[black] &= ~position[a8]; 
			occupancy[white] |= position[d8]; 

			occupancy[both] &= ~position[a8]; 
			occupancy[both] |= position[d8]; 
		}
		else if (castleFlag == wkc) {
			pieces[wRook] &= ~position[h1]; 
			pieces[wRook] |= position[f1]; 

			occupancy[white] &= ~position[h1]; 
			occupancy[white] |= position[f1]; 

			occupancy[both] &= ~position[h1]; 
			occupancy[both] |= position[f1]; 
		}
		else {
			pieces[bRook] &= ~position[h8];
			pieces[bRook] |= position[f8]; 

			occupancy[black] &= ~position[h8]; 
			occupancy[black] |= position[f8]; 

			occupancy[both] &= ~position[h8]; 
			occupancy[both] |= position[f8]; 
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

	//flags for different branches 
	if (denpassant) {
		this->enpassant = 64; 
	}
	else if (dcapture) {
		this->enpassant = 64; 
	}
	else if (ddoublePush) {
		this->enpassant = dtargetIndex + (side == white ? 8 : -8);
	}
	else if(dcastle) {
		this->enpassant = 64; 
		if (side == white) castle &= 0b0011;
		else castle &= 0b1100; 
	}
	else {
		this->enpassant = 64; 
	}

	//castle flags 
	if (dpiece == wRook && dsourceIndex == A1) castle &= 0b1011; 
	else if (dpiece == wRook && dsourceIndex == H1) castle &= 0b0111; 
	else if (dpiece == bRook && dsourceIndex == A8) castle &= 0b1110; 
	else if (dpiece == bRook && dsourceIndex == H8) castle &= 0b1101;
	else if (dpiece == wKing) castle &= 0b0011; 
	else if (dpiece == bKing) castle &= 0b1100; 

	printBoard(); 

}