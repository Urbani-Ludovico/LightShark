
#ifndef LSTYPES_H
#define LSTYPES_H

#include <stdint.h>

// Parameters

enum _ls_player_t {
    LS_PLAYER_WHITE,
    LS_PLAYER_BLACK,
    LS_UNDEFINED_PLAYER
};

typedef enum _ls_player_t ls_player_t;

enum _ls_check_t {
    LS_CHECK_WHITE,
    LS_CHECK_BLACK,
    LS_NO_CHECK,
    LS_UNDEFINED_CHECK
};

typedef enum _ls_check_t ls_check_t;

enum _ls_state_moves_generation_moves_status {
    LS_STATE_GENERATION_MOVES_DONE,
    LS_STATE_GENERATION_MOVES_FAILED,
    LS_STATE_GENERATION_MOVES_EMPTY,
    LS_STATE_GENERATION_MOVES_ALREADY_DONE,
    LS_STATE_GENERATION_MOVES_PLAYER_UNDEFINED
};

typedef enum _ls_state_moves_generation_moves_status ls_state_moves_generation_status;

// Types

typedef struct _ls_t* ls_t;

typedef struct _ls_state_t* ls_state_t;
typedef struct _ls_board_t* ls_board_t;
typedef uint64_t ls_board_state_t;

struct _ls_t {
    // Board and tree
    ls_board_t board;
    ls_state_t state;
    ls_state_t tree;

    // Game status
    ls_player_t turn;
    uint16_t moves_count;
    uint8_t captured_white_queen;
    uint8_t captured_white_rock;
    uint8_t captured_white_knight;
    uint8_t captured_white_bishop;
    uint8_t captured_white_pawn;
    uint8_t captured_black_queen;
    uint8_t captured_black_rock;
    uint8_t captured_black_knight;
    uint8_t captured_black_bishop;
    uint8_t captured_black_pawn;
};

struct _ls_state_t {
    // Board
    ls_board_t board;

    // Board status
    ls_check_t is_check;
    ls_player_t turn;

    // Tree
    ls_state_t parent;
    ls_state_t* moves;
    uint16_t moves_length;
    uint16_t _moves_array_length;
    ls_state_t next_move;
};

struct _ls_board_t {
    ls_board_state_t white_king;
    ls_board_state_t white_queen;
    ls_board_state_t white_rock;
    ls_board_state_t white_knight;
    ls_board_state_t white_bishop;
    ls_board_state_t white_pawn;

    ls_board_state_t black_king;
    ls_board_state_t black_queen;
    ls_board_state_t black_rock;
    ls_board_state_t black_knight;
    ls_board_state_t black_bishop;
    ls_board_state_t black_pawn;
};

#endif
