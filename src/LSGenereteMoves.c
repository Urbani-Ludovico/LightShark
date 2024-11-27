
#include "LSGenereteMoves.h"

#include <stdlib.h>

#include "LSBoard.h"
#include "LSMoves.h"
#include "LSState.h"
#include "LSTree.h"

#ifndef LS_STATE_MOVES_GENERATE_INSERT_MOVE_CHECK
#define LS_STATE_MOVES_GENERATE_INSERT_MOVE_CHECK \
    if (!ls_state_is_board_check(new_board, state->turn)) { \
        ls_tree_insert_board_move(state, new_board); \
    } else { \
        ls_board_destroy(new_board); \
    }
#endif

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
    LS_STATE_MOVES_GENERATE_INSERT_MOVE_CHECK
#endif


ls_state_moves_generation_status ls_state_moves_generate(ls_state_t const state) {
    if (state->moves_length != 0) return LS_STATE_GENERATION_MOVES_ALREADY_DONE;
    if (state->turn == LS_UNDEFINED_PLAYER) return LS_STATE_GENERATION_MOVES_PLAYER_UNDEFINED;

    ls_board_state_t const empty_player_squares = ~(state->turn == LS_PLAYER_WHITE ? ls_board_occupied_mask_white(state->board) : ls_board_occupied_mask_black(state->board));
    ls_board_state_t const opponent_positions = state->turn == LS_PLAYER_WHITE ? ls_board_occupied_mask_black(state->board) : ls_board_occupied_mask_white(state->board);
    ls_board_state_t const empty_squares = ~ls_board_occupied_mask(state->board);

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
                    ls_board_state_t new_king = (1ULL << (i + _ls_king_moves_directions[move])) & empty_player_squares;

                    if (new_king) {
                        new_king |= king & ~(1ULL << i);

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
                        new_queen = (_ls_king_moves_directions[move] > 0 ? (new_queen << _ls_king_moves_directions[move]) : (new_queen >> -_ls_king_moves_directions[move])) & empty_player_squares;

                        if (new_queen) {
                            new_queen |= queen & ~(1ULL << i);

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
                        new_bishop = (_ls_king_moves_directions[move] > 0 ? (new_bishop << _ls_king_moves_directions[move]) : (new_bishop >> -_ls_king_moves_directions[move])) & empty_player_squares;

                        if (new_bishop) {
                            new_bishop |= queen & ~(1ULL << i);

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
                    ls_board_state_t new_knight = (1ULL << (i + _ls_knight_moves_directions[move])) & empty_player_squares;

                    if (new_knight) {
                        new_knight |= king & ~(1ULL << i);

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
                        new_rook = (_ls_king_moves_directions[move] > 0 ? (new_rook << _ls_king_moves_directions[move]) : (new_rook >> -_ls_king_moves_directions[move])) & empty_player_squares;

                        if (new_rook) {
                            new_rook |= queen & ~(1ULL << i);

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
            // Forward
            if ((state->turn == LS_PLAYER_WHITE ? 0x0000FFFFFFFFFFFF : 0xFFFFFFFFFFFF0000) & (1ULL << i)) {
                ls_board_state_t new_pawn = (state->turn == LS_PLAYER_WHITE ? (1ULL << (i + 8)) : (1ULL << (i - 8))) & empty_squares;
                if (new_pawn) {
                    new_pawn |= pawn & ~(1ULL << i);
                    LS_STATE_MOVES_GENERATE_INSERT_MOVE(pawn)
                }
            }

            // Eat left
            if ((state->turn == LS_PLAYER_WHITE ? 0x007F7F7F7F7F7F7F : 0x7F7F7F7F7F7F7F00) & (1ULL << i)) {
                ls_board_state_t new_pawn = (state->turn == LS_PLAYER_WHITE ? (1ULL << (i + 9)) : (1ULL << (i - 7))) & opponent_positions;
                if (new_pawn) {
                    new_pawn |= pawn & ~(1ULL << i);
                    LS_STATE_MOVES_GENERATE_INSERT_MOVE(pawn)
                }
            }

            // Eat right
            if ((state->turn == LS_PLAYER_WHITE ? 0x00FEFEFEFEFEFEFE : 0xFEFEFEFEFEFEFE00) & (1ULL << i)) {
                ls_board_state_t new_pawn = (state->turn == LS_PLAYER_WHITE ? (1ULL << (i + 7)) : (1ULL << (i - 9))) & opponent_positions;
                if (new_pawn) {
                    new_pawn |= pawn & ~(1ULL << i);
                    LS_STATE_MOVES_GENERATE_INSERT_MOVE(pawn)
                }
            }

            if (state->turn == LS_PLAYER_WHITE) {
                // Upgrade
                if ((0x00FF000000000000 & (1ULL << i)) && (empty_squares & (1ULL << (i + 8)))) {
                    ls_board_t new_board = ls_board_copy(state->board);
                    new_board->white_pawn = pawn & ~(1ULL << i);
                    new_board->white_queen |= 1ULL << i;
                    LS_STATE_MOVES_GENERATE_INSERT_MOVE_CHECK

                    new_board = ls_board_copy(state->board);
                    new_board->white_pawn = pawn & ~(1ULL << i);
                    new_board->white_bishop |= 1ULL << i;
                    LS_STATE_MOVES_GENERATE_INSERT_MOVE_CHECK

                    new_board = ls_board_copy(state->board);
                    new_board->white_pawn = pawn & ~(1ULL << i);
                    new_board->white_knight |= 1ULL << i;
                    LS_STATE_MOVES_GENERATE_INSERT_MOVE_CHECK

                    new_board = ls_board_copy(state->board);
                    new_board->white_pawn = pawn & ~(1ULL << i);
                    new_board->white_rook |= 1ULL << i;
                    LS_STATE_MOVES_GENERATE_INSERT_MOVE_CHECK
                }

                // Double forward
                if ((0x000000000000FF00 & (1ULL << i)) && (empty_squares & (1ULL << (i + 8))) && (empty_squares & (1ULL << (i + 16)))) {
                    ls_board_state_t const new_pawn = (1ULL << (i + 16)) | (pawn & ~(1ULL << i));
                    LS_STATE_MOVES_GENERATE_INSERT_MOVE(pawn)
                }

                // En-passant
                if (state->parent != nullptr) {
                    if ((0x0000007F00000000 & (1ULL << i)) && (state->board->white_pawn & (1ULL << (i + 1))) && (state->parent->board->white_pawn & (1ULL << (i + 17)))) {
                        ls_board_t const new_board = ls_board_copy(state->board);
                        new_board->white_pawn = (1ULL << (i + 9)) | (pawn & ~(1ULL << i));
                        new_board->black_pawn = new_board->black_pawn & ~(1ULL << (i + 1));
                        LS_STATE_MOVES_GENERATE_INSERT_MOVE_CHECK
                    } else if ((0x000000FE00000000 & (1ULL << i)) && (state->board->white_pawn & (1ULL << (i - 1))) && (state->parent->board->white_pawn & (1ULL << (i + 15)))) {
                        ls_board_t const new_board = ls_board_copy(state->board);
                        new_board->white_pawn = (1ULL << (i + 7)) | (pawn & ~(1ULL << i));
                        new_board->black_pawn = new_board->black_pawn & ~(1ULL << (i - 1));
                        LS_STATE_MOVES_GENERATE_INSERT_MOVE_CHECK
                    }
                }
            } else {
                // Upgrade
                if ((0x000000000000FF00 & (1ULL << i)) && (empty_squares & (1ULL << (i - 8)))) {
                    ls_board_t new_board = ls_board_copy(state->board);
                    new_board->black_pawn = pawn & ~(1ULL << i);
                    new_board->black_queen |= 1ULL << i;
                    LS_STATE_MOVES_GENERATE_INSERT_MOVE_CHECK

                    new_board = ls_board_copy(state->board);
                    new_board->black_pawn = pawn & ~(1ULL << i);
                    new_board->black_bishop |= 1ULL << i;
                    LS_STATE_MOVES_GENERATE_INSERT_MOVE_CHECK

                    new_board = ls_board_copy(state->board);
                    new_board->black_pawn = pawn & ~(1ULL << i);
                    new_board->black_knight |= 1ULL << i;
                    LS_STATE_MOVES_GENERATE_INSERT_MOVE_CHECK

                    new_board = ls_board_copy(state->board);
                    new_board->black_pawn = pawn & ~(1ULL << i);
                    new_board->black_rook |= 1ULL << i;
                    LS_STATE_MOVES_GENERATE_INSERT_MOVE_CHECK
                }

                // Double forward
                if ((0x00FF000000000000 & (1ULL << i)) && (empty_squares & (1ULL << (i - 8))) && (empty_squares & (1ULL << (i - 16)))) {
                    ls_board_state_t const new_pawn = (1ULL << (i - 16)) | (pawn & ~(1ULL << i));
                    LS_STATE_MOVES_GENERATE_INSERT_MOVE(pawn)
                }

                // En-passant
                if (state->parent != nullptr) {
                    if ((0x000000007F000000 & (1ULL << i)) && (state->board->white_pawn & (1ULL << (i + 1))) && (state->parent->board->white_pawn & (1ULL << (i - 15)))) {
                        ls_board_t const new_board = ls_board_copy(state->board);
                        new_board->black_pawn = (1ULL << (i - 7)) | (pawn & ~(1ULL << i));
                        new_board->white_pawn = new_board->white_pawn & ~(1ULL << (i + 1));
                        LS_STATE_MOVES_GENERATE_INSERT_MOVE_CHECK
                    } else if ((0x00000000FE000000 & (1ULL << i)) && (state->board->white_pawn & (1ULL << (i - 1))) && (state->parent->board->white_pawn & (1ULL << (i - 17)))) {
                        ls_board_t const new_board = ls_board_copy(state->board);
                        new_board->black_pawn = (1ULL << (i - 9)) | (pawn & ~(1ULL << i));
                        new_board->white_pawn = new_board->white_pawn & ~(1ULL << (i - 1));
                        LS_STATE_MOVES_GENERATE_INSERT_MOVE_CHECK
                    }
                }
            }
        }
    }

    // Castling
    if (state->turn == LS_PLAYER_WHITE) {
        bool king_stop = true;
        bool left_rock_stop = true;
        bool right_rock_stop = true;
        ls_state_t current_state = state;
        while (king_stop && (left_rock_stop || right_rock_stop) && current_state != nullptr) {
            if (!(current_state->board->white_king & LS_START_POSITION_WHITE_KING)) king_stop = false;
            if (!(current_state->board->white_rook & 0x80ULL)) left_rock_stop = false;
            if (!(current_state->board->white_rook & 0x1ULL)) right_rock_stop = false;
            current_state = current_state->parent;
        }

        if (king_stop) {
            ls_board_state_t const no_white_king = state->board->white_king & ~0x8ULL;
            if (left_rock_stop && ((0x70ULL & empty_squares) == 0x70ULL)) {
                ls_board_t const new_board = ls_board_copy(state->board);

                new_board->white_king = no_white_king | 0x10ULL;
                if (ls_state_is_board_check(new_board, LS_PLAYER_BLACK)) free(new_board);
                else {
                    new_board->white_king = no_white_king | 0x20ULL;
                    if (ls_state_is_board_check(new_board, LS_PLAYER_BLACK)) free(new_board);
                    else {
                        new_board->white_rook = (new_board->white_rook & ~0x80ULL) | 0x10ULL;
                        LS_STATE_MOVES_GENERATE_INSERT_MOVE_CHECK
                    }
                }
            }
            if (left_rock_stop && ((0x6ULL & empty_squares) == 0x6ULL)) {
                ls_board_t const new_board = ls_board_copy(state->board);

                new_board->white_king = no_white_king | 0x4ULL;
                if (ls_state_is_board_check(new_board, LS_PLAYER_BLACK)) free(new_board);
                else {
                    new_board->white_king = no_white_king | 0x2ULL;
                    if (ls_state_is_board_check(new_board, LS_PLAYER_BLACK)) free(new_board);
                    else {
                        new_board->white_rook = (new_board->white_rook & ~0x1ULL) | 0x4ULL;
                        LS_STATE_MOVES_GENERATE_INSERT_MOVE_CHECK
                    }
                }
            }
        }
    } else {
        bool king_stop = true;
        bool left_rock_stop = true;
        bool right_rock_stop = true;
        ls_state_t current_state = state;
        while (king_stop && (left_rock_stop || right_rock_stop) && current_state != nullptr) {
            if (!(current_state->board->white_king & LS_START_POSITION_BLACK_KING)) king_stop = false;
            if (!(current_state->board->white_rook & 0x8000000000000000)) left_rock_stop = false;
            if (!(current_state->board->white_rook & 0x0100000000000000)) right_rock_stop = false;
            current_state = current_state->parent;
        }

        if (king_stop) {
            ls_board_state_t const no_black_king = state->board->black_king & ~0x0800000000000000;
            if (left_rock_stop && ((0x7000000000000000 & empty_squares) == 0x7000000000000000)) {
                ls_board_t const new_board = ls_board_copy(state->board);

                new_board->black_king = no_black_king | 0x1000000000000000;
                if (ls_state_is_board_check(new_board, LS_PLAYER_WHITE)) free(new_board);
                else {
                    new_board->black_king = no_black_king | 0x2000000000000000;
                    if (ls_state_is_board_check(new_board, LS_PLAYER_WHITE)) free(new_board);
                    else {
                        new_board->black_rook = (new_board->black_rook & ~0x8000000000000000) | 0x1000000000000000;
                        LS_STATE_MOVES_GENERATE_INSERT_MOVE_CHECK
                    }
                }
            }
            if (left_rock_stop && ((0x0600000000000000 & empty_squares) == 0x0600000000000000)) {
                ls_board_t const new_board = ls_board_copy(state->board);

                new_board->black_king = no_black_king | 0x0400000000000000;
                if (ls_state_is_board_check(new_board, LS_PLAYER_WHITE)) free(new_board);
                else {
                    new_board->black_king = no_black_king | 0x0200000000000000;
                    if (ls_state_is_board_check(new_board, LS_PLAYER_WHITE)) free(new_board);
                    else {
                        new_board->black_rook = (new_board->black_rook & ~0x0100000000000000) | 0x0400000000000000;
                        LS_STATE_MOVES_GENERATE_INSERT_MOVE_CHECK
                    }
                }
            }
        }
    }

    return state->moves_length > 0 ? LS_STATE_GENERATION_MOVES_DONE : LS_STATE_GENERATION_MOVES_EMPTY;
}
