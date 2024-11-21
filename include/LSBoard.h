
#ifndef BOARD_H
#define BOARD_H

#include <stdlib.h>
#include <stdint.h>

typedef uint64_t ls_board_state_t;

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

typedef struct _ls_board_t* ls_board_t;

ls_board_t ls_board_init();
void ls_board_destroy(ls_board_t board);

void ls_board_start(ls_board_t board);
char* ls_board_to_string(ls_board_t board);

#endif
