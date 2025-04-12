//
// Created by Zach Gillette on 4/11/25.
//

#include "Bitboard/include/Queens.h"

Queens::Queens(PieceType t) : type(t) {
  // Initialize for white
  if(type == WHITE_QUEEN) {
    bitboard = 0x0000000000000010;
  }
  else if(type == BLACK_QUEEN) {
    bitboard = 0x1000000000000000;
  }
  else {
    // This should never happen.
    std::cout << "ZACH ERROR: Initialized Queen Incorrectly." << std::endl;
    bitboard = 0x0;
  }
}
Queens::Queens(PieceType t, uint64_t bb) : type(t), bitboard(bb) {}

std::array<uint64_t, Sliding_Pieces::MAX_NUM_QUEEN_MOVES> Queens::all_moves(uint64_t empty_squares, uint64_t enemy_squares) {

  std::array<uint64_t, Sliding_Pieces::MAX_NUM_QUEEN_MOVES> to_ret;

  std::array<uint64_t, Sliding_Pieces::MAX_NUM_ROOK_MOVES> rook_moves = Sliding_Pieces::all_rook_moves(bitboard, empty_squares, enemy_squares);
  std::array<uint64_t, Sliding_Pieces::MAX_NUM_BISHOP_MOVES> bishop_moves = Sliding_Pieces::all_bishop_moves(bitboard, empty_squares, enemy_squares);

  // Copy data
  std::copy(rook_moves.begin(), rook_moves.end(), to_ret.begin());
  std::copy(bishop_moves.begin(), bishop_moves.end(), to_ret.begin() + Sliding_Pieces::MAX_NUM_ROOKS);
  return to_ret;
}
