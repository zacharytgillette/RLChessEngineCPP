//
// Created by Zach Gillette on 4/10/25.
//

#ifndef SLIDING_PIECES_H
#define SLIDING_PIECES_H

#include "Pieces.h"

class Sliding_Pieces : public Pieces {
private:
protected:
  static const int MAX_NUM_ROOKS = 10;
  static const int MAX_NUM_ROOK_MOVES = MAX_NUM_ROOKS * 14;
  static const int MAX_NUM_BISHOPS = 10;
  static const int MAX_NUM_BISHOP_MOVES = MAX_NUM_BISHOPS * 13;
  static const int MAX_NUM_QUEENS = 9;
  static const int MAX_NUM_QUEEN_MOVES = MAX_NUM_QUEENS * 27;
public:

  // Constructors
  Sliding_Pieces();
  Sliding_Pieces(PieceType type);

  // Main functions
  static std::array<uint64_t, MAX_NUM_ROOK_MOVES> all_rook_moves(uint64_t bitboard, uint64_t empty_squares, uint64_t enemy_squares);
  static std::array<uint64_t, MAX_NUM_BISHOP_MOVES> all_bishop_moves(uint64_t bitboard, uint64_t empty_squares, uint64_t enemy_squares);

  // Helper functions
  static uint64_t get_horizontal_moves(uint64_t bitboard, uint64_t empty_squares, uint64_t enemy_squares);
  static uint64_t get_vertical_moves(uint64_t bitboard, uint64_t empty_squares, uint64_t enemy_squares);
  static uint64_t get_diagonal_moves(uint64_t bitboard, uint64_t empty_squares, uint64_t enemy_squares);

  // Helper^2 functions
  static int get_index(uint64_t bitboard);
  static int get_index_from_coors(int x, int y);
  // Important function: gets the ray of ones in an attack bitboard
  static uint64_t get_left_horizontal_ray(uint64_t bitboard, uint64_t empty_squares, uint64_t enemy_squares);
  static uint64_t get_right_horizontal_ray(uint64_t bitboard, uint64_t empty_squares, uint64_t enemy_squares);

};

#endif // SLIDING_PIECES_H
