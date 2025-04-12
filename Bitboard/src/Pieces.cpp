//
// Created by Zach Gillette on 4/10/25.
//

#include "Bitboard/include/Pieces.h"

Pieces::Pieces() : type(NONE) { }
Pieces::Pieces(PieceType type) : type(type) { }

PieceType Pieces::flip_piece_type(PieceType ptype) {

  switch(ptype) {
  case WHITE_PAWN:    return BLACK_PAWN;
  case BLACK_PAWN:    return WHITE_PAWN;
  case WHITE_KNIGHT:  return BLACK_KNIGHT;
  case BLACK_KNIGHT:  return WHITE_KNIGHT;
  case WHITE_BISHOP:  return BLACK_BISHOP;
  case BLACK_BISHOP:  return WHITE_BISHOP;
  case WHITE_ROOK:    return BLACK_ROOK;
  case BLACK_ROOK:    return WHITE_ROOK;
  case WHITE_QUEEN:   return BLACK_QUEEN;
  case BLACK_QUEEN:   return WHITE_QUEEN;
  case WHITE_KING:    return BLACK_KING;
  case BLACK_KING:    return WHITE_KING;
  default:            return NONE;  // or static_cast<PieceType>(-1)
  }

}
