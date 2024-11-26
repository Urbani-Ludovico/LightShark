
#ifndef LSMOVES_H
#define LSMOVES_H

#include "LSTree.h"
#include "LSState.h"

enum _ls_state_moves_generation_moves_status {
    LS_STATE_GENERATION_MOVES_DONE,
    LS_STATE_GENERATION_MOVES_FAILED,
    LS_STATE_GENERATION_MOVES_EMPTY,
    LS_STATE_GENERATION_MOVES_ALREADY_DONE,
    LS_STATE_GENERATION_MOVES_PLAYER_UNDEFINED
};

typedef enum _ls_state_moves_generation_moves_status ls_state_moves_generation_status;

ls_state_moves_generation_status ls_state_moves_generate(ls_state_t state);

#endif
