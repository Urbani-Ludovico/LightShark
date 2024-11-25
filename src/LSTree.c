
#include "LSTree.h"

ls_state_t ls_tree_init() {
    auto const tree = (ls_state_t)malloc(sizeof(struct _ls_state_t));

    // Board
    tree->board = nullptr;

    // Board status
    tree->capture = 0x0;

    // Tree
    tree->parent = nullptr;
    tree->children = nullptr;
    tree->children_length = 0;
    tree->_children_array_length = 0;

    return tree;
}

void ls_tree_destroy(const ls_state_t tree) {
    if (tree->_children_array_length > 0) {
        for (uint16_t i = 0; i < tree->children_length; i++) {
            ls_tree_destroy(tree->children[i]);
        }
        free(tree->children);
    }

    ls_board_destroy(tree->board);

    free(tree);
}

ls_state_t ls_tree_insert_child(const ls_state_t tree, const ls_board_t board) {
    if (tree->_children_array_length == 0) {
        tree->children = (ls_state_t*)malloc(sizeof(ls_state_t) * _LS_TREE_CHILDREN_ARRAY_INCREMENT);
        tree->_children_array_length = _LS_TREE_CHILDREN_ARRAY_INCREMENT;
    } else if (tree->children_length == tree->_children_array_length) {
        tree->_children_array_length += _LS_TREE_CHILDREN_ARRAY_INCREMENT;
        auto const new_children = (ls_state_t*)realloc(tree->children, sizeof(ls_state_t) * tree->_children_array_length);

        if (new_children == nullptr) {
            exit(1);
        }
        tree->children = new_children;
    }

    auto const new_tree = ls_tree_init();
    new_tree->parent = tree;

    tree->children[tree->children_length] = new_tree;
    tree->children[tree->children_length]->board = board;

    tree->children_length++;

    return new_tree;
}
