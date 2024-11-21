
#ifndef TREE_H
#define TREE_H

#include <stdlib.h>

#include "LSBoard.h"
#include <stdint.h>

typedef struct _ls_tree_t* ls_tree_t;
struct _ls_tree_t {
    ls_board_t board;

    ls_tree_t *children;
    uint16_t children_length;
};

ls_tree_t ls_tree_init();
void ls_tree_destroy(ls_tree_t tree);

#endif
