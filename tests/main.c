
#include "unity/unity.h"
#include "unity/example_tests.h"

#include "tests/start.h"

int main(void) {
    UNITY_BEGIN

    UNITY_TEST(unity_example_test, "Tests for unity")

    UNITY_HEADER("Engine structure")
    UNITY_TEST(test_init, "Test init")

    UNITY_END
    return 0;
}
