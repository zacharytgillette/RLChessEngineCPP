//
// Created by Zach Gillette on 4/11/25.
//

#include "Sliding_Pieces.h"

#ifndef QUEENS_H
#define QUEENS_H

class Queens : public Sliding_Pieces {
private:
  PieceType type;
  uint64_t bitboard;
public:

  // TODO: fix this
  static const int p = MAX_NUM_QUEEN_MOVES;

  // Constructors
  Queens() = delete;
  Queens(PieceType type);
  Queens(PieceType type, uint64_t bitboard);

  // Move generation
  std::array<uint64_t, Sliding_Pieces::MAX_NUM_QUEEN_MOVES> all_moves(uint64_t empty_squares, uint64_t enemy_squares);

};



#endif // QUEENS_H
