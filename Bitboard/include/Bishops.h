//
// Created by Zach Gillette on 4/11/25.
//

#include "Sliding_Pieces.h"

#ifndef BISHOPS_H
#define BISHOPS_H

class Bishops : public Sliding_Pieces {
private:
  PieceType type;
  uint64_t bitboard;
public:

  // Constructors
  Bishops() = delete;
  Bishops(PieceType type);
  Bishops(PieceType type, uint64_t bitboard);

  // Move generation
  std::array<uint64_t, Sliding_Pieces::MAX_NUM_BISHOP_MOVES> all_moves(uint64_t empty_squares, uint64_t enemy_squares);

};



#endif // BISHOPS_H
