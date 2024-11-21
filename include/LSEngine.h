#ifndef ENGINE_H
#define ENGINE_H

#include <stdlib.h>

#include "LSBoard.h"
#include "LSTree.h"

struct _ls_t {
    ls_board_t board;
    ls_tree_t tree;
};

typedef struct _ls_t* ls_t;

ls_t ls_init();
void ls_destroy(ls_t engine);

#endif
