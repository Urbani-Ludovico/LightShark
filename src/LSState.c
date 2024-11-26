
#include "LSState.h"

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

constexpr int8_t ls_rook_directions[] = {8, -1, -8, 1};
constexpr ls_board_state_t ls_rook_masks[] = {
    0x00FFFFFFFFFFFFFF, // Up
    0xFEFEFEFEFEFEFEFE, // Left
    0xFFFFFFFFFFFFFF00, // Down
    0x7F7F7F7F7F7F7F7F, // Right
};
constexpr int8_t ls_bishop_directions[] = {7, -9, -7, 9};
constexpr ls_board_state_t ls_bishop_masks[] = {
    0x00FEFEFEFEFEFEFE, // Up-Right
    0xFEFEFEFEFEFEFE00, // Down-Left
    0x7F7F7F7F7F7F7F00, // Down-Right
    0x007F7F7F7F7F7F7F // Up-Left
};

bool ls_state_is_board_check(ls_board_t const board, ls_player_t const player) {
    ls_board_state_t const king = player == WHITE ? board->black_king : board->white_king;
    ls_board_state_t const queen = player == WHITE ? board->white_queen : board->black_queen;
    ls_board_state_t const bishop = player == WHITE ? board->white_bishop : board->black_bishop;
    ls_board_state_t const knight = player == WHITE ? board->white_knight : board->black_knight;
    ls_board_state_t const rook = player == WHITE ? board->white_rock : board->black_rock;
    ls_board_state_t const pawn = player == WHITE ? board->white_pawn : board->black_pawn;

    ls_board_state_t const occupied_mask = ~ls_board_occupied_mask(board);

    // Queen
    LS_STATE_IS_BOARD_CHECK_ATTACK(queen, ls_rook_masks, ls_rook_directions, 4)
    LS_STATE_IS_BOARD_CHECK_ATTACK(queen, ls_bishop_masks, ls_bishop_directions, 4)

    // Bishop
    LS_STATE_IS_BOARD_CHECK_ATTACK(bishop, ls_bishop_masks, ls_bishop_directions, 4)

    // Knight
    if ((((knight & 0x0000FEFEFEFEFEFE) << 15) | ((knight & 0x00FCFCFCFCFCFCFC) << 6) | ((knight & 0xFCFCFCFCFCFCFC00) >> 10) | ((knight & 0xFEFEFEFEFEFE0000) >> 17) | ((knight & 0x7F7F7F7F7F7F0000) >> 15) | ((knight & 0x3F3F3F3F3F3F3F00) >> 6) | ((knight & 0x003F3F3F3F3F3F3F) << 10) | ((knight & 0x00007F7F7F7F7F7F) << 17)) & king) {
        return true;
    }

    // Rook
    LS_STATE_IS_BOARD_CHECK_ATTACK(rook, ls_rook_masks, ls_rook_directions, 4)

    // Pawn
    if ((player == WHITE && ((((pawn & 0x007F7F7F7F7F7F7F) << 9) | ((pawn & 0x00FEFEFEFEFEFEFE) << 7)) & king)) || (player == BLACK && ((((pawn & 0xFEFEFEFEFEFEFE00) >> 9) | ((pawn & 0x7F7F7F7F7F7F7F00) >> 7)) & king))) {
        return true;
    }

    return false;
}

ls_board_state_t ls_board_occupied_mask(ls_board_t const board) {
    return board->white_king | board->black_king | board->white_queen | board->black_queen | board->white_bishop | board->black_bishop | board->white_knight | board->black_knight | board->white_rock | board->black_rock | board->white_pawn | board->black_pawn;
}
