cmake_minimum_required(VERSION 3.26)
project(RLChessEngineCPP)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(Bitboard)

add_executable(RLChessEngineCPP
        Bitboard/src/Bishops.cpp
        Bitboard/include/Bishops.h
        Bitboard/src/Bitboard.cpp
        Bitboard/include/Bitboard.h
        Bitboard/src/Kings.cpp
        Bitboard/include/Kings.h
        Bitboard/src/Knights.cpp
        Bitboard/include/Knights.h
        Bitboard/src/Pawns.cpp
        Bitboard/include/Pawns.h
        Bitboard/src/Pieces.cpp
        Bitboard/include/Pieces.h
        Bitboard/src/Queens.cpp
        Bitboard/include/Queens.h
        Bitboard/src/Rooks.cpp
        Bitboard/include/Rooks.h
        Bitboard/src/Sliding_Pieces.cpp
        Bitboard/include/Sliding_Pieces.h
        main.cpp
        test.cpp
        game_functions.h
        game_functions.cpp)
