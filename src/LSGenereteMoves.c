
#include "LSGenereteMoves.h"

#include "LSBoard.h"
#include "LSMoves.h"
#include "LSState.h"
#include "LSTree.h"


ls_state_moves_generation_status ls_state_moves_generate(ls_state_t const state) {
    if (state->moves_length != 0) return LS_STATE_GENERATION_MOVES_ALREADY_DONE;
    if (state->turn == LS_UNDEFINED_PLAYER) return LS_STATE_GENERATION_MOVES_PLAYER_UNDEFINED;

    ls_board_state_t const empty_squares = ~(state->turn == LS_PLAYER_WHITE ? ls_board_occupied_mask_white(state->board) : ls_board_occupied_mask_black(state->board));
    ls_board_state_t const opponent_positions = state->turn == LS_PLAYER_WHITE ? ls_board_occupied_mask_black(state->board) : ls_board_occupied_mask_white(state->board);

    // King
    ls_board_state_t const king = state->turn == LS_PLAYER_WHITE ? state->board->white_king : state->board->black_king;
    ls_board_state_t const queen = state->turn == LS_PLAYER_WHITE ? state->board->white_queen : state->board->black_queen;
    for (uint8_t i = 0; i < 64; i++) {
        if (king & (1ULL << i)) {
            for (uint8_t move = 0; move < _ls_king_moves; move++) {
                if (_ls_king_moves_from_masks[move] & (1ULL << i)) {
                    ls_board_state_t new_king = (_ls_king_moves_directions[move] > 0 ? (1ULL << (i + _ls_king_moves_directions[move])) : (1ULL >> (i - _ls_king_moves_directions[move]))) & empty_squares;

                    if (new_king) {
                        new_king |= (king & ~(1ULL << i));

                        ls_board_t const new_board = ls_board_copy(state->board);
                        if (state->turn == LS_PLAYER_WHITE) {
                            new_board->white_king = new_king;
                        } else {
                            new_board->black_king = new_king;
                        }

                        if (!ls_state_is_board_check(new_board, state->turn)) {
                            ls_tree_insert_board_move(state, new_board);
                        } else {
                            ls_board_destroy(new_board);
                        }
                    }
                }
            }
        }

        // Queen
        if (queen & (1ULL << i)) {
            for (uint8_t move = 0; move < _ls_queen_moves; move++) {
                ls_board_state_t new_queen = (1ULL << i);
                for (uint8_t move_step = 0; move_step < _ls_queen_moves; move_step++) {
                    if (_ls_queen_moves_from_masks[move] & new_queen) {
                        new_queen = (_ls_king_moves_directions[move] > 0 ? (new_queen << _ls_king_moves_directions[move]) : (new_queen >> -_ls_king_moves_directions[move])) & empty_squares;

                        if (new_queen) {
                            new_queen |= (queen & ~(1ULL << i));

                            ls_board_t const new_board = ls_board_copy(state->board);
                            if (state->turn == LS_PLAYER_WHITE) {
                                new_board->white_queen = new_queen;
                            } else {
                                new_board->black_queen = new_queen;
                            }

                            if (!ls_state_is_board_check(new_board, state->turn)) {
                                ls_tree_insert_board_move(state, new_board);
                            } else {
                                ls_board_destroy(new_board);
                            }

                            if (new_queen & opponent_positions) {
                                break;
                            }
                        } else break;
                    }
                }
            }
        }
    }

    return state->moves_length > 0 ? LS_STATE_GENERATION_MOVES_DONE : LS_STATE_GENERATION_MOVES_EMPTY;
}
