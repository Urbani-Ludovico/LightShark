
#include "LSState.h"

#include "LSMoves.h"

#define LS_STATE_IS_BOARD_CHECK_ATTACK(piece, masks, directions, directions_count) \
{ \
    for (int d = 0; d < directions_count; d++) { \
        ls_board_state_t current_state = piece; \
        for (uint8_t i = 0; i < 7 && current_state; i++) { \
            current_state &= masks[d]; \
            current_state = directions[d] > 0 ? current_state << directions[d] : current_state >> -directions[d]; \
            if (current_state & king) return true; \
            current_state &= occupied_mask; \
        } \
    } \
}

ls_check_t ls_state_is_check(ls_state_t const state) {
    if (state->is_check == LS_UNDEFINED_CHECK) {
        if (ls_state_is_board_check(state->board, LS_PLAYER_WHITE) == true) {
            state->is_check = LS_CHECK_WHITE;
        } else if (ls_state_is_board_check(state->board, LS_PLAYER_BLACK) == true) {
            state->is_check = LS_CHECK_BLACK;
        } else {
            state->is_check = LS_NO_CHECK;
        }
    }

    return state->is_check;
}

bool ls_state_is_board_check(ls_board_t const board, ls_player_t const player) {
    ls_board_state_t const king = player == LS_PLAYER_WHITE ? board->black_king : board->white_king;
    ls_board_state_t const queen = player == LS_PLAYER_WHITE ? board->white_queen : board->black_queen;
    ls_board_state_t const bishop = player == LS_PLAYER_WHITE ? board->white_bishop : board->black_bishop;
    ls_board_state_t const knight = player == LS_PLAYER_WHITE ? board->white_knight : board->black_knight;
    ls_board_state_t const rook = player == LS_PLAYER_WHITE ? board->white_rock : board->black_rock;
    ls_board_state_t const pawn = player == LS_PLAYER_WHITE ? board->white_pawn : board->black_pawn;

    ls_board_state_t const occupied_mask = ~ls_board_occupied_mask(board);

    // Queen
    LS_STATE_IS_BOARD_CHECK_ATTACK(queen, _ls_queen_moves_from_masks, _ls_queen_moves_directions, _ls_queen_moves)

    // Bishop
    LS_STATE_IS_BOARD_CHECK_ATTACK(bishop, _ls_bishop_moves_from_masks, _ls_bishop_moves_directions, _ls_bishop_moves)

    // Knight
    for (uint8_t i = 0; i < _ls_knight_moves; i++) {
        ls_board_state_t current_state = knight & _ls_knight_moves_from_masks[i];
        current_state = _ls_knight_moves_directions[i] > 0 ? current_state << _ls_knight_moves_directions[i] : current_state >> -_ls_knight_moves_directions[i];
        if (current_state & king) return true;
    }

    // Rook
    LS_STATE_IS_BOARD_CHECK_ATTACK(rook, _ls_rock_moves_from_masks, _ls_rock_moves_directions, _ls_rock_moves)

    // Pawn
    if ((player == LS_PLAYER_WHITE && ((((pawn & 0x007F7F7F7F7F7F7F) << 9) | ((pawn & 0x00FEFEFEFEFEFEFE) << 7)) & king)) || (player == LS_PLAYER_BLACK && ((((pawn & 0xFEFEFEFEFEFEFE00) >> 9) | ((pawn & 0x7F7F7F7F7F7F7F00) >> 7)) & king))) {
        return true;
    }

    return false;
}

ls_board_state_t ls_board_occupied_mask(ls_board_t const board) {
    return ls_board_occupied_mask_white(board) & ls_board_occupied_mask_black(board);
}

ls_board_state_t ls_board_occupied_mask_white(ls_board_t const board) {
    return board->white_king | board->white_queen | board->white_bishop | board->white_knight | board->white_rock | board->white_pawn;
}

ls_board_state_t ls_board_occupied_mask_black(ls_board_t const board) {
    return board->black_king | board->black_queen | board->black_bishop | board->black_knight | board->black_rock | board->black_pawn;
}
