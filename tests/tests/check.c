
#include "check.h"

UNITY_TEST_RETURN test_check_single_white(UNITY_TEST_PARAMETERS) {
    UNITY_TEST_BEGIN

    auto const board = ls_board_init();
    board->black_king = 0x0000001000000000;

    ls_board_state_t* const piece[] = {
        &board->white_queen, &board->white_queen, &board->white_queen, &board->white_queen, &board->white_queen, &board->white_queen, &board->white_queen, &board->white_queen, &board->white_queen, &board->white_queen, &board->white_queen, &board->white_queen, &board->white_queen, &board->white_queen, &board->white_queen, &board->white_queen,
        &board->white_bishop, &board->white_bishop, &board->white_bishop, &board->white_bishop, &board->white_bishop, &board->white_bishop, &board->white_bishop, &board->white_bishop,
        &board->white_knight, &board->white_knight, &board->white_knight, &board->white_knight, &board->white_knight, &board->white_knight, &board->white_knight, &board->white_knight,
        &board->white_rock, &board->white_rock, &board->white_rock, &board->white_rock, &board->white_rock, &board->white_rock, &board->white_rock, &board->white_rock,
        &board->white_pawn, &board->white_pawn
    };
    constexpr int8_t state[] = {
        8, 7, -1, -9, -8, -7, 1, 9, 16, 14, -2, -18, -16, -14, 2, 18,
        7, -9, -7, 9, 14, -18, -14, 18,
        15, 6, -10, -17, -15, -6, 10, 17,
        8, -1, -8, 1, 16, -2, -16, 2,
        -7, -9
    };

    for (int i = 0; i < 42; i++) {
        *piece[i] = state[i] > 0 ? 0x0000001000000000 << state[i] : 0x0000001000000000 >> -state[i];
        UNITY_ASSERT_TRUE(ls_state_is_board_check(board, WHITE));
        *piece[i] = 0x0;
    }

    UNITY_TEST_END
}