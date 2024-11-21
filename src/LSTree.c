
#include "LSTree.h"

struct _ls_tree_t {
    ls_board_t board;

    ls_tree_t *children;
    unsigned int children_length;
};