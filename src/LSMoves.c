
#include "LSMoves.h"

ls_state_moves_generation_status ls_state_moves_generate(ls_state_t const state) {
    if (state->moves_length != 0) return LS_STATE_GENERATION_ALREADY_DONE;

    return state->moves_length > 0 ? LS_STATE_GENERATION_DONE : LS_STATE_GENERATION_EMPTY;
}