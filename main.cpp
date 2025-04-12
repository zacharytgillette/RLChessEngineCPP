#include "Bitboard/include/Bishops.h"
#include "Bitboard/include/Bitboard.h"
#include "Bitboard/include/Kings.h"
#include "Bitboard/include/Knights.h"
#include "Bitboard/include/Pawns.h"
#include "Bitboard/include/Queens.h"
#include "Bitboard/include/Rooks.h"
#include <iostream>

int main1() {
  // For testing purposes, we assume the board is completely empty.
  // This means that every square is legal (empty squares and enemy pieces masks are fully set).
  const uint64_t fullMask = 0xffffffffffffffffULL;
  const uint64_t noMask = 0x0;
  // You can adjust the enemy mask as necessary (for example, set to 0 if you want no captures).
  const uint64_t emptySquares = fullMask;
  const uint64_t enemySquares = noMask;

  std::cout << "---- WHITE PIECES ----\n";

  // White Pieces (using the PieceType enum values defined in Pieces.h)
  Kings whiteKing(WHITE_KING);
  Queens whiteQueen(WHITE_QUEEN);
  Rooks whiteRook(WHITE_ROOK);
  Bishops whiteBishop(WHITE_BISHOP);
  Knights whiteKnight(WHITE_KNIGHT);
  Pawns whitePawn(WHITE_PAWN);

  // For each piece, call its all_moves function and print each resulting bitboard.
  std::cout << "\nWhite King moves:\n";
  auto wkMoves = whiteKing.all_moves(emptySquares, enemySquares);
  for (auto m : wkMoves) {
    std::cout << "FINAL KING MOVES" << std::endl;
    Bitboard::print(m);
  }

  std::cout << "\nWhite Queen moves:\n";
  auto wqMoves = whiteQueen.all_moves(emptySquares, enemySquares);
  for (auto m : wqMoves) {
    Bitboard::print(m);
  }

  std::cout << "\nWhite Rook moves:\n";
  auto wrMoves = whiteRook.all_moves(emptySquares, enemySquares);
  for (auto m : wrMoves) {
    Bitboard::print(m);
  }

  std::cout << "\nWhite Bishop moves:\n";
  auto wbMoves = whiteBishop.all_moves(emptySquares, enemySquares);
  for (auto m : wbMoves) {
    Bitboard::print(m);
  }

  std::cout << "\nWhite Knight moves:\n";
  auto wnMoves = whiteKnight.all_moves(emptySquares, enemySquares);
  for (auto m : wnMoves) {
    Bitboard::print(m);
  }

  std::cout << "\nWhite Pawn moves:\n";
  auto wpMoves = whitePawn.all_moves(emptySquares, enemySquares);
  for (auto m : wpMoves) {
    Bitboard::print(m);
  }

  std::cout << "\n---- BLACK PIECES ----\n";

  // Black Pieces
  Kings blackKing(BLACK_KING);
  Queens blackQueen(BLACK_QUEEN);
  Rooks blackRook(BLACK_ROOK);
  Bishops blackBishop(BLACK_BISHOP);
  Knights blackKnight(BLACK_KNIGHT);
  Pawns blackPawn(BLACK_PAWN);

  std::cout << "\nBlack King moves:\n";
  auto bkMoves = blackKing.all_moves(emptySquares, enemySquares);
  for (auto m : bkMoves) {
    Bitboard::print(m);
  }

  std::cout << "\nBlack Queen moves:\n";
  auto bqMoves = blackQueen.all_moves(emptySquares, enemySquares);
  for (auto m : bqMoves) {
    Bitboard::print(m);
  }

  std::cout << "\nBlack Rook moves:\n";
  auto brMoves = blackRook.all_moves(emptySquares, enemySquares);
  for (auto m : brMoves) {
    Bitboard::print(m);
  }

  std::cout << "\nBlack Bishop moves:\n";
  auto bbMoves = blackBishop.all_moves(emptySquares, enemySquares);
  for (auto m : bbMoves) {
    Bitboard::print(m);
  }

  std::cout << "\nBlack Knight moves:\n";
  auto bnMoves = blackKnight.all_moves(emptySquares, enemySquares);
  for (auto m : bnMoves) {
    Bitboard::print(m);
  }

  std::cout << "\nBlack Pawn moves:\n";
  auto bpMoves = blackPawn.all_moves(emptySquares, enemySquares);
  for (auto m : bpMoves) {
    Bitboard::print(m);
  }

  return 0;
}
