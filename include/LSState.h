
#ifndef LSBOARDSTATUS_H
#define LSBOARDSTATUS_H

#include "LSTypes.h"

ls_check_t ls_state_is_check(ls_state_t state);
bool ls_state_is_board_check(ls_board_t board, ls_player_t player);

ls_board_state_t ls_board_occupied_mask(ls_board_t board);
ls_board_state_t ls_board_occupied_mask_white(ls_board_t board);
ls_board_state_t ls_board_occupied_mask_black(ls_board_t board);


#endif
