
#include "LSEngine.h"

ls_t ls_init() {
    const auto engine = (ls_t)calloc(1, sizeof(struct _ls_t));

    engine->tree = ls_tree_init();
    engine->tree->board = ls_board_init();
    engine->board = engine->tree->board;

    ls_board_start(engine->board);

    return engine;
}

void ls_destroy(const ls_t engine) {
    ls_tree_destroy(engine->tree);

    free(engine);
}
