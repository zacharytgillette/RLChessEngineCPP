//
// Created by Zach Gillette on 4/12/25.
//

#include "Bitboard/include/Pawns.h"
#include "Bitboard/include/Knights.h"
#include "Bitboard/include/Bishops.h"
#include "Bitboard/include/Rooks.h"
#include "Bitboard/include/Queens.h"
#include "Bitboard/include/Kings.h"

#ifndef GAME_FUNCTIONS_H
#define GAME_FUNCTIONS_H

class Chess {
private:
  static const int row_count = 8;
  static const int column_count = 8;
  static const int action_size = row_count * column_count * 73;
  static const int T;

  const std::unordered_map<const int, const int> Left_Shift_to_Movement_Type = {
      { 8, 0 },
      { 16, 1 },
      { 24, 2 },
      { 32, 3 },
      { 40, 4 },
      { 48, 5 },
      { 56, 6 },

      { 7, 7 },
      { 14, 8 },
      { 21, 9 },
      { 28, 10 },
      { 35, 11 },
      { 42, 12 },
      { 49, 13 },

      { -1, 14 },
      { -2, 15 },
      { -3, 16 },
      { -4, 17 },
      { -5, 18 },
      { -6, 19 },
      { -7, 20 },

      { -9, 21 },
      { -18, 22 },
      { -27, 23 },
      { -36, 24 },
      { -45, 25 },
      { -54, 26 },
      { -63, 27 },

      { -8, 28 },
      { -16, 29 },
      { -24, 30 },
      { -32, 31 },
      { -40, 32 },
      { -48, 33 },
      { -56, 34 },

      // Duplicate key: -7 appears again.
      { -7, 35 },
      { -14, 36 },
      { -21, 37 },
      { -28, 38 },
      { -35, 39 },
      { -42, 40 },
      { -49, 41 },

      { 1, 42 },
      { 2, 43 },
      { 3, 44 },
      { 4, 45 },
      { 5, 46 },
      { 6, 47 },
      { 7, 48 },

      { 9, 49 },
      { 18, 50 },
      { 27, 51 },
      { 36, 52 },
      { 45, 53 },
      { 54, 54 },
      { 63, 55 },

      { 15, 56 },
      { 6, 57 },
      { -10, 58 },
      { -17, 59 },
      { -15, 60 },
      { -6, 61 },
      { 10, 62 },
      { 17, 63 }
  };

  // Define a function pointer type. For example, a function that takes an int and returns an int.
  using FuncPtr = uint64_t(*)(uint64_t);

  // Define a constexpr mapping from int keys to lambda functions (converted to function pointers)
  std::array<std::pair<int, FuncPtr>, 73> Index_to_Movement_Type {{
      {0,  [](uint64_t x) -> uint64_t { return x << 8; }},
      {1,  [](uint64_t x) -> uint64_t { return x << 16; }},
      {2,  [](uint64_t x) -> uint64_t { return x << 24; }},
      {3,  [](uint64_t x) -> uint64_t { return x << 32; }},
      {4,  [](uint64_t x) -> uint64_t { return x << 40; }},
      {5,  [](uint64_t x) -> uint64_t { return x << 48; }},
      {6,  [](uint64_t x) -> uint64_t { return x << 56; }},

      // up-right
      {7,  [](uint64_t x) -> uint64_t { return x << 7; }},
      {8,  [](uint64_t x) -> uint64_t { return x << 14; }},
      {9,  [](uint64_t x) -> uint64_t { return x << 21; }},
      {10, [](uint64_t x) -> uint64_t { return x << 28; }},
      {11, [](uint64_t x) -> uint64_t { return x << 35; }},
      {12, [](uint64_t x) -> uint64_t { return x << 42; }},
      {13, [](uint64_t x) -> uint64_t { return x << 49; }},

      // right
      {14, [](uint64_t x) -> uint64_t { return x >> 1; }},
      {15, [](uint64_t x) -> uint64_t { return x >> 2; }},
      {16, [](uint64_t x) -> uint64_t { return x >> 3; }},
      {17, [](uint64_t x) -> uint64_t { return x >> 4; }},
      {18, [](uint64_t x) -> uint64_t { return x >> 5; }},
      {19, [](uint64_t x) -> uint64_t { return x >> 6; }},
      {20, [](uint64_t x) -> uint64_t { return x >> 7; }},

      // down-right
      {21, [](uint64_t x) -> uint64_t { return x >> 9; }},
      {22, [](uint64_t x) -> uint64_t { return x >> 18; }},
      {23, [](uint64_t x) -> uint64_t { return x >> 27; }},
      {24, [](uint64_t x) -> uint64_t { return x >> 36; }},
      {25, [](uint64_t x) -> uint64_t { return x >> 45; }},
      {26, [](uint64_t x) -> uint64_t { return x >> 54; }},
      {27, [](uint64_t x) -> uint64_t { return x >> 63; }},

      // down
      {28, [](uint64_t x) -> uint64_t { return x >> 8; }},
      {29, [](uint64_t x) -> uint64_t { return x >> 16; }},
      {30, [](uint64_t x) -> uint64_t { return x >> 24; }},
      {31, [](uint64_t x) -> uint64_t { return x >> 32; }},
      {32, [](uint64_t x) -> uint64_t { return x >> 40; }},
      {33, [](uint64_t x) -> uint64_t { return x >> 48; }},
      {34, [](uint64_t x) -> uint64_t { return x >> 56; }},

      // down-left
      {35, [](uint64_t x) -> uint64_t { return x >> 7; }},
      {36, [](uint64_t x) -> uint64_t { return x >> 14; }},
      {37, [](uint64_t x) -> uint64_t { return x >> 21; }},
      {38, [](uint64_t x) -> uint64_t { return x >> 28; }},
      {39, [](uint64_t x) -> uint64_t { return x >> 35; }},
      {40, [](uint64_t x) -> uint64_t { return x >> 42; }},
      {41, [](uint64_t x) -> uint64_t { return x >> 49; }},

      // left
      {42, [](uint64_t x) -> uint64_t { return x << 1; }},
      {43, [](uint64_t x) -> uint64_t { return x << 2; }},
      {44, [](uint64_t x) -> uint64_t { return x << 3; }},
      {45, [](uint64_t x) -> uint64_t { return x << 4; }},
      {46, [](uint64_t x) -> uint64_t { return x << 5; }},
      {47, [](uint64_t x) -> uint64_t { return x << 6; }},
      {48, [](uint64_t x) -> uint64_t { return x << 7; }},

      // top left
      {49, [](uint64_t x) -> uint64_t { return x << 9; }},
      {50, [](uint64_t x) -> uint64_t { return x << 18; }},
      {51, [](uint64_t x) -> uint64_t { return x << 27; }},
      {52, [](uint64_t x) -> uint64_t { return x << 36; }},
      {53, [](uint64_t x) -> uint64_t { return x << 45; }},
      {54, [](uint64_t x) -> uint64_t { return x << 54; }},
      {55, [](uint64_t x) -> uint64_t { return x << 63; }},

      // knight moves
      {56, [](uint64_t x) -> uint64_t { return x << 15; }},
      {57, [](uint64_t x) -> uint64_t { return x << 6; }},
      {58, [](uint64_t x) -> uint64_t { return x >> 10; }},
      {59, [](uint64_t x) -> uint64_t { return x >> 17; }},
      {60, [](uint64_t x) -> uint64_t { return x >> 15; }},
      {61, [](uint64_t x) -> uint64_t { return x >> 6; }},
      {62, [](uint64_t x) -> uint64_t { return x << 10; }},
      {63, [](uint64_t x) -> uint64_t { return x << 17; }},

      // underpromotions (keys 64 to 72)
      {64, [](uint64_t x) -> uint64_t { return x << 9; }},
      {65, [](uint64_t x) -> uint64_t { return x << 8; }},
      {66, [](uint64_t x) -> uint64_t { return x << 7; }},
      {67, [](uint64_t x) -> uint64_t { return x << 9; }},
      {68, [](uint64_t x) -> uint64_t { return x << 8; }},
      {69, [](uint64_t x) -> uint64_t { return x << 7; }},
      {70, [](uint64_t x) -> uint64_t { return x << 9; }},
      {71, [](uint64_t x) -> uint64_t { return x << 8; }},
      {72, [](uint64_t x) -> uint64_t { return x << 7; }}
  }};


  // Functions

  std::string repr();
  //State get_next_state(State state, int action);
  //std::array<Pieces, 12> temp_apply_action_to_bitboard(std::array<Pieces, 12> state_pieces, State state, int action);
  //std::array<int, TODO: length i forget> get_valid_moves(State state);
  std::array<uint64_t, 2> get_important_squares(std::array<Pieces, 12> state_pieces, Colors color);
  bool is_in_check(std::array<Pieces, 12> state_pieces, Colors color);
  //bool check_win(State state, int action);
  bool is_power_of_two(int n);
  //bool get_terminal_flags(State state);
  //careful of this one, return type slightly different:
  //std::array<int, 2> get_value_and_terminated(State state, int action);
  int get_opponent(int player);
  // TODO: is value an int?
  int get_opponent_value(int value);
  // NOTE: functions like flip_vertical and flip_piece_type were
  // moved to Bitboard and Pieces respectively, since they should've
  // been there all along
  //State change_perspective(State state);
  // TODO: decide on get_encoded_state output, since it goes into model shit





};

class game_functions {




};

#endif // GAME_FUNCTIONS_H
