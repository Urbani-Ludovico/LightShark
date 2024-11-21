
#include "start.h"

UNITY_TEST_RETURN test_init(UNITY_TEST_PARAMETERS) {
    UNITY_TEST_BEGIN

    const auto engine = ls_init();

    UNITY_ASSERT_NOT_NULLPTR(engine->board)
    UNITY_ASSERT_NOT_NULLPTR(engine->tree)

    UNITY_ASSERT_NULLPTR(engine->tree->children)
    UNITY_ASSERT_EQUAL(engine->tree->children_length, 0)
    UNITY_ASSERT_EQUAL(engine->tree->_children_array_length, 0)

    ls_destroy(engine);

    UNITY_TEST_END
}

UNITY_TEST_RETURN test_board_start(UNITY_TEST_PARAMETERS) {
    UNITY_TEST_BEGIN

    const auto engine = ls_init();

    constexpr char default_board[64] = {
        'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r',
        'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p',
        ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
        ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
        ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
        ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
        'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P',
        'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'
    };
    char* board_string = ls_board_to_string(engine->board);
    UNITY_ASSERT_STRING_ARRAY_EQUAL(board_string, default_board, 64);
    free(board_string);

    // ls_board_print(engine->board);

    ls_destroy(engine);

    UNITY_TEST_END
}