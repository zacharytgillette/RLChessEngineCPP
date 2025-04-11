//
// Created by Zach Gillette on 4/11/25.
//

#include "Knights.h"

// Useful bitboards

// Empty left barrier (for vertical knight moves that wrap around the right to the left)
const uint64_t EMPTY_LEFT_SIDE = 0x7f7f7f7f7f7f7f7f;
// Empty right barrier (for vertical knight moves that wrap around the left to the right)
const uint64_t EMPTY_RIGHT_SIDE = 0xfefefefefefefefe;
// Empty left barrier (for horizontal knight moves that wrap around the right to the left)
const uint64_t EMPTY_TWO_LEFT_SIDE = 0x3f3f3f3f3f3f3f3f;
// Empty right barrier (for horizontal knight moves that wrap around the left to the right)
const uint64_t EMPTY_TWO_RIGHT_SIDE = 0xfcfcfcfcfcfcfcfc;

Knights::Knights(PieceType t) : type(t) {
  // Initialize for white
  if(type == WHITE_KNIGHT) {
    bitboard = 0x0000000000000042;
  }
  else if(type == BLACK_KNIGHT) {
    bitboard = 0x4200000000000000;
  }
  else {
    // This should never happen.
    std::cout << "ZACH ERROR: Initialized Knight Incorrectly." << std::endl;
    bitboard = 0x0;
  }
}
Knights::Knights(PieceType t, uint64_t bb) : type(t), bitboard(bb) {}

// Declared here, and in .h
using FuncPtr = uint64_t (*)(uint64_t, uint64_t, uint64_t);
FuncPtr Knights::get_opposite_move(FuncPtr ptr) {

  if(ptr == &Knights::up_left) {
    return &down_right;
  }
  else if (ptr == &Knights::up_right) {
    return &Knights::down_left;
  }
  else if (ptr == &Knights::down_left) {
    return &Knights::up_right;
  }
  else if (ptr == &Knights::down_right) {
    return &Knights::up_left;
  }
  else if (ptr == &Knights::left_up) {
    return &Knights::right_down;
  }
  else if (ptr == &Knights::left_down) {
    return &Knights::right_up;
  }
  else if (ptr == &Knights::right_up) {
    return &Knights::left_down;
  }
  else if (ptr == &Knights::right_down) {
    return &Knights::left_up;
  }
  else {
    // This should never happen
    std::cout << "ZACH ERROR: KNIGHT CODE IS WRONG." << std::endl;
    return nullptr;
  }

}

FuncPtr Knights::get_move_from_int(int ind) {

  if(ind == 0) {
    return &Knights::up_left;
  }
  else if(ind == 1) {
    return &Knights::up_right;
  }
  else if(ind == 2) {
    return &Knights::down_left;
  }
  else if(ind == 3) {
    return &Knights::down_right;
  }
  else if(ind == 4) {
    return &Knights::left_up;
  }
  else if(ind == 5) {
    return &Knights::left_down;
  }
  else if(ind == 6) {
    return &Knights::right_up;
  }
  else if(ind == 7) {
    return &Knights::right_down;
  }
  else {
    // Should never happen
    std::cout << "ZACH ERROR: Invalid index." << std::endl;
    return nullptr;
  }



}

uint64_t Knights::up_left(uint64_t bb, uint64_t empty_squares, uint64_t enemy_squares) {
    return (bb << 17) & (empty_squares | enemy_squares) & EMPTY_RIGHT_SIDE;
}

uint64_t Knights::up_right(uint64_t bb, uint64_t empty_squares,uint64_t enemy_squares) {
    return (bb << 15) & (empty_squares | enemy_squares) & EMPTY_LEFT_SIDE;
}

uint64_t Knights::down_left(uint64_t bb, uint64_t empty_squares, uint64_t enemy_squares) {
    return (bb >> 15) & (empty_squares | enemy_squares) & EMPTY_RIGHT_SIDE;
}

uint64_t Knights::down_right(uint64_t bb, uint64_t empty_squares, uint64_t enemy_squares) {
    return (bb >> 17) & (empty_squares | enemy_squares) & EMPTY_LEFT_SIDE;
}

uint64_t Knights::left_up(uint64_t bb, uint64_t empty_squares, uint64_t enemy_squares) {
    return (bb << 10) & (empty_squares | enemy_squares) & EMPTY_TWO_RIGHT_SIDE;
}

uint64_t Knights::left_down(uint64_t bb, uint64_t empty_squares, uint64_t enemy_squares) {
    return (bb >> 6) & (empty_squares | enemy_squares) & EMPTY_TWO_RIGHT_SIDE;
}

uint64_t Knights::right_up(uint64_t bb, uint64_t empty_squares, uint64_t enemy_squares) {
    return (bb << 6) & (empty_squares | enemy_squares) & EMPTY_TWO_LEFT_SIDE;
}

uint64_t Knights::right_down(uint64_t bb, uint64_t empty_squares, uint64_t enemy_squares) {
    return (bb >> 10) & (empty_squares | enemy_squares) & EMPTY_TWO_LEFT_SIDE;
}

std::array<uint64_t, Knights::MAX_NUM_KNIGHT_MOVES> Knights::all_moves(uint64_t empty_squares, uint64_t enemy_squares) {

    // to ret
    std::array<uint64_t, Knights::MAX_NUM_KNIGHT_MOVES> unique_post_move_bitboards;
    int move_index = 0;

    // For each of the 8 possible types of moves...
    for(int i=0; i<8; i++) {

      // Get move
      FuncPtr move = get_move_from_int(i);

      //Bitboard POST making a move
      uint64_t post_move = move(bitboard, empty_squares, enemy_squares);

      while(post_move > 0x0) {

        // Get a single Knight via lsb
        uint64_t to_square = Bitboard::get_lsb(post_move);

        // Find where the knight came from (opposite move function
        FuncPtr reverse_move = Knights::get_opposite_move(move);
        uint64_t from_square = Bitboard::reverse(to_square);

        // Get completed post-move bitboard, that we will then save
        uint64_t to_save = (bitboard | to_square) & (Bitboard::complement(from_square));

        // Save
        unique_post_move_bitboards[move_index] = to_save;
        move_index++;

        // Remove lsb, repeat
        post_move = Bitboard::remove_lsb(post_move);


      }

    }

  return unique_post_move_bitboards;

}

