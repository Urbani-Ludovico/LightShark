
#include "Board.h"

struct _ls_board_t {

};

ls_board_t ls_board_init() {
    const auto engine = (ls_board_t)calloc(1, sizeof(ls_board_t));

    return engine;
}

void ls_board_destroy(const ls_board_t board) {
    free(board);
}