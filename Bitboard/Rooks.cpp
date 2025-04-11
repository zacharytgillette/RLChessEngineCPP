//
// Created by Zach Gillette on 4/11/25.
//

#include "Rooks.h"

Rooks::Rooks(PieceType t) : type(t) {

  // Initialize for white
  if(type == WHITE_ROOK) {
    bitboard = 0x0000000000000081;
  }
  else if(type == BLACK_ROOK) {
    bitboard = 0x8100000000000000;
  }
  else {
    // This should never happen.
    std::cout << "ZACH ERROR: Initialized Rook Incorrectly." << std::endl;
    bitboard = 0x0;
  }

}
Rooks::Rooks(PieceType t, uint64_t bb) : type(t), bitboard(bb) {}

std::array<uint64_t, Sliding_Pieces::MAX_NUM_ROOK_MOVES> Rooks::all_moves(uint64_t empty_squares, uint64_t enemy_squares) {

  return Sliding_Pieces::all_rook_moves(bitboard, empty_squares, enemy_squares);

}
