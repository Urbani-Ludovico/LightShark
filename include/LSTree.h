
#ifndef TREE_H
#define TREE_H

#include <stdlib.h>

#include "LSBoard.h"

typedef struct _ls_tree_t* ls_tree_t;
struct _ls_tree_t {
    ls_board_t board;

    ls_tree_t *children;
    unsigned int children_length;
};

ls_tree_t ls_tree_init();

#endif
