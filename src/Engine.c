
#include "Engine.h"

struct _ls_t {
    ls_board_t board;
    ls_tree_t tree;
};

ls_t ls_init() {
    const auto engine = (ls_t)calloc(1, sizeof(struct _ls_t));

    return engine;
}

void ls_destroy(const ls_t engine) {
    free(engine);
}