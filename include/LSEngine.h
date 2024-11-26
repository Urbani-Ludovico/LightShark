#ifndef LIGHTSHARK_ENGINE_H
#define LIGHTSHARK_ENGINE_H

#include <stdlib.h>

#include "LSBoard.h"
#include "LSTree.h"

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

typedef struct _ls_t* ls_t;

ls_t ls_init();
void ls_destroy(ls_t engine);

#endif
