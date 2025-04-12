//
// Created by Zach Gillette on 4/11/25.
//

#include "Sliding_Pieces.h"

#ifndef ROOKS_H
#define ROOKS_H

class Rooks : public Sliding_Pieces {
private:
  PieceType type;
  uint64_t bitboard;
public:

  // Constructors
  Rooks() = delete;
  Rooks(PieceType type);
  Rooks(PieceType type, uint64_t bitboard);

  // Move generation
  std::array<uint64_t, Sliding_Pieces::MAX_NUM_ROOK_MOVES> all_moves(uint64_t empty_squares, uint64_t empty_pieces);

};



#endif // ROOKS_H
