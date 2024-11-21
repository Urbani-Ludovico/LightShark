
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