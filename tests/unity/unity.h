
#ifndef UNITY_H
#define UNITY_H

#include <stdio.h>

#define UNITY_TEST_PARAMETERS unsigned int* _unity_assert_count, unsigned int* _unity_assert_passed_count, unsigned int* _unity_assert_failed_count
#define UNITY_TEST_RETURN int

#define UNITY_BEGIN \
    unsigned int _unity_header_count = 0; \
    unsigned int _unity_test_count = 0; \
    unsigned int _unity_test_passed_count = 0; \
    unsigned int _unity_test_failed_count = 0; \
    unsigned int _unity_assert_count = 0; \
    unsigned int _unity_assert_passed_count = 0; \
    unsigned int _unity_assert_failed_count = 0; \
    int result; \
    printf("Begin Unit Testing\n\n----------------------------------------\n\n");

#define UNITY_END \
    printf("\n----------------------------------------\n\nEnd Unit Testing\n\n"); \
    if (_unity_test_failed_count > 0) { \
        printf("\t\033[0;31mPassed %u/%u tests. %u tests failed!\033[0m\n", _unity_test_passed_count, _unity_test_count, _unity_test_failed_count); \
        printf("\t\033[0;31mPassed %u/%u asserts. %u asserts failed!\033[0m\n", _unity_assert_passed_count, _unity_assert_count, _unity_assert_failed_count); \
    } else { \
        printf("\033[0;32m%u asserts passed in %u tests. Good job!\033[0m\n", _unity_assert_count, _unity_test_count); \
    }

#define UNITY_HEADER(header) \
    _unity_header_count++; \
    if (_unity_header_count != 0 || _unity_test_count != 0) { \
        printf("\n"); \
    } \
    printf("\033[0;36m----------  "); \
    printf(header); \
    printf("  ----------\033[0m\n");

#define UNITY_TEST(func, name) \
    _unity_test_count++; \
    printf("\t\033[0;35mTEST %u\033[0m: ", _unity_test_count); \
    printf(name); \
    printf("\n"); \
    result = func(&_unity_assert_count, &_unity_assert_passed_count, &_unity_assert_failed_count); \
    if (result == 0) { \
        _unity_test_passed_count++; \
    } else { \
        _unity_test_failed_count++; \
    }

#define UNITY_TEST_BEGIN \
    unsigned int _unity_test_assert_count = 0; \
    unsigned int _unity_test_assert_passed_count = 0; \
    unsigned int _unity_test_assert_failed_count = 0;

#define UNITY_TEST_END \
    if (_unity_test_assert_failed_count > 0) { \
        printf("\t\033[0;31mPassed %u/%u asserts. %u assert failed!\033[0m\n", _unity_test_assert_passed_count, _unity_test_assert_count, _unity_test_assert_failed_count); \
    } \
    return _unity_test_assert_failed_count;

#define UNITY_ASSERT(func, message) \
    _unity_test_assert_count++; \
    (*_unity_assert_count)++; \
    printf("\t\t\033[0;33mASSERT %u\033[0m", _unity_test_assert_count); \
    if (func) {\
        printf(": \033[0;32mPASSED\033[0m\n"); \
        _unity_test_assert_passed_count++; \
        (*_unity_assert_passed_count)++; \
    } else { \
        printf(": \033[0;31mFAILED\033[0m\n\t"); \
        printf(message); \
        printf("\n"); \
        _unity_test_assert_failed_count++; \
        (*_unity_assert_failed_count)++; \
    }

#define UNITY_ASSERT_EQUAL(func, target) \
    UNITY_ASSERT(func == target, "\"" #func "\" == \"" #target "\"")

#define UNITY_ASSERT_NULLPTR(func) \
    UNITY_ASSERT(func == nullptr, "\"" #func "\" == nullptr")

#define UNITY_ASSERT_NOT_NULLPTR(func) \
    UNITY_ASSERT(func != nullptr, "\"" #func "\" != nullptr")

#endif
