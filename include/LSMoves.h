
#ifndef LSMOVES_H
#define LSMOVES_H

#include "LSTree.h"

enum _ls_state_moves_generation_status {
    LS_STATE_GENERATION_DONE,
    LS_STATE_GENERATION_FAILED,
    LS_STATE_GENERATION_EMPTY,
    LS_STATE_GENERATION_ALREADY_DONE
};

typedef enum _ls_state_moves_generation_status ls_state_moves_generation_status;

ls_state_moves_generation_status ls_state_moves_generate(ls_state_t state);

#endif
