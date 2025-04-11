//
// Created by Zach Gillette on 4/11/25.
//

#include "Bishops.h"

Bishops::Bishops(PieceType t) : type(t) {
  // Initialize for white
  if(type == WHITE_BISHOP) {
    bitboard = 0x0000000000000024;
  }
  else if(type == BLACK_BISHOP) {
    bitboard = 0x2400000000000000;
  }
  else {
    // This should never happen.
    std::cout << "ZACH ERROR: Initialized Bishop Incorrectly." << std::endl;
    bitboard = 0x0;
  }
}
Bishops::Bishops(PieceType t, uint64_t bb) : type(t), bitboard(bb) {}

std::array<uint64_t, Sliding_Pieces::MAX_NUM_BISHOP_MOVES> Bishops::all_moves(uint64_t empty_squares, uint64_t enemy_squares) {

  return Sliding_Pieces::all_bishop_moves(bitboard, empty_squares, enemy_squares);

}
