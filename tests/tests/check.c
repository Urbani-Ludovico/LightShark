
#include "check.h"

#include <stdint.h>
#include <LightShark.h>

#define TEST_CHECK_KING_POSITION 0x0000001000000000

#define TEST_CHECK_FOR_TRUE(piece, state, length, player) \
    for (int i = 0; i < length; i++) { \
        *piece[i] = state[i] > 0 ? TEST_CHECK_KING_POSITION << state[i] : TEST_CHECK_KING_POSITION >> -state[i];\
        UNITY_ASSERT_TRUE(ls_state_is_board_check(board, player)); \
        *piece[i] = 0x0; \
    }

#define TEST_CHECK_FOR_FALSE(piece, state, length, player) \
    for (int i = 0; i < length; i++) { \
        *piece[i] = state[i] > 0 ? TEST_CHECK_KING_POSITION << state[i] : TEST_CHECK_KING_POSITION >> -state[i];\
        UNITY_ASSERT_FALSE(ls_state_is_board_check(board, player)); \
        *piece[i] = 0x0; \
    }

UNITY_TEST_RETURN test_check_single_white(UNITY_TEST_PARAMETERS) {
    UNITY_TEST_BEGIN

    auto const board = ls_board_init();
    board->black_king = TEST_CHECK_KING_POSITION;

    ls_board_state_t* const piece[] = {&board->white_queen, &board->white_queen, &board->white_queen, &board->white_queen, &board->white_queen, &board->white_queen, &board->white_queen, &board->white_queen, &board->white_queen, &board->white_queen, &board->white_queen, &board->white_queen, &board->white_queen, &board->white_queen, &board->white_queen, &board->white_queen, &board->white_bishop, &board->white_bishop, &board->white_bishop, &board->white_bishop, &board->white_bishop, &board->white_bishop, &board->white_bishop, &board->white_bishop, &board->white_knight, &board->white_knight, &board->white_knight, &board->white_knight, &board->white_knight, &board->white_knight, &board->white_knight, &board->white_knight, &board->white_rook, &board->white_rook, &board->white_rook, &board->white_rook, &board->white_rook, &board->white_rook, &board->white_rook, &board->white_rook, &board->white_pawn, &board->white_pawn};
    constexpr int8_t state[] = {8, 7, -1, -9, -8, -7, 1, 9, 16, 14, -2, -18, -16, -14, 2, 18, 7, -9, -7, 9, 14, -18, -14, 18, 15, 6, -10, -17, -15, -6, 10, 17, 8, -1, -8, 1, 16, -2, -16, 2, -7, -9};
    TEST_CHECK_FOR_TRUE(piece, state, 42, LS_PLAYER_BLACK)

    ls_board_destroy(board);

    UNITY_TEST_END
}


UNITY_TEST_RETURN test_check_single_black(UNITY_TEST_PARAMETERS) {
    UNITY_TEST_BEGIN

    auto const board = ls_board_init();
    board->white_king = TEST_CHECK_KING_POSITION;

    ls_board_state_t* const piece[] = {&board->black_queen, &board->black_queen, &board->black_queen, &board->black_queen, &board->black_queen, &board->black_queen, &board->black_queen, &board->black_queen, &board->black_queen, &board->black_queen, &board->black_queen, &board->black_queen, &board->black_queen, &board->black_queen, &board->black_queen, &board->black_queen, &board->black_bishop, &board->black_bishop, &board->black_bishop, &board->black_bishop, &board->black_bishop, &board->black_bishop, &board->black_bishop, &board->black_bishop, &board->black_knight, &board->black_knight, &board->black_knight, &board->black_knight, &board->black_knight, &board->black_knight, &board->black_knight, &board->black_knight, &board->black_rook, &board->black_rook, &board->black_rook, &board->black_rook, &board->black_rook, &board->black_rook, &board->black_rook, &board->black_rook, &board->black_pawn, &board->black_pawn};
    constexpr int8_t state[] = {8, 7, -1, -9, -8, -7, 1, 9, 16, 14, -2, -18, -16, -14, 2, 18, 7, -9, -7, 9, 14, -18, -14, 18, 15, 6, -10, -17, -15, -6, 10, 17, 8, -1, -8, 1, 16, -2, -16, 2, 7, 9};
    TEST_CHECK_FOR_TRUE(piece, state, 42, LS_PLAYER_WHITE)

    ls_board_destroy(board);

    UNITY_TEST_END
}


UNITY_TEST_RETURN test_not_check_single_white(UNITY_TEST_PARAMETERS) {
    UNITY_TEST_BEGIN

    auto const board = ls_board_init();
    board->black_king = TEST_CHECK_KING_POSITION;

    ls_board_state_t* const piece[] = {&board->white_queen, &board->white_queen, &board->white_queen, &board->white_queen, &board->white_bishop, &board->white_bishop, &board->white_bishop, &board->white_bishop, &board->white_knight, &board->white_knight, &board->white_knight, &board->white_knight, &board->white_rook, &board->white_rook, &board->white_rook, &board->white_rook, &board->white_pawn, &board->white_pawn, &board->white_pawn, &board->white_pawn};
    constexpr int8_t state[] = {13, 25, -11, 35, 8, 15, -4, -26, 9, 18, -2, -16, 9, 23, -7, -18, 7, 9, -8, -18};
    TEST_CHECK_FOR_FALSE(piece, state, 20, LS_PLAYER_BLACK)

    ls_board_destroy(board);

    UNITY_TEST_END
}


UNITY_TEST_RETURN test_not_check_single_black(UNITY_TEST_PARAMETERS) {
    UNITY_TEST_BEGIN

    auto const board = ls_board_init();
    board->white_king = TEST_CHECK_KING_POSITION;

    ls_board_state_t* const piece[] = {&board->black_queen, &board->black_queen, &board->black_queen, &board->black_queen, &board->black_bishop, &board->black_bishop, &board->black_bishop, &board->black_bishop, &board->black_knight, &board->black_knight, &board->black_knight, &board->black_knight, &board->black_rook, &board->black_rook, &board->black_rook, &board->black_rook, &board->black_pawn, &board->black_pawn, &board->black_pawn, &board->black_pawn};
    constexpr int8_t state[] = {13, 25, -11, 35, 8, 15, -4, -26, 9, 18, -2, -16, 9, 23, -7, -18, -7, -9, 8, 18};
    TEST_CHECK_FOR_FALSE(piece, state, 20, LS_PLAYER_WHITE)

    ls_board_destroy(board);

    UNITY_TEST_END
}


UNITY_TEST_RETURN test_not_check_obstacle(UNITY_TEST_PARAMETERS) {
    UNITY_TEST_BEGIN

    auto const board = ls_board_init();
    board->black_king = TEST_CHECK_KING_POSITION;

    ls_board_state_t* const piece[] = {&board->white_queen, &board->white_queen, &board->white_bishop, &board->white_bishop, &board->white_rook, &board->white_rook};
    constexpr int8_t state[] = {2, -27, 18, 27, 2, -24};
    constexpr int8_t obstacles[] = {1, -18, 9, 9, 1, -8};
    for (int i = 0; i < 6; i++) {
        *piece[i] = state[i] > 0 ? TEST_CHECK_KING_POSITION << state[i] : TEST_CHECK_KING_POSITION >> -state[i];
        board->white_pawn = obstacles[i] > 0 ? TEST_CHECK_KING_POSITION << obstacles[i] : TEST_CHECK_KING_POSITION >> -obstacles[i];
        UNITY_ASSERT_FALSE(ls_state_is_board_check(board, LS_PLAYER_BLACK));
        *piece[i] = 0x0;
        board->white_pawn = 0x0;
    }

    ls_board_destroy(board);

    UNITY_TEST_END
}
