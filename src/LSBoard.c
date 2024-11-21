
#include "LSBoard.h"

ls_board_t ls_board_init() {
    const auto board = (ls_board_t)calloc(1, sizeof(struct _ls_board_t));

    return board;
}

void ls_board_destroy(const ls_board_t board) {
    free(board);
}

void ls_board_start(const ls_board_t board) {
    board->white_king = 0x8;
    board->white_queen = 0x10;
    board->white_rock = 0x81;
    board->white_knight = 0x42;
    board->white_bishop = 0x24;
    board->white_pawn = 0xff00;

    board->black_king = 0x800000000000000;
    board->black_queen = 0x1000000000000000;
    board->black_rock = 0x8100000000000000;
    board->black_knight = 0x4200000000000000;
    board->black_bishop = 0x2400000000000000;
    board->black_pawn = 0xff000000000000;
    
}
