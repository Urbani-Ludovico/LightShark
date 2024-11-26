
#ifndef LIGHTSHARK_TREE_H
#define LIGHTSHARK_TREE_H

#define _LS_TREE_CHILDREN_ARRAY_INCREMENT 20

#include <stdlib.h>
#include <stdint.h>

#include "LSBoard.h"

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

typedef uint8_t ls_state_capture_t; // 0 0 0 Queen Bishop Knight Rock Pawn

typedef struct _ls_state_t* ls_state_t;

struct _ls_state_t {
    // Board
    ls_board_t board;

    // Board status
    ls_check_t is_check;
    ls_state_capture_t capture;
    ls_player_t turn;

    // Tree
    ls_state_t parent;
    ls_state_t* moves;
    uint16_t moves_length;
    uint16_t _moves_array_length;
    ls_state_t next_move;
};

ls_state_t ls_tree_init();
void ls_tree_destroy(ls_state_t tree);

void ls_tree_insert_move(ls_state_t tree, ls_state_t child);
ls_state_t ls_tree_insert_board_move(ls_state_t tree, ls_board_t board);

#endif
