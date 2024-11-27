
#ifndef LSMOVES_H
#define LSMOVES_H

#include "LSTypes.h"

#include <stdint.h>

// Start configuration

#define LS_START_POSITION_WHITE_KING 0x8
#define LS_START_POSITION_WHITE_QUEEN 0x10
#define LS_START_POSITION_WHITE_ROOK 0x81
#define LS_START_POSITION_WHITE_KNIGHT 0x42
#define LS_START_POSITION_WHITE_BISHOP 0x24
#define LS_START_POSITION_WHITE_PAWN 0xff00

#define LS_START_POSITION_BLACK_KING 0x800000000000000
#define LS_START_POSITION_BLACK_QUEEN 0x1000000000000000
#define LS_START_POSITION_BLACK_ROCK 0x8100000000000000
#define LS_START_POSITION_BLACK_KNIGHT 0x4200000000000000
#define LS_START_POSITION_BLACK_BISHOP 0x2400000000000000
#define LS_START_POSITION_BLACK_PAWN 0xFF000000000000

// Moves

constexpr uint8_t _ls_king_moves = 8;
constexpr int8_t _ls_king_moves_directions[] = {8, 7, -1, -9, -8, -7, 1, 9};
constexpr ls_board_state_t _ls_king_moves_from_masks[] = {
    0x00FFFFFFFFFFFFFF, // Up
    0x00FEFEFEFEFEFEFE, // Up-Right
    0xFEFEFEFEFEFEFEFE, // Right
    0xFEFEFEFEFEFEFE00, // Down-Right
    0xFFFFFFFFFFFFFF00, // Down
    0x7F7F7F7F7F7F7F00, // Down-Left
    0x7F7F7F7F7F7F7F7F, // Left
    0x007F7F7F7F7F7F7F // Up-Left
};

constexpr uint8_t _ls_queen_moves = 8;
constexpr int8_t _ls_queen_moves_directions[] = {8, 7, -1, -9, -8, -7, 1, 9};
constexpr ls_board_state_t _ls_queen_moves_from_masks[] = {
    0x00FFFFFFFFFFFFFF, // Up
    0x00FEFEFEFEFEFEFE, // Up-Right
    0xFEFEFEFEFEFEFEFE, // Right
    0xFEFEFEFEFEFEFE00, // Down-Right
    0xFFFFFFFFFFFFFF00, // Down
    0x7F7F7F7F7F7F7F00, // Down-Left
    0x7F7F7F7F7F7F7F7F, // Left
    0x007F7F7F7F7F7F7F // Up-Left
};

constexpr uint8_t _ls_bishop_moves = 4;
constexpr int8_t _ls_bishop_moves_directions[] = {7, -9, -7, 9};
constexpr ls_board_state_t _ls_bishop_moves_from_masks[] = {
    0x00FEFEFEFEFEFEFE, // Up-Right
    0xFEFEFEFEFEFEFE00, // Down-Right
    0x7F7F7F7F7F7F7F00, // Down-Left
    0x007F7F7F7F7F7F7F // Up-Left
};

constexpr uint8_t _ls_knight_moves = 8;
constexpr int8_t _ls_knight_moves_directions[] = {15, 6, -10, -17, -15, -6, 10, 17};
constexpr ls_board_state_t _ls_knight_moves_from_masks[] = {
    0x0000FEFEFEFEFEFE, // Up-Left
    0x00FCFCFCFCFCFCFC, // Right-Up
    0xFCFCFCFCFCFCFC00, // Right-Bottom
    0xFEFEFEFEFEFE0000, // Down-Right
    0x7F7F7F7F7F7F0000, // Down-Left
    0x3F3F3F3F3F3F3F00, // Left-Down
    0x003F3F3F3F3F3F3F, // Left-Up
    0x00007F7F7F7F7F7F // Up-Left
};

constexpr uint8_t _ls_rook_moves = 4;
constexpr int8_t _ls_rook_moves_directions[] = {8, -1, -8, 1};
constexpr ls_board_state_t _ls_rook_moves_from_masks[] = {
    0x00FFFFFFFFFFFFFF, // Up
    0xFEFEFEFEFEFEFEFE, // Right
    0xFFFFFFFFFFFFFF00, // Down
    0x7F7F7F7F7F7F7F7F // Left
};

#endif
