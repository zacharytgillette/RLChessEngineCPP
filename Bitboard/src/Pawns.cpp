//
// Created by Zach Gillette on 4/11/25.
//

#include "Bitboard/include/Pawns.h"

// Useful bitboards

// Second and seventh rank: useful for pawn double moves
const uint64_t SECOND_RANK = 0x000000000000ff00;
const uint64_t SEVENTH_RANK = 0x00ff000000000000;

// Left barrier (for pawn capture moves that wrap around the right to the left)
const uint64_t EMPTY_LEFT_SIDE = 0x7f7f7f7f7f7f7f7f;
// Empty right barrier (for pawn capture moves that wrap around the left to the right)
const uint64_t EMPTY_RIGHT_SIDE = 0xfefefefefefefefe;

Pawns::Pawns(PieceType t) : type(t) {
  // Initialize for white
  if(type == WHITE_PAWN) {
    bitboard = 0x000000000000ff00;
  }
  else if(type == BLACK_PAWN) {
    bitboard = 0x00ff000000000000;
  }
  else {
    // This should never happen.
    std::cout << "ZACH ERROR: Initialized Pawns Incorrectly." << std::endl;
    bitboard = 0x0;
  }
}
Pawns::Pawns(PieceType t, uint64_t bb) : type(t), bitboard(bb) {}

uint64_t Pawns::single_moves(uint64_t bitboard, uint64_t empty_squares) {
    return (bitboard << 8) & empty_squares;
}

uint64_t Pawns::double_moves(uint64_t bitboard, uint64_t empty_squares) {
    uint64_t on_second_rank = bitboard & SECOND_RANK;
    uint64_t first_move = (on_second_rank << 8) & empty_squares;
    return (first_move << 8) & empty_squares;
}

uint64_t Pawns::capture_left(uint64_t bitboard, uint64_t enemy_squares) {
    return ((bitboard << 9) & enemy_squares & EMPTY_RIGHT_SIDE);
}

uint64_t Pawns::capture_right(uint64_t bitboard, uint64_t enemy_squares) {
    return ((bitboard << 7) & enemy_squares & EMPTY_LEFT_SIDE);
}

std::array<uint64_t, Pawns::MAX_NUM_PAWN_MOVES> Pawns::all_moves(uint64_t empty_squares, uint64_t enemy_squares) {

    // to ret
    std::array<uint64_t, Pawns::MAX_NUM_PAWN_MOVES> unique_post_move_bitboards;
    int move_index = 0;

    // Moves from each move type
    uint64_t post_move = Pawns::single_moves(bitboard, empty_squares);
    while(post_move > 0x0) {

      // Get individual pawn
      uint64_t to_square = Bitboard::get_lsb(post_move);

      // Find where it came from
      uint64_t from_square = to_square >> 8;

      // Completed move, to save
      uint64_t to_add = (bitboard | to_square) & (Bitboard::complement(from_square));

      // Save it
      unique_post_move_bitboards[move_index] = to_add;
      move_index++;

      // Remove lsb repeat
      post_move = Bitboard::remove_lsb(post_move);

    }


    post_move = Pawns::double_moves(bitboard, empty_squares);
    while(post_move > 0x0) {

      // Get individual pawn
      uint64_t to_square = Bitboard::get_lsb(post_move);

      // Find where it came from
      uint64_t from_square = to_square >> 16;

      // Completed move, to save
      uint64_t to_add = (bitboard | to_square) & (Bitboard::complement(from_square));

      // Save it
      unique_post_move_bitboards[move_index] = to_add;
      move_index++;

      // Remove lsb repeat
      post_move = Bitboard::remove_lsb(post_move);

    }


    post_move = Pawns::capture_left(bitboard, enemy_squares);
    while(post_move > 0x0) {

      // Get individual pawn
      uint64_t to_square = Bitboard::get_lsb(post_move);

      // Find where it came from
      uint64_t from_square = to_square >> 9;

      // Completed move, to save
      uint64_t to_add = (bitboard | to_square) & (Bitboard::complement(from_square));

      // Save it
      unique_post_move_bitboards[move_index] = to_add;
      move_index++;

      // Remove lsb repeat
      post_move = Bitboard::remove_lsb(post_move);

    }


    post_move = Pawns::capture_right(bitboard, enemy_squares);
    while(post_move > 0x0) {

      // Get individual pawn
      uint64_t to_square = Bitboard::get_lsb(post_move);

      // Find where it came from
      uint64_t from_square = to_square >> 7;

      // Completed move, to save
      uint64_t to_add = (bitboard | to_square) & (Bitboard::complement(from_square));

      // Save it
      unique_post_move_bitboards[move_index] = to_add;
      move_index++;

      // Remove lsb repeat
      post_move = Bitboard::remove_lsb(post_move);

    }

    //make all other indices empty bitboards
    for(int i=move_index; i<MAX_NUM_PAWN_MOVES; i++) {
      unique_post_move_bitboards[i] = 0x0;
    }

    return unique_post_move_bitboards;

}

