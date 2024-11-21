
#include "LSTree.h"

struct _ls_tree_t {
    ls_board_t board;

    ls_tree_t *children;
    unsigned int children_length;
};

ls_tree_t ls_tree_init() {
    const auto tree = (ls_tree_t)calloc(1, sizeof(struct _ls_tree_t));

    tree->board = ls_board_init();
    tree->children_length = 0;

    return tree;
}