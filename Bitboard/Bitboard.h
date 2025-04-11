#ifndef BITBOARD_H
#define BITBOARD_H

#include <cstdint>
#include <iostream>
#include <string>

class Bitboard {
private:
public:
  // Constructors: no args
  Bitboard();

  // Complement bitboard
  static uint64_t complement(uint64_t bitboard);

  // Least-significant bit of bitboard
  static uint64_t get_lsb(uint64_t bitboard);

  // Removes the Least-significant bit of bitboard
  static uint64_t remove_lsb(uint64_t bitboard);

  // To string
  static std::string to_string(uint64_t bitboard);
  static std::string reverse_to_string(uint64_t bitboard);

  // Friend function: cout for bitboards
  static void print(uint64_t bitboard);

  // Bitboard transformations
  static uint64_t flip_diagonal(uint64_t bitboard);
  static uint64_t reverse(uint64_t bitboard);

};

#endif // BITBOARD_H
