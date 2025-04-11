#include <iostream>
#include "Bitboard/Bitboard.h"

int main() {
  // Create a Bitboard instance.

  Bitboard bitboard1(0x00a500000000a500);
  std::cout << "before flip" << std::endl;
  Bitboard::print(bitboard1.get_board());

  std::cout << "after flip" << std::endl;
  Bitboard::print(Bitboard::complement(bitboard1.get_board()));

  bitboard1.set_board(Bitboard::remove_lsb(bitboard1.get_board()));

  Bitboard::print(bitboard1.get_board());



  return 0;
}
