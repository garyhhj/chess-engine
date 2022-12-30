#include "BitBoard.h"
#include "macro.h"
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

	enpassant(-1), 

	castle(0)
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
	if (this->castle & wkc) cout << "wkc, "; 
	if (this->castle & wqc) cout << "wqc, "; 
	if (this->castle & bkc) cout << "bkc, "; 
	if (this->castle & bqc) cout << "bqc, "; 
	cout << endl; 
}





