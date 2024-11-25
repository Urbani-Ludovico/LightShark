
#include "LSState.h"

ls_check_t ls_state_is_check(ls_state_t const state) {
    if (state->is_check == UNDEFINED_CHECK) {
        if (ls_state_is_board_check(state->board, WHITE) == true) {
            state->is_check = CHECK_WHITE;
        } else if (ls_state_is_board_check(state->board, BLACK) == true) {
            state->is_check = CHECK_BLACK;
        } else {
            state->is_check = NO_CHECK;
        }
    }

    return state->is_check;
}

bool ls_state_is_board_check(ls_board_t const board, ls_player_t const player) {
    ls_board_state_t const king = player == WHITE ? board->black_king : board->white_king;
    ls_board_state_t const queen = player == WHITE ? board->white_queen : board->black_queen;
    // ls_board_state_t const bishop = player == WHITE ? board->white_bishop : board->black_bishop;
    // ls_board_state_t const knight = player == WHITE ? board->white_knight : board->black_knight;
    // ls_board_state_t const rook = player == WHITE ? board->white_rock : board->black_rock;
    // ls_board_state_t const pawn = player == WHITE ? board->white_pawn: board->black_pawn;

    ls_board_state_t const occupied_mask = ~ls_board_occupied_mask(board);

    // Queen
    ls_board_state_t current_state = queen;
    for (uint8_t i = 0; i < 7 && current_state; i++) {
        current_state &= 0x00FFFFFFFFFFFFFF;
        current_state <<= 8;
        if (current_state & king) return true;
        current_state &= occupied_mask;
    }
    current_state = queen;
    for (uint8_t i = 0; i < 7 && current_state; i++) {
        current_state &= 0x00FEFEFEFEFEFEFE;
        current_state <<= 7;
        if (current_state & king) return true;
        current_state &= occupied_mask;
    }
    current_state = queen;
    for (uint8_t i = 0; i < 7 && current_state; i++) {
        current_state &= 0xFEFEFEFEFEFEFEFE;
        current_state >>= 1;
        if (current_state & king) return true;
        current_state &= occupied_mask;
    }
    current_state = queen;
    for (uint8_t i = 0; i < 7 && current_state; i++) {
        current_state &= 0xFEFEFEFEFEFEFE00;
        current_state >>= 9;
        if (current_state & king) return true;
        current_state &= occupied_mask;
    }
    current_state = queen;
    for (uint8_t i = 0; i < 7 && current_state; i++) {
        current_state &= 0xFFFFFFFFFFFFFF00;
        current_state >>= 8;
        if (current_state & king) return true;
        current_state &= occupied_mask;
    }
    current_state = queen;
    for (uint8_t i = 0; i < 7 && current_state; i++) {
        current_state &= 0x7F7F7F7F7F7F7F00;
        current_state >>= 7;
        if (current_state & king) return true;
        current_state &= occupied_mask;
    }
    current_state = queen;
    for (uint8_t i = 0; i < 7 && current_state; i++) {
        current_state &= 0x7F7F7F7F7F7F7F7F;
        current_state <<= 1;
        if (current_state & king) return true;
        current_state &= occupied_mask;
    }
    current_state = queen;
    for (uint8_t i = 0; i < 7 && current_state; i++) {
        current_state &= 0x007F7F7F7F7F7F7F;
        current_state <<= 9;
        if (current_state & king) return true;
        current_state &= occupied_mask;
    }

    return false;
}

ls_board_state_t ls_board_occupied_mask(ls_board_t const board) {
    return board->white_king | board->black_king | board->white_queen | board->black_queen | board->white_bishop | board->black_bishop | board->white_knight | board->black_knight | board->white_rock | board->black_rock | board->white_pawn | board->black_pawn;
}
