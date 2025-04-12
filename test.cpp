//
// Created by Zach Gillette on 4/12/25.
//
#include "Bitboard/include/Bitboard.h"
#include "Bitboard/include/Queens.h"
#include "Bitboard/include/Sliding_Pieces.h"
#include "iostream"

int main() {

  uint64_t w = 0x0000000000000010;
  uint64_t b = 0x1000000000000000;

//  w = Bitboard::flip_diagonal(w);
  b = Bitboard::flip_diagonal(b);

  Bitboard::print(w, "white diagonal");
  Bitboard::print(b, "black diagonal");

  w = Sliding_Pieces::get_vertical_moves(w, 0xffffffffffffffff, 0x0000000000000000);
  Bitboard::print(w, "white ray");

  Queens queen(WHITE_QUEEN, 0x0000000010000000);

  Bitboard::print(0x0000000010000000, "queen loc");

  uint64_t all = 0x0;
  std::array<uint64_t, Queens::p> qmoves = queen.all_moves(0xffffffffffffffff, 0x0);

  for(int i=0; i<Queens::p; i++) {
      all |= qmoves[i];
  }

  Bitboard::print(all, "queen moves");



  return 0;
}