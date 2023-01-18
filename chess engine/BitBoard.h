#pragma once
#include <vector>
#include <iostream>
#include <string>

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

struct boardState {
    uint64_t pieces[12]; 
    uint64_t occupancy[3]; 
    
    int side; 
    int enpassant; 
    uint32_t castle; 
};

struct moveList {
    int begin = 0; 
    int index = 0; 
    int end = 0;

};

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

    void generateMove(moveList& ml, uint32_t* moveList);

    //pawn 
    //change from uint64_t to void? 
    uint64_t wPawnPush(moveList& ml, uint32_t* moveList);
    uint64_t wPawnDoublePush(moveList& ml, uint32_t* moveList);
    uint64_t wPawnCapture(moveList& ml, uint32_t* moveList); 

    uint64_t bPawnPush(moveList& ml, uint32_t* moveList);
    uint64_t bPawnDoublePush(moveList& ml, uint32_t* moveList);
    uint64_t bPawnCapture(moveList& ml, uint32_t* moveList);

    //knight
    uint64_t wKnightMove(moveList& ml, uint32_t* moveList);
    uint64_t bKnightMove(moveList& ml, uint32_t* moveList);
    
    //king 
    uint64_t wKingMove(moveList& ml, uint32_t* moveList);
    uint64_t bKingMove(moveList& ml, uint32_t* moveList);

    //bishop 
    uint64_t wBishopMove(moveList& ml, uint32_t* moveList);
    uint64_t bBishopMove(moveList& ml, uint32_t* moveList);
    
    //rook 
    uint64_t wRookMove(moveList& ml, uint32_t* moveList);
    uint64_t bRookMove(moveList& ml, uint32_t* moveList);

    //queen 
    uint64_t wQueenMove(moveList& ml, uint32_t* moveList);
    uint64_t bQueenMove(moveList& ml, uint32_t* moveList);

    //enpassant 
    uint64_t wEnpassantMove(moveList& ml, uint32_t* moveList);
    uint64_t bEnpassantMove(moveList& ml, uint32_t* moveList);
    
    //castle 
    uint64_t wCastleMove(moveList& ml, uint32_t* moveList);
    uint64_t bCastleMove(moveList& ml, uint32_t* moveList);

    /*
     =======================
     move list 
     =======================
     */

    void addMove(moveList& ml, uint32_t* moveList, uint32_t move);
    void removeMove(moveList& ml);
    void removeMoveAll(moveList& ml);
    void printMove(uint32_t move);
    void printMoveList(const moveList ml, const uint32_t* moveList);

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


    /*
     =====================
     preserve board state
     =====================
     */
    
    void storeState(boardState& state); 
    void restoreState(boardState& state);


    /*
     =====================
     make move 
     =====================
     */

    bool makeMove(uint32_t move);

    /*
     =====================
     GUI
     =====================
     */

    uint32_t parseMove(const std::string& move); 
};


//initialize chess

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
