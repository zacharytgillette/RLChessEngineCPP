//
// Created by Zach Gillette on 4/11/25.
//

#include "Pieces.h"

#ifndef RLCHESSENGINE_PAWNS_H
#define RLCHESSENGINE_PAWNS_H

class Pawns : public Pieces {
private:
  PieceType type;
  uint64_t bitboard;
  static const int MAX_NUM_PAWNS = 8;
  static const int MAX_NUM_PAWN_MOVES = MAX_NUM_PAWNS * 4;
public:

  // Constructors
  Pawns() = delete;
  Pawns(PieceType type);
  Pawns(PieceType type, uint64_t bitboard);

  // Individual move functions
  static uint64_t single_moves(uint64_t bitboard, uint64_t empty_squares);
  static uint64_t double_moves(uint64_t bitboard, uint64_t empty_squares);
  static uint64_t capture_left(uint64_t bitboard, uint64_t enemy_squares);
  static uint64_t capture_right(uint64_t bitboard, uint64_t enemy_squares);

  // Move generation
  std::array<uint64_t, MAX_NUM_PAWN_MOVES> all_moves(uint64_t empty_squares, uint64_t enemy_squares);








};

#endif // RLCHESSENGINE_PAWNS_H
