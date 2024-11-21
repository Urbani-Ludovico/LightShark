
#include "LSTree.h"

ls_tree_t ls_tree_init() {
    const auto tree = (ls_tree_t)calloc(1, sizeof(struct _ls_tree_t));

    tree->board = ls_board_init();
    tree->children_length = 0;

    ls_board_start(tree->board);

    return tree;
}