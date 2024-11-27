
#include "LSGenereteMoves.h"

#include "LSBoard.h"
#include "LSMoves.h"
#include "LSState.h"
#include "LSTree.h"


ls_state_moves_generation_status ls_state_moves_generate(ls_state_t const state) {
    if (state->moves_length != 0) return LS_STATE_GENERATION_MOVES_ALREADY_DONE;
    if (state->turn == LS_UNDEFINED_PLAYER) return LS_STATE_GENERATION_MOVES_PLAYER_UNDEFINED;

    ls_board_state_t const occupied = ~(state->turn == LS_PLAYER_WHITE ? ls_board_occupied_mask_white(state->board) : ls_board_occupied_mask_black(state->board));

    // King
    ls_board_state_t const king = state->turn == LS_PLAYER_WHITE ? state->board->white_king : state->board->black_king;
    ls_board_state_t king_shift = king;
    for (uint8_t i = 0; i < 64; i++) {
        if (king_shift % 2 == 0) {
            ls_board_state_t const this_king = 1ULL << i;

            for (uint8_t j = 0; j < _ls_king_moves; j++) {
                ls_board_state_t new_this_king = this_king & _ls_king_moves_from_masks[j];
                new_this_king = _ls_king_moves_directions[j] > 0 ? new_this_king << _ls_king_moves_directions[j] : new_this_king >> -_ls_king_moves_directions[j];
                new_this_king &= occupied;

                if (new_this_king) {
                    ls_board_state_t const new_king = (king & ~this_king) | new_this_king;

                    ls_board_t const new_board = ls_board_copy(state->board);

                    if (state->turn == LS_PLAYER_WHITE) {
                        new_board->white_king = new_king;
                    } else {
                        new_board->black_king = new_king;
                    }

                    if (ls_state_is_board_check(new_board, state->turn) == false) {
                        ls_tree_insert_board_move(state, new_board);
                    } else {
                        ls_board_destroy(new_board);
                    }
                }
            }
        }

        king_shift >>= 1;
    }

    return state->moves_length > 0 ? LS_STATE_GENERATION_MOVES_DONE : LS_STATE_GENERATION_MOVES_EMPTY;
}
