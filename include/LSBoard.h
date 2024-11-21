
#ifndef BOARD_H
#define BOARD_H

#include <stdlib.h>

typedef struct _ls_board_t* ls_board_t;

ls_board_t ls_board_init();
void ls_board_destroy(ls_board_t board);

#endif
