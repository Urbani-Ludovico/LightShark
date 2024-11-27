
#include "tree.h"

#include <LightShark.h>

UNITY_TEST_RETURN test_tree_insert(UNITY_TEST_PARAMETERS) {
    UNITY_TEST_BEGIN

    auto const engine = ls_init();

    const ls_board_t new_board = ls_board_init();
    const ls_state_t new_child = ls_tree_init();
    new_child->board = new_board;
    ls_tree_insert_move(engine->tree, new_child);

    UNITY_ASSERT_NOT_NULLPTR(engine->tree->moves)
    UNITY_ASSERT_EQUAL(engine->tree->moves_length, 1)
    UNITY_ASSERT_NOT_EQUAL(engine->tree->_moves_array_length, 0)
    UNITY_ASSERT_POINTER_EQUAL(engine->tree->moves[0]->parent, engine->tree)

    ls_destroy(engine);

    UNITY_TEST_END
}


UNITY_TEST_RETURN test_tree_insert_board(UNITY_TEST_PARAMETERS) {
    UNITY_TEST_BEGIN

    auto const engine = ls_init();

    const ls_board_t new_board = ls_board_init();
    ls_tree_insert_board_move(engine->tree, new_board);

    UNITY_ASSERT_NOT_NULLPTR(engine->tree->moves)
    UNITY_ASSERT_EQUAL(engine->tree->moves_length, 1)
    UNITY_ASSERT_NOT_EQUAL(engine->tree->_moves_array_length, 0)
    UNITY_ASSERT_POINTER_EQUAL(engine->tree->moves[0]->parent, engine->tree)

    UNITY_ASSERT_POINTER_EQUAL(engine->tree->moves[0]->board, new_board)

    ls_destroy(engine);

    UNITY_TEST_END
}
