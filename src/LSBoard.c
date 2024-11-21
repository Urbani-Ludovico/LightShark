
#include "LSBoard.h"

ls_board_t ls_board_init() {
    const auto board = (ls_board_t)calloc(1, sizeof(struct _ls_board_t));

    return board;
}

void ls_board_destroy(const ls_board_t board) {
    free(board);
}