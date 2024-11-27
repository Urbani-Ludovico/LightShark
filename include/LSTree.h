
#ifndef LIGHTSHARK_TREE_H
#define LIGHTSHARK_TREE_H

#include "LSTypes.h"

ls_state_t ls_tree_init();
void ls_tree_destroy(ls_state_t tree);

void ls_tree_insert_move(ls_state_t tree, ls_state_t child);
ls_state_t ls_tree_insert_board_move(ls_state_t tree, ls_board_t board);

#endif
