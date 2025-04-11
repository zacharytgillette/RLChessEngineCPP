//
// Created by Zach Gillette on 4/11/25.
//

#include "Pieces.h"

#ifndef KNIGHTS_H
#define KNIGHTS_H

class Knights : public Pieces {

private:
  PieceType type;
  uint64_t bitboard;
  static const int MAX_NUM_KNIGHTS = 10;
  static const int MAX_NUM_KNIGHT_MOVES = MAX_NUM_KNIGHTS * 8;

public:

  // Declared here, and in .cpp
  using FuncPtr = uint64_t (*)(uint64_t, uint64_t, uint64_t);

  // Constructors
  Knights() = delete;
  Knights(PieceType type);
  Knights(PieceType type, uint64_t bitboard);

  // Get opposite move function
  static FuncPtr get_opposite_move(FuncPtr ptr);

  // Get move function from int
  static FuncPtr get_move_from_int(int ind);

  // Individual move functions
  static uint64_t up_left(uint64_t bitboard, uint64_t empty_squares, uint64_t enemy_squares);
  static uint64_t up_right(uint64_t bitboard, uint64_t empty_squares, uint64_t enemy_squares);
  static uint64_t down_left(uint64_t bitboard, uint64_t empty_squares, uint64_t enemy_squares);
  static uint64_t down_right(uint64_t bitboard, uint64_t empty_squares, uint64_t enemy_squares);
  static uint64_t left_up(uint64_t bitboard, uint64_t empty_squares, uint64_t enemy_squares);
  static uint64_t left_down(uint64_t bitboard, uint64_t empty_squares, uint64_t enemy_squares);
  static uint64_t right_up(uint64_t bitboard, uint64_t empty_squares, uint64_t enemy_squares);
  static uint64_t right_down(uint64_t bitboard, uint64_t empty_squares, uint64_t enemy_squares);

  // Move generation
  std::array<uint64_t, MAX_NUM_KNIGHT_MOVES> all_moves(uint64_t empty_squares, uint64_t enemy_squares);

};

#endif // KNIGHTS_H
