
#ifndef BOARD_H
#define BOARD_H

#include <stdlib.h>

struct _ls_board_t {

};
typedef struct _ls_board_t* ls_board_t;

ls_board_t ls_board_init();
void ls_board_destroy(ls_board_t board);

void ls_board_start(ls_board_t board);

#endif
