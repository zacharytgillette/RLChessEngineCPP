//
// Created by Zach Gillette on 4/10/25.
//

#include "Bitboard/include/Bitboard.h"

Bitboard::Bitboard() { }

uint64_t Bitboard::complement(uint64_t bitboard) {
  return ~bitboard;
}

uint64_t Bitboard::get_lsb(uint64_t bitboard) {
  return bitboard & -bitboard;
}

uint64_t Bitboard::remove_lsb(uint64_t bitboard) {
  return bitboard & ~(get_lsb(bitboard));
}

std::string Bitboard::to_string(uint64_t bitboard) {
  std::string to_ret(64, '0');
  for (int i = 63; i >= 0; i--) {
    to_ret[i] = (bitboard & 1) ? '1' : '0';
    bitboard >>= 1;
  }
  return to_ret;
}

std::string Bitboard::reverse_to_string(uint64_t bitboard) {
  std::string to_ret(64, '0');
  for (int i = 63; i >= 0; i--) {
    to_ret[63-i] = (bitboard & 1) ? '1' : '0';
    bitboard >>= 1;
  }
  return to_ret;
}

void Bitboard::print(uint64_t bitboard) {
  Bitboard::print(bitboard, "");
}

void Bitboard::print(uint64_t bitboard, std::string s) {

  if(bitboard == 0x0) {
    std::cout << "\nEMPTY BITBOARD\n";
    return;
  }

  std::string bitboard_string = Bitboard::to_string(bitboard);

  std::cout << '\n';

  if(!std::equal(s.begin(), s.end(), "")) {
    std::cout << s << std::endl;
  }

  for (int i = 0; i < 8; i++) {
    std::cout << bitboard_string.substr(i * 8, 4) << " "
       << bitboard_string.substr(i * 8 + 4, 4) << '\n';
  }
  std::cout << '\n';
}


// Shout out ChatGPT for this one
uint64_t Bitboard::flip_diagonal(uint64_t bb) {
  uint64_t t;
  const uint64_t k1 = 0x5500550055005500ULL;
  const uint64_t k2 = 0x3333000033330000ULL;
  const uint64_t k4 = 0x0f0f0f0f00000000ULL;

  t = k4 & (bb ^ (bb << 28));
  bb ^= t ^ (t >> 28);

  t = k2 & (bb ^ (bb << 14));
  bb ^= t ^ (t >> 14);

  t = k1 & (bb ^ (bb << 7));
  bb ^= t ^ (t >> 7);

  return bb;
}



// Shout out ChatGPT for this one
uint64_t Bitboard::reverse(uint64_t x) {
  // swap adjacent bits
  x = ((x & 0x5555555555555555ULL) << 1)  | ((x >> 1)  & 0x5555555555555555ULL);
  // swap pairs of bits
  x = ((x & 0x3333333333333333ULL) << 2)  | ((x >> 2)  & 0x3333333333333333ULL);
  // swap nibbles (4 bits)
  x = ((x & 0x0F0F0F0F0F0F0F0FULL) << 4)  | ((x >> 4)  & 0x0F0F0F0F0F0F0F0FULL);
  // swap bytes
  x = ((x & 0x00FF00FF00FF00FFULL) << 8)  | ((x >> 8)  & 0x00FF00FF00FF00FFULL);
  // swap 16-bit words
  x = ((x & 0x0000FFFF0000FFFFULL) << 16) | ((x >> 16) & 0x0000FFFF0000FFFFULL);
  // swap 32-bit double words
  x = (x << 32) | (x >> 32);
  return x;
}

// Shout out ChatGPT for this one
uint64_t Bitboard::flip_vertical(uint64_t bb) {
  bb = ((bb & 0x00000000000000FF) << 56) | \
       ((bb & 0x000000000000FF00) << 40) | \
       ((bb & 0x0000000000FF0000) << 24) | \
       ((bb & 0x00000000FF000000) << 8)  | \
       ((bb & 0x000000FF00000000) >> 8)  | \
       ((bb & 0x0000FF0000000000) >> 24) | \
       ((bb & 0x00FF000000000000) >> 40) | \
       ((bb & 0xFF00000000000000) >> 56);
  return bb;
}



