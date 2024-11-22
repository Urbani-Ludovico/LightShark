
#include "unity/unity.h"
#include "unity/example_tests.h"

#include "tests/start.h"
#include "tests/tree.h"

int main(void) {
    UNITY_BEGIN

    UNITY_TEST(unity_example_test, "Tests for unity")

    UNITY_HEADER("Engine structure")
    UNITY_TEST(test_init, "Engine init")
    UNITY_TEST(test_init_game_information, "Game information init")
    UNITY_TEST(test_board_start, "Board start")

    UNITY_HEADER("Tree structure")
    UNITY_TEST(test_tree_insert, "Tree insert")

    UNITY_END
    return 0;
}
