cmake_minimum_required(VERSION 3.26)
project(RLChessEngineCPP)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(Bitboard)

add_executable(RLChessEngineCPP
        Bitboard/Bishops.cpp
        Bitboard/Bishops.h
        Bitboard/Bitboard.cpp
        Bitboard/Bitboard.h
        Bitboard/Kings.cpp
        Bitboard/Kings.h
        Bitboard/Knights.cpp
        Bitboard/Knights.h
        Bitboard/Pawns.cpp
        Bitboard/Pawns.h
        Bitboard/Pieces.cpp
        Bitboard/Pieces.h
        Bitboard/Queens.cpp
        Bitboard/Queens.h
        Bitboard/Rooks.cpp
        Bitboard/Rooks.h
        Bitboard/Sliding_Pieces.cpp
        Bitboard/Sliding_Pieces.h
        main.cpp)
