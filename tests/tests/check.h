
#ifndef CHECK_H
#define CHECK_H

#include "../unity/unity.h"

UNITY_TEST_RETURN test_check_single_white(UNITY_TEST_PARAMETERS);
UNITY_TEST_RETURN test_check_single_black(UNITY_TEST_PARAMETERS);
UNITY_TEST_RETURN test_not_check_single_white(UNITY_TEST_PARAMETERS);
UNITY_TEST_RETURN test_not_check_single_black(UNITY_TEST_PARAMETERS);
UNITY_TEST_RETURN test_not_check_obstacle(UNITY_TEST_PARAMETERS);

#endif
