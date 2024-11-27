
#include "LSGenereteMoves.h"

#include "LSBoard.h"
#include "LSMoves.h"
#include "LSState.h"
#include "LSTree.h"


#ifndef LS_STATE_MOVES_GENERATE_INSERT_MOVE
#define LS_STATE_MOVES_GENERATE_INSERT_MOVE(piece) \
    ls_board_t const new_board = ls_board_copy(state->board); \
    if (state->turn == LS_PLAYER_WHITE) { \
        new_board->white_##piece = new_##piece; \
        new_board->black_king &= ~new_##piece; \
        new_board->black_queen &= ~new_##piece; \
        new_board->black_bishop &= ~new_##piece; \
        new_board->black_knight &= ~new_##piece; \
        new_board->black_rook &= ~new_##piece; \
        new_board->black_pawn &= ~new_##piece; \
    } else { \
        new_board->black_##piece = new_##piece; \
        new_board->white_king &= ~new_##piece; \
        new_board->white_queen &= ~new_##piece; \
        new_board->white_bishop &= ~new_##piece; \
        new_board->white_knight &= ~new_##piece; \
        new_board->white_rook &= ~new_##piece; \
        new_board->white_pawn &= ~new_##piece; \
    } \
    if (!ls_state_is_board_check(new_board, state->turn)) { \
        ls_tree_insert_board_move(state, new_board); \
    } else { \
        ls_board_destroy(new_board); \
    }
#endif


ls_state_moves_generation_status ls_state_moves_generate(ls_state_t const state) {
    if (state->moves_length != 0) return LS_STATE_GENERATION_MOVES_ALREADY_DONE;
    if (state->turn == LS_UNDEFINED_PLAYER) return LS_STATE_GENERATION_MOVES_PLAYER_UNDEFINED;

    ls_board_state_t const empty_squares = ~(state->turn == LS_PLAYER_WHITE ? ls_board_occupied_mask_white(state->board) : ls_board_occupied_mask_black(state->board));
    ls_board_state_t const opponent_positions = state->turn == LS_PLAYER_WHITE ? ls_board_occupied_mask_black(state->board) : ls_board_occupied_mask_white(state->board);

    // King
    ls_board_state_t const king = state->turn == LS_PLAYER_WHITE ? state->board->white_king : state->board->black_king;
    ls_board_state_t const queen = state->turn == LS_PLAYER_WHITE ? state->board->white_queen : state->board->black_queen;
    ls_board_state_t const bishop = state->turn == LS_PLAYER_WHITE ? state->board->white_bishop : state->board->black_bishop;
    ls_board_state_t const knight = state->turn == LS_PLAYER_WHITE ? state->board->white_knight : state->board->black_knight;
    ls_board_state_t const rook = state->turn == LS_PLAYER_WHITE ? state->board->white_rook : state->board->black_rook;
    ls_board_state_t const pawn = state->turn == LS_PLAYER_WHITE ? state->board->white_pawn : state->board->black_pawn;
    for (uint8_t i = 0; i < 64; i++) {
        // King
        if (king & (1ULL << i)) {
            for (uint8_t move = 0; move < _ls_king_moves; move++) {
                if (_ls_king_moves_from_masks[move] & (1ULL << i)) {
                    ls_board_state_t new_king = (_ls_king_moves_directions[move] > 0 ? (1ULL << (i + _ls_king_moves_directions[move])) : (1ULL >> (i - _ls_king_moves_directions[move]))) & empty_squares;

                    if (new_king) {
                        new_king |= (king & ~(1ULL << i));

                        LS_STATE_MOVES_GENERATE_INSERT_MOVE(king)
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

                            LS_STATE_MOVES_GENERATE_INSERT_MOVE(queen)

                            if (new_queen & opponent_positions) {
                                break;
                            }
                        } else break;
                    }
                }
            }
        }

        // Bishop
        if (bishop & (1ULL << i)) {
            for (uint8_t move = 0; move < _ls_bishop_moves; move++) {
                ls_board_state_t new_bishop = (1ULL << i);
                for (uint8_t move_step = 0; move_step < _ls_queen_moves; move_step++) {
                    if (_ls_queen_moves_from_masks[move] & new_bishop) {
                        new_bishop = (_ls_king_moves_directions[move] > 0 ? (new_bishop << _ls_king_moves_directions[move]) : (new_bishop >> -_ls_king_moves_directions[move])) & empty_squares;

                        if (new_bishop) {
                            new_bishop |= (queen & ~(1ULL << i));

                            LS_STATE_MOVES_GENERATE_INSERT_MOVE(bishop)

                            if (new_bishop & opponent_positions) {
                                break;
                            }
                        } else break;
                    }
                }
            }
        }

        // Knight
        if (knight & (1ULL << i)) {
            for (uint8_t move = 0; move < _ls_knight_moves; move++) {
                if (_ls_knight_moves_from_masks[move] & (1ULL << i)) {
                    ls_board_state_t new_knight = (_ls_knight_moves_directions[move] > 0 ? (1ULL << (i + _ls_knight_moves_directions[move])) : (1ULL >> (i - _ls_knight_moves_directions[move]))) & empty_squares;

                    if (new_knight) {
                        new_knight |= (king & ~(1ULL << i));

                        LS_STATE_MOVES_GENERATE_INSERT_MOVE(knight)
                    }
                }
            }
        }

        // Rook
        if (rook & (1ULL << i)) {
            for (uint8_t move = 0; move < _ls_rook_moves; move++) {
                ls_board_state_t new_rook = (1ULL << i);
                for (uint8_t move_step = 0; move_step < _ls_queen_moves; move_step++) {
                    if (_ls_queen_moves_from_masks[move] & new_rook) {
                        new_rook = (_ls_king_moves_directions[move] > 0 ? (new_rook << _ls_king_moves_directions[move]) : (new_rook >> -_ls_king_moves_directions[move])) & empty_squares;

                        if (new_rook) {
                            new_rook |= (queen & ~(1ULL << i));

                            LS_STATE_MOVES_GENERATE_INSERT_MOVE(rook)

                            if (new_rook & opponent_positions) {
                                break;
                            }
                        } else break;
                    }
                }
            }
        }

        // Pawn
        if (pawn & (1ULL << i)) {
            if ((state->turn == LS_PLAYER_WHITE ? 0x00FFFFFFFFFFFFFF : 0xFFFFFFFFFFFFFF00) & (1ULL << i)) {
                ls_board_state_t new_pawn = (state->turn == LS_PLAYER_WHITE ? (1ULL << (i + 8)) : (1ULL >> (i - 8))) & empty_squares;

                if (new_pawn) {
                    new_pawn |= (pawn & ~(1ULL << i));

                    LS_STATE_MOVES_GENERATE_INSERT_MOVE(pawn)
                }
            }

            if ((state->turn == LS_PLAYER_WHITE ? 0x007F7F7F7F7F7F7F : 0x7F7F7F7F7F7F7F00) & (1ULL << i)) {
                ls_board_state_t new_pawn = (state->turn == LS_PLAYER_WHITE ? (1ULL << (i + 9)) : (1ULL >> (i - 7))) & opponent_positions;

                if (new_pawn) {
                    new_pawn |= (pawn & ~(1ULL << i));

                    LS_STATE_MOVES_GENERATE_INSERT_MOVE(pawn)
                }
            }

            if ((state->turn == LS_PLAYER_WHITE ? 0x00FEFEFEFEFEFEFE : 0xFEFEFEFEFEFEFE00) & (1ULL << i)) {
                ls_board_state_t new_pawn = (state->turn == LS_PLAYER_WHITE ? (1ULL << (i + 7)) : (1ULL >> (i - 9))) & opponent_positions;

                if (new_pawn) {
                    new_pawn |= (pawn & ~(1ULL << i));

                    LS_STATE_MOVES_GENERATE_INSERT_MOVE(pawn)
                }
            }

            if ((state->turn == LS_PLAYER_WHITE ? 0x000000000000FF00 : 0x00FF000000000000) & (1ULL << i)) {
                ls_board_state_t new_pawn = (state->turn == LS_PLAYER_WHITE ? (1ULL << (i + 16)) : (1ULL >> (i - 16))) & opponent_positions;

                if (new_pawn) {
                    new_pawn |= (pawn & ~(1ULL << i));

                    LS_STATE_MOVES_GENERATE_INSERT_MOVE(pawn)
                }
            }
        }
    }

    return state->moves_length > 0 ? LS_STATE_GENERATION_MOVES_DONE : LS_STATE_GENERATION_MOVES_EMPTY;
}
