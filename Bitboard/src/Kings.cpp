//
// Created by Zach Gillette on 4/11/25.
//

#include "Bitboard/include/Kings.h"

// Useful bitboards

// Empty left barrier (for king moves that wrap around the right to the left)
const uint64_t EMPTY_LEFT_SIDE = 0x7f7f7f7f7f7f7f7f;
// Empty right barrier (for king moves that wrap around the left to the right)
const uint64_t EMPTY_RIGHT_SIDE = 0xfefefefefefefefe;

Kings::Kings(PieceType t) : type(t) {
  // Initialize for white
  if(type == WHITE_KING) {
    bitboard = 0x0000000000000008;
  }
  else if(type == BLACK_KING) {
    bitboard = 0x0800000000000000;
  }
  else {
    // This should never happen.
    std::cout << "ZACH ERROR: Initialized King Incorrectly." << std::endl;
    bitboard = 0x0;
  }
}
Kings::Kings(PieceType t, uint64_t bb) : type(t), bitboard(bb) {}

// Declared here, and in .h
using FuncPtr = uint64_t (*)(uint64_t, uint64_t, uint64_t);
FuncPtr Kings::get_opposite_move(FuncPtr ptr) {

  if(ptr == &Kings::left) {
    return &Kings::right;
  }
  else if (ptr == &Kings::right) {
    return &Kings::left;
  }
  else if (ptr == &Kings::up) {
    return &Kings::down;
  }
  else if (ptr == &Kings::down) {
    return &Kings::up;
  }
  else if (ptr == &Kings::down_right) {
    return &Kings::up_left;
  }
  else if (ptr == &Kings::up_left) {
    return &Kings::down_right;
  }
  else if (ptr == &Kings::up_right) {
    return &Kings::down_left;
  }
  else if (ptr == &Kings::down_left) {
    return &Kings::up_right;
  }
  else {
    // This should never happen
    std::cout << "ZACH ERROR: KING CODE IS WRONG." << std::endl;
    return nullptr;
  }

}

FuncPtr Kings::get_move_from_int(int ind) {

  if(ind == 0) {
    return &Kings::left;
  }
  else if(ind == 1) {
    return &Kings::right;
  }
  else if(ind == 2) {
    return &Kings::up;
  }
  else if(ind == 3) {
    return &Kings::down;
  }
  else if(ind == 4) {
    return &Kings::up_left;
  }
  else if(ind == 5) {
    return &Kings::down_right;
  }
  else if(ind == 6) {
    return &Kings::up_right;
  }
  else if(ind == 7) {
    return &Kings::down_left;
  }
  else {
    // Should never happen
    std::cout << "ZACH ERROR: Invalid index." << std::endl;
    return nullptr;
  }

}

uint64_t Kings::left(uint64_t bitboard, uint64_t empty_squares, uint64_t enemy_squares) {
    return (bitboard << 1) & (empty_squares | enemy_squares) & EMPTY_RIGHT_SIDE;
}

uint64_t Kings::right(uint64_t bitboard, uint64_t empty_squares, uint64_t enemy_squares) {
    return (bitboard >> 1) & (empty_squares | enemy_squares) & EMPTY_LEFT_SIDE;
}

uint64_t Kings::up(uint64_t bitboard, uint64_t empty_squares, uint64_t enemy_squares) {
    return (bitboard << 8) & (empty_squares | enemy_squares);
}

uint64_t Kings::down(uint64_t bitboard, uint64_t empty_squares, uint64_t enemy_squares) {
    return (bitboard >> 8) & (empty_squares | enemy_squares);
}

uint64_t Kings::up_left(uint64_t bitboard, uint64_t empty_squares, uint64_t enemy_squares) {
    return (bitboard << 9) & (empty_squares | enemy_squares) & EMPTY_RIGHT_SIDE;
}

uint64_t Kings::down_left(uint64_t bitboard, uint64_t empty_squares, uint64_t enemy_squares) {
    return (bitboard >> 7) & (empty_squares | enemy_squares) & EMPTY_RIGHT_SIDE;
}

uint64_t Kings::up_right(uint64_t bitboard, uint64_t empty_squares, uint64_t enemy_squares) {
    return (bitboard << 7) & (empty_squares | enemy_squares) & EMPTY_LEFT_SIDE;
}

uint64_t Kings::down_right(uint64_t bitboard, uint64_t empty_squares, uint64_t enemy_squares) {
    return (bitboard >> 9) & (empty_squares | enemy_squares) & EMPTY_LEFT_SIDE;
}

std::array<uint64_t, Kings::MAX_NUM_KING_MOVES> Kings::all_moves(uint64_t empty_squares, uint64_t enemy_squares) {

    // to ret
    std::array<uint64_t, Kings::MAX_NUM_KING_MOVES> unique_post_move_bitboards;
    int move_index = 0;

    for(int i=0; i<8; i++) {

      std::cout << "ITER " << i << std::endl;

      // Get move
      FuncPtr move = get_move_from_int(i);

      // Bitboard POST making a move
      uint64_t post_move = move(bitboard, empty_squares, enemy_squares);

//      std::cout<<"POST MOVE"<<std::endl;
//      Bitboard::print(post_move);

      while(post_move > 0x0) {

        // Get a single Knight via lsb
        uint64_t to_square = Bitboard::get_lsb(post_move);

//        std::cout<<"TO SQUARE"<<std::endl;
//        Bitboard::print(to_square);

        // Find where the King came from (opposite move function
        FuncPtr reverse_move = Kings::get_opposite_move(move);
        uint64_t from_square = reverse_move(to_square, 0xffffffffffffffff, 0xffffffffffffffff);

//        std::cout<<"FROM SQUARE"<<std::endl;
//        Bitboard::print(from_square);

        // Get completed post-move bitboard, that we will then save
        uint64_t to_save = (bitboard | to_square) & (Bitboard::complement(from_square));

        std::cout<<"TO SAVE"<<std::endl;
        Bitboard::print(to_save);

        // Save
        unique_post_move_bitboards[move_index] = to_save;
        move_index++;

        // Remove lsb, repeat
        post_move = Bitboard::remove_lsb(post_move);

//        std::cout<<"POST MOVE UPDATED"<<std::endl;
//        Bitboard::print(post_move);



      }

    }

    //make all other indices empty bitboards
    for(int i=move_index; i<MAX_NUM_KING_MOVES; i++) {
      unique_post_move_bitboards[i] = 0x0;
    }

  return unique_post_move_bitboards;

}
