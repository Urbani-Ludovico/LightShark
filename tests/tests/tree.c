
#include "tree.h"

UNITY_TEST_RETURN test_tree_insert(UNITY_TEST_PARAMETERS) {
    UNITY_TEST_BEGIN

    const auto engine = ls_init();

    const ls_board_t new_board = ls_board_init();
    ls_tree_insert_child(engine->tree, new_board);

    UNITY_ASSERT_NOT_NULLPTR(engine->tree->children)
    UNITY_ASSERT_EQUAL(engine->tree->children_length, 1)
    UNITY_ASSERT_NOT_EQUAL(engine->tree->_children_array_length, 0)
    UNITY_ASSERT_POINTER_EQUAL(engine->tree->children[0]->board, new_board)

    ls_destroy(engine);

    UNITY_TEST_END
}