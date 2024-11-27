
#ifndef LIGHTSHARK_BOARD_H
#define LIGHTSHARK_BOARD_H

#include "LSTypes.h"

ls_board_t ls_board_init();
void ls_board_destroy(ls_board_t board);

void ls_board_print(ls_board_t board);
void ls_board_start(ls_board_t board);
char* ls_board_to_string(ls_board_t board);

#endif
