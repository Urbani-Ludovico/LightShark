
#ifndef TREE_H
#define TREE_H

#define _LS_TREE_CHILDREN_ARRAY_INCREMENT 20

#include <stdlib.h>

#include "LSBoard.h"
#include <stdint.h>

typedef struct _ls_tree_t* ls_tree_t;

struct _ls_tree_t {
    ls_board_t board;

    ls_tree_t* children;
    uint16_t children_length;
    uint16_t _children_array_length;
};

ls_tree_t ls_tree_init();
void ls_tree_destroy(ls_tree_t tree);

ls_tree_t ls_tree_insert_child(ls_tree_t tree, ls_board_t board);

#endif
