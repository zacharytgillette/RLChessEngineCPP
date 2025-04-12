//
// Created by Zach Gillette on 4/10/25.
//

#ifndef PIECES_H
#define PIECES_H

#include "Bitboard.h"

// Enumerate colors, piece types
enum Colors {
  WHITE = 1,
  BLACK = -1
};

enum PieceType {
  NONE = -1,
  WHITE_PAWN = 0,
  WHITE_KNIGHT = 1,
  WHITE_BISHOP = 2,
  WHITE_ROOK = 3,
  WHITE_QUEEN = 4,
  WHITE_KING = 5,
  BLACK_PAWN = 6,
  BLACK_KNIGHT = 7,
  BLACK_BISHOP = 8,
  BLACK_ROOK = 9,
  BLACK_QUEEN = 10,
  BLACK_KING = 11
};

class Pieces : public Bitboard {
private:
  PieceType type;
public:

  // Constructors
  Pieces();
  Pieces(PieceType type);

  // Functions
  PieceType flip_piece_type(PieceType type);

};

#endif // PIECES_H
