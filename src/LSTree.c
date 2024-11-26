
#include "LSTree.h"

ls_state_t ls_tree_init() {
    auto const tree = (ls_state_t)malloc(sizeof(struct _ls_state_t));

    // Board
    tree->board = nullptr;

    // Board status
    tree->capture = 0x0;
    tree->is_check = LS_UNDEFINED_CHECK;

    // Tree
    tree->parent = nullptr;
    tree->moves = nullptr;
    tree->moves_length = 0;
    tree->_moves_array_length = 0;

    return tree;
}

void ls_tree_destroy(const ls_state_t tree) {
    if (tree->_moves_array_length > 0) {
        for (uint16_t i = 0; i < tree->moves_length; i++) {
            ls_tree_destroy(tree->moves[i]);
        }
        free(tree->moves);
    }

    ls_board_destroy(tree->board);

    free(tree);
}

void ls_tree_insert_move(const ls_state_t tree, const ls_state_t child) {
    if (tree->_moves_array_length == 0) {
        tree->moves = (ls_state_t*)malloc(sizeof(ls_state_t) * _LS_TREE_CHILDREN_ARRAY_INCREMENT);
        tree->_moves_array_length = _LS_TREE_CHILDREN_ARRAY_INCREMENT;
    } else if (tree->moves_length == tree->_moves_array_length) {
        tree->_moves_array_length += _LS_TREE_CHILDREN_ARRAY_INCREMENT;
        auto const new_children = (ls_state_t*)realloc(tree->moves, sizeof(ls_state_t) * tree->_moves_array_length);

        if (new_children == nullptr) {
            exit(1);
        }
        tree->moves = new_children;
    }

    tree->moves[tree->moves_length] = child;
    child->parent = tree;
    tree->moves_length++;
}

ls_state_t ls_tree_insert_board_move(const ls_state_t tree, const ls_board_t board) {
    auto const new_tree = ls_tree_init();
    new_tree->board = board;

    ls_tree_insert_move(tree, new_tree);

    return new_tree;
}