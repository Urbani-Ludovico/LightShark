
#include "LSTree.h"

ls_tree_t ls_tree_init() {
    const auto tree = (ls_tree_t)malloc(sizeof(struct _ls_tree_t));

    tree->board = nullptr;

    tree->children = nullptr;
    tree->children_length = 0;
    tree->_children_array_length = 0;

    return tree;
}

void ls_tree_destroy(const ls_tree_t tree) {
    if (tree->_children_array_length > 0) {
        for (uint16_t i = 0; i < tree->children_length; i++) {
            ls_tree_destroy(tree->children[i]);
        }
        free(tree->children);
    }

    ls_board_destroy(tree->board);

    free(tree);
}

ls_tree_t ls_tree_insert_child(const ls_tree_t tree, const ls_board_t board) {
    if (tree->_children_array_length == 0) {
        tree->children = (ls_tree_t*)malloc(sizeof(ls_tree_t) * _LS_TREE_CHILDREN_ARRAY_INCREMENT);
        tree->_children_array_length = _LS_TREE_CHILDREN_ARRAY_INCREMENT;
    } else if (tree->children_length == tree->_children_array_length) {
        tree->_children_array_length += _LS_TREE_CHILDREN_ARRAY_INCREMENT;
        const auto new_children = (ls_tree_t*)realloc(tree->children, sizeof(ls_tree_t) * tree->_children_array_length);

        if (new_children == nullptr) {
            exit(1);
        }
        tree->children = new_children;
    }

    const auto new_tree = ls_tree_init();

    tree->children[tree->children_length] = new_tree;
    tree->children[tree->children_length]->board = board;

    tree->children_length++;

    return new_tree;
}
