#pragma once
#include <vector>
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

class BitBoard {
public:
	//pieces on bitboard 
    uint64_t pieces[12]; 

    //occupancies 
    uint64_t occupancy[3]; 

    //side to move 
    int side; 

    //en passant 
    int enpassant; 

    //castling right (bit encoded) 
    uint32_t castle; 

    //move list 
    uint32_t moveList[100000]; 
    int moveListIndex; 
    int moveListBegin; 
    int moveListEnd; 

	//constructor 
	BitBoard();
	void printBoard();

    //fen string 
    void parseFen(std::string& fen); 

    //reset board state; 
    void reset(); 




    /*
     ====================
     move generation
     ====================
     */

     //is attacked
    bool isAttacked(int index, int side);
    uint64_t allAttacked(int side);

    void generateMove();

    //pawn 
    //change from uint64_t to void? 
    uint64_t wPawnPush(); 
    uint64_t wPawnDoublePush();
    uint64_t wPawnCapture(); 

    uint64_t bPawnPush(); 
    uint64_t bPawnDoublePush(); 
    uint64_t bPawnCapture(); 

    //knight
    uint64_t wKnightMove(); 
    uint64_t bKnightMove(); 
    
    //king 
    uint64_t wKingMove(); 
    uint64_t bKingMove(); 

    //bishop 
    uint64_t wBishopMove(); 
    uint64_t bBishopMove(); 
    
    //rook 
    uint64_t wRookMove(); 
    uint64_t bRookMove();

    //queen 
    uint64_t wQueenMove(); 
    uint64_t bQueenMove(); 

    //enpassant 
    uint64_t wEnpassantMove(); 
    uint64_t bEnpassantMove(); 
    
    //castle 
    uint64_t wCastleMove(); 
    uint64_t bCastleMove(); 

    /*
     =======================
     encode and decode move
     =======================
     */

    constexpr uint32_t encodeMove(int sourceIndex, int targetIndex, int piece, int promotePiece, int capture, int doublePush, int enpassant, int castle);
    constexpr int decodeMoveSourceIndex(uint32_t move);
    constexpr int decodeMoveTargetIndex(uint32_t move);
    constexpr int decodeMovePiece(uint32_t move);
    constexpr int decodeMovePromotePiece(uint32_t move);
    constexpr int decodeMoveCapture(uint32_t move); 
    constexpr int decodeMoveDoublePush(uint32_t move);
    constexpr int decodeMoveEnpassant(uint32_t move);
    constexpr int decodeMoveCastle(uint32_t move);



    void addMove(uint32_t move); 
    void removeMove(); 
    void removeMoveAll(); 

    void printMove(uint32_t move);
    void printMoveList(); 

};

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

    //no piece 
    noPiece = 0xf,
};
*/
