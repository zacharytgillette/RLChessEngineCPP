//
// Created by Zach Gillette on 4/10/25.
//

#include "Sliding_Pieces.h"

Sliding_Pieces::Sliding_Pieces() : Pieces() { }
Sliding_Pieces::Sliding_Pieces(PieceType type) : Pieces(type) { }

std::array<uint64_t, Sliding_Pieces::MAX_NUM_ROOK_MOVES> Sliding_Pieces::all_rook_moves(uint64_t bitboard, uint64_t empty_squares, uint64_t enemy_squares) {

    // First, create a list of isolated rook bitboards
    uint64_t rook_bb = bitboard;
    uint64_t isolated_rook_bbs[Sliding_Pieces::MAX_NUM_ROOKS];
    int rook_index = 0;

    while(rook_bb > 0x0) {

      // Get isolated move bitboard
      uint64_t isolated_bb = Bitboard::get_lsb(rook_bb);

      // Save it
      isolated_rook_bbs[rook_index] = isolated_bb;
      rook_index++;

      // Remove it from combined bb
      rook_bb = Bitboard::remove_lsb(rook_bb);

    }

    // Now, determine completed move bitboards from the isolated bitboards
    std::array<uint64_t, Sliding_Pieces::MAX_NUM_ROOK_MOVES> unique_post_move_bitboards;
    int move_index = 0;
    for(int i=0; i<rook_index; i++) {

      // Get isolated rook bitboard
      uint64_t rook = isolated_rook_bbs[i];
      uint64_t rook_complement = Bitboard::complement(rook);

      // Get moves
      uint64_t vertical_moves = Sliding_Pieces::get_vertical_moves(rook, empty_squares, enemy_squares & rook_complement);
      uint64_t horizontal_moves = Sliding_Pieces::get_horizontal_moves(rook, empty_squares, enemy_squares & rook_complement);
      uint64_t moves_bitboard = vertical_moves | horizontal_moves;

      // Bitboard without current move
      uint64_t bitboard_removed_rook = bitboard & Bitboard::complement(rook);

      // Save all final bitboards
      while(moves_bitboard > 0x0) {

        // Get single moves
        uint64_t isolated_move = Bitboard::get_lsb(moves_bitboard);

        // Add it to bitboard of all the other rooks
        uint64_t combined_rook_bb = bitboard_removed_rook | isolated_move;

        // Save it
        unique_post_move_bitboards[move_index] = combined_rook_bb;
        move_index++;

        // Remove single move from moves bitboard, repeat
        moves_bitboard = Bitboard::remove_lsb(moves_bitboard);

      }


    }

    return unique_post_move_bitboards;
}

std::array<uint64_t, Sliding_Pieces::MAX_NUM_BISHOP_MOVES> Sliding_Pieces::all_bishop_moves(uint64_t bitboard, uint64_t empty_squares, uint64_t enemy_squares) {

  uint64_t bishop_bb = bitboard;
  uint64_t isolated_bishop_bbs[Sliding_Pieces::MAX_NUM_BISHOPS];
  int bishop_index = 0;

  while(bishop_bb > 0x0) {

      // Get isolated move bitboard
      uint64_t isolated_bb = Bitboard::get_lsb(bishop_bb);

      // Save it
      isolated_bishop_bbs[bishop_index] = isolated_bb;
      bishop_index++;

      // Remove it from combined bb
      bishop_bb = Bitboard::remove_lsb(bishop_bb);

  }

  // Now, determine completed move bitboards from the isolated bitboards
  // Now, determine completed move bitboards from the isolated bitboards
  std::array<uint64_t, Sliding_Pieces::MAX_NUM_BISHOP_MOVES> unique_post_move_bitboards;
  int move_index = 0;
  for(int i=0; i<bishop_index; i++) {

      // Get isolated rook bitboard
      uint64_t bishop = isolated_bishop_bbs[i];
      uint64_t bishop_complement = Bitboard::complement(bishop);

      // Get moves
      uint64_t moves_bitboard = Sliding_Pieces::get_diagonal_moves(bishop, empty_squares, enemy_squares);

      // Bitboard without current move
      uint64_t bitboard_removed_bishop = bitboard & Bitboard::complement(bishop);

      // Save all final bitboards
      while(moves_bitboard > 0x0) {

        // Get single moves
        uint64_t isolated_move = Bitboard::get_lsb(moves_bitboard);

        // Add it to bitboard of all the other rooks
        uint64_t combined_bishop_bb = bitboard_removed_bishop | isolated_move;

        // Save it
        unique_post_move_bitboards[move_index] = combined_bishop_bb;
        move_index++;

        // Remove single move from moves bitboard, repeat
        moves_bitboard = Bitboard::remove_lsb(moves_bitboard);

      }

  }


  return unique_post_move_bitboards;

}

uint64_t Sliding_Pieces::get_horizontal_moves(uint64_t bitboard, uint64_t empty_squares, uint64_t enemy_squares) {

    uint64_t l_ray = Sliding_Pieces::get_left_horizontal_ray(bitboard, empty_squares, enemy_squares);
    uint64_t r_ray = Sliding_Pieces::get_right_horizontal_ray(bitboard, empty_squares, enemy_squares);

    return l_ray | r_ray;

}

uint64_t Sliding_Pieces::get_vertical_moves(uint64_t bitboard, uint64_t empty_squares, uint64_t enemy_squares) {

    uint64_t up_ray = Sliding_Pieces::get_left_horizontal_ray(Bitboard::flip_diagonal(bitboard), Bitboard::flip_diagonal(empty_squares), Bitboard::flip_diagonal(enemy_squares));
    uint64_t down_ray = Sliding_Pieces::get_right_horizontal_ray(Bitboard::flip_diagonal(bitboard), Bitboard::flip_diagonal(empty_squares), Bitboard::flip_diagonal(enemy_squares));

    return up_ray | down_ray;

}

//TODO: this can be easily optimized
uint64_t Sliding_Pieces::get_diagonal_moves(uint64_t bitboard, uint64_t empty_squares, uint64_t enemy_squares) {

    int index = Sliding_Pieces::get_index(bitboard);
    uint64_t to_ret = 0x0;

    // Safety in case bitboard is empty
    if(index == 99) {
      return to_ret;
    }

    std::string empty_sub = Bitboard::reverse_to_string(empty_squares);
    std::string enemy_sub = Bitboard::reverse_to_string(enemy_squares);

    int X = index % 8;
    int Y = index / 8;
    int x;
    int y;

    // Top left
    x = X + 1;
    y = Y + 1;
    while(x < 8 && y < 8) {

      if(empty_sub[Sliding_Pieces::get_index_from_coors(x, y)] == '0' && enemy_sub[Sliding_Pieces::get_index_from_coors(x, y)] == '0') {
        break;
      }

      int ind = Sliding_Pieces::get_index_from_coors(x, y);
      to_ret |= (1ULL << ind); // faster way of doing 2^ind

      // Break if we land on another piece
      if(enemy_sub[Sliding_Pieces::get_index_from_coors(x, y)] == '1') {
        break;
      }

      x++;
      y++;

    }

    // Top right
    x = X - 1;
    y = Y + 1;
    while(x >= 0 && y < 8) {

      if(empty_sub[Sliding_Pieces::get_index_from_coors(x, y)] == '0' && enemy_sub[Sliding_Pieces::get_index_from_coors(x, y)] == '0') {
        break;
      }

      int ind = Sliding_Pieces::get_index_from_coors(x, y);
      to_ret |= (1ULL << ind); // faster way of doing 2^ind

      // Break if we land on another piece
      if(enemy_sub[Sliding_Pieces::get_index_from_coors(x, y)] == '1') {
        break;
      }

      x--;
      y++;

    }

    // Bottom right
    x = X - 1;
    y = Y - 1;
    while(x >= 0 && y >= 0) {

      if(empty_sub[Sliding_Pieces::get_index_from_coors(x, y)] == '0' && enemy_sub[Sliding_Pieces::get_index_from_coors(x, y)] == '0') {
        break;
      }

      int ind = Sliding_Pieces::get_index_from_coors(x, y);
      to_ret |= (1ULL << ind); // faster way of doing 2^ind

      // Break if we land on another piece
      if(enemy_sub[Sliding_Pieces::get_index_from_coors(x, y)] == '1') {
        break;
      }

      x--;
      y--;

    }

    // Bottom left
    x = X + 1;
    y = Y - 1;
    while(x < 8 && y >= 0) {

      if(empty_sub[Sliding_Pieces::get_index_from_coors(x, y)] == '0' && enemy_sub[Sliding_Pieces::get_index_from_coors(x, y)] == '0') {
        break;
      }

      int ind = Sliding_Pieces::get_index_from_coors(x, y);
      to_ret |= (1ULL << ind); // faster way of doing 2^ind

      // Break if we land on another piece
      if(enemy_sub[Sliding_Pieces::get_index_from_coors(x, y)] == '1') {
        break;
      }

      x++;
      y--;

    }

    return to_ret;

}

int Sliding_Pieces::get_index(uint64_t bitboard) {

  if(bitboard == 0x0) {
    return 99;
  }
  // This built-in function is undefined if bitboard==0
  return __builtin_ctzll(bitboard);

}

int Sliding_Pieces::get_index_from_coors(int x, int y) {
  return (y*8) + x;
}

uint64_t Sliding_Pieces::get_left_horizontal_ray(uint64_t bitboard, uint64_t empty_squares, uint64_t enemy_squares) {

  int rook_index = Sliding_Pieces::get_index(bitboard);
  if(rook_index == 99) {
    return 0x0;
  }
  int dist_from_RIGHT_wall = rook_index % 8;
  int dist_from_LEFT_wall = 7 - dist_from_RIGHT_wall;

  // Find distance to closest enemy piece AFTER rook_index
  uint64_t enemy_pieces_shifted = enemy_squares >> rook_index;
  int dist_from_enemy = Sliding_Pieces::get_index(Bitboard::get_lsb(enemy_pieces_shifted)) - 1;

  // Find distance to closest piece on same team
  uint64_t blockers = Bitboard::complement(empty_squares) & Bitboard::complement(bitboard) & Bitboard::complement(enemy_squares);
  uint64_t blockers_shifted = blockers >> rook_index;
  int dist_from_blocker = Sliding_Pieces::get_index(Bitboard::get_lsb(blockers_shifted)) - 1;

  // Find the "limiting reactant" of what is closest
  int limiting_reactant = std::min(dist_from_LEFT_wall, std::min(dist_from_enemy, dist_from_blocker));

  // Adjust limiting reactant if we're attacking
  //TODO: this logic is both wrong and overcomplicated...
  if(limiting_reactant == dist_from_enemy && limiting_reactant >= 0 && dist_from_blocker > limiting_reactant && dist_from_LEFT_wall > 0 && dist_from_LEFT_wall != dist_from_enemy) {
    limiting_reactant++;
  }

  // Cannot be negative...
  if(limiting_reactant == -1) {
    limiting_reactant = 0;
  }

  return ((1ULL << limiting_reactant) - 1) << (rook_index+1);

}

uint64_t Sliding_Pieces::get_right_horizontal_ray(uint64_t bitboard, uint64_t empty_squares, uint64_t enemy_squares) {

  uint64_t rev_bitboard = Bitboard::reverse(bitboard);
  uint64_t rev_enemy_squares = Bitboard::reverse(enemy_squares);
  uint64_t rev_empty_squares = Bitboard::reverse(empty_squares);

  uint64_t rev_r_ray = Sliding_Pieces::get_left_horizontal_ray(rev_bitboard, rev_empty_squares, rev_enemy_squares);
  uint64_t r_ray = Bitboard::reverse(rev_r_ray);

  return r_ray;

}

