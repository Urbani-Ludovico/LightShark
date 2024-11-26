
#include "start.h"

UNITY_TEST_RETURN test_init(UNITY_TEST_PARAMETERS) {
    UNITY_TEST_BEGIN

    auto const engine = ls_init();

    UNITY_ASSERT_NOT_NULLPTR(engine->tree)
    UNITY_ASSERT_NOT_NULLPTR(engine->tree->board)
    UNITY_ASSERT_POINTER_EQUAL(engine->state, engine->tree)
    UNITY_ASSERT_POINTER_EQUAL(engine->board, engine->tree->board)

    UNITY_ASSERT_EQUAL(engine->tree->capture, 0x0)
    UNITY_ASSERT_NULLPTR(engine->tree->moves)
    UNITY_ASSERT_EQUAL(engine->tree->moves_length, 0)
    UNITY_ASSERT_EQUAL(engine->tree->_moves_array_length, 0)

    ls_destroy(engine);

    UNITY_TEST_END
}

UNITY_TEST_RETURN test_init_game_information(UNITY_TEST_PARAMETERS) {
    UNITY_TEST_BEGIN

    auto const engine = ls_init();

    UNITY_ASSERT_EQUAL(engine->turn, WHITE)
    UNITY_ASSERT_EQUAL(engine->moves_count, 0)
    UNITY_ASSERT_EQUAL(engine->captured_white_queen, 0)
    UNITY_ASSERT_EQUAL(engine->captured_white_rock, 0)
    UNITY_ASSERT_EQUAL(engine->captured_white_knight, 0)
    UNITY_ASSERT_EQUAL(engine->captured_white_bishop, 0)
    UNITY_ASSERT_EQUAL(engine->captured_white_pawn, 0)
    UNITY_ASSERT_EQUAL(engine->captured_black_queen, 0)
    UNITY_ASSERT_EQUAL(engine->captured_black_rock, 0)
    UNITY_ASSERT_EQUAL(engine->captured_black_knight, 0)
    UNITY_ASSERT_EQUAL(engine->captured_black_bishop, 0)
    UNITY_ASSERT_EQUAL(engine->captured_black_pawn, 0)

    ls_destroy(engine);

    UNITY_TEST_END
}

UNITY_TEST_RETURN test_board_start(UNITY_TEST_PARAMETERS) {
    UNITY_TEST_BEGIN

    auto const engine = ls_init();

    constexpr char default_board[64] = {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'};
    char* board_string = ls_board_to_string(engine->board);
    UNITY_ASSERT_STRING_ARRAY_EQUAL(board_string, default_board, 64);
    free(board_string);

    ls_destroy(engine);

    UNITY_TEST_END
}
