
#ifndef LIGHTSHARK_TESTS_UNITY_H
#define LIGHTSHARK_TESTS_UNITY_H

#include <stdio.h>
#include <stdint.h>

#define UNITY_TEST_PARAMETERS unsigned int* _unity_assert_count, unsigned int* _unity_assert_passed_count, unsigned int* _unity_assert_failed_count
#define UNITY_TEST_RETURN bool

#define UNITY_BEGIN \
    unsigned int _unity_header_count = 0; \
    unsigned int _unity_test_count = 0; \
    unsigned int _unity_test_passed_count = 0; \
    unsigned int _unity_test_failed_count = 0; \
    unsigned int _unity_assert_count = 0; \
    unsigned int _unity_assert_passed_count = 0; \
    unsigned int _unity_assert_failed_count = 0; \
    bool result; \
    printf("Begin Unit Testing\n\n----------------------------------------\n\n");

#define UNITY_END \
    printf("\n----------------------------------------\n\nEnd Unit Testing\n\n"); \
    if (_unity_test_failed_count > 0) { \
        printf("\033[0;31mPassed %u/%u tests. %u tests failed!\033[0m\n", _unity_test_passed_count, _unity_test_count, _unity_test_failed_count); \
        printf("\033[0;31mPassed %u/%u asserts. %u asserts failed!\033[0m\n", _unity_assert_passed_count, _unity_assert_count, _unity_assert_failed_count); \
    } else { \
        printf("\33[0;32m%u asserts passed in %u tests. Good job!\033[0m\n", _unity_assert_count, _unity_test_count); \
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
    if (result) { \
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
    return _unity_test_assert_failed_count == 0;

#define UNITY_ASSERT_BEGIN \
    _unity_test_assert_count++; \
    (*_unity_assert_count)++; \
    printf("\t\t\033[0;33mASSERT %u\033[0m", _unity_test_assert_count);

#define UNITY_ASSERT_PASSED \
    printf(": \033[0;32mPASSED\033[0m\n"); \
    _unity_test_assert_passed_count++; \
    (*_unity_assert_passed_count)++;

#define UNITY_ASSERT_FAILED(message) \
    printf(": \033[0;31mFAILED\033[0m\n"); \
    printf("\t\t\t%s\n", message); \
    _unity_test_assert_failed_count++; \
    (*_unity_assert_failed_count)++;

#define UNITY_ASSERT(func, message) \
    UNITY_ASSERT_BEGIN \
    if (func) {\
        UNITY_ASSERT_PASSED \
    } else { \
        UNITY_ASSERT_FAILED(message) \
    }

#define UNITY_ASSERT_EQUAL(func, target) \
    { \
        char* _unity_string; \
        asprintf(&_unity_string, "%d == %d", func, target); \
        UNITY_ASSERT(func == target, _unity_string) \
        free(_unity_string); \
    }

#define UNITY_ASSERT_NOT_EQUAL(func, target) \
    { \
        char* _unity_string; \
        asprintf(&_unity_string, "%d != %d", func, target); \
        UNITY_ASSERT(func != target, _unity_string) \
        free(_unity_string); \
    }

#define UNITY_ASSERT_POINTER_EQUAL(func, target) \
    { \
        char* _unity_string; \
        asprintf(&_unity_string, "%p == %p", func, target); \
        UNITY_ASSERT(func == target, _unity_string) \
        free(_unity_string); \
    }

#define UNITY_ASSERT_NULLPTR(func) \
    { \
        char* _unity_string; \
        asprintf(&_unity_string, "%p == nullptr", func); \
        UNITY_ASSERT(func == nullptr, _unity_string) \
        free(_unity_string); \
    }

#define UNITY_ASSERT_NOT_NULLPTR(func) \
    { \
        char* _unity_string; \
        asprintf(&_unity_string, "%p != nullptr", func); \
        UNITY_ASSERT(func != nullptr, _unity_string) \
        free(_unity_string); \
    }

#define UNITY_ASSERT_STRING_ARRAY_EQUAL(func, target, length) \
    UNITY_ASSERT_BEGIN \
    { \
        uint8_t _unity_flag = 0; \
        for (unsigned int i = 0; i < length; i++) { \
            if (func[i] != target[i]) { \
                char* _unity_string; \
                asprintf(&_unity_string, "\"%c\" == \"%c\"", func[i], target[i]); \
                UNITY_ASSERT_FAILED(_unity_string) \
                free(_unity_string); \
                _unity_flag = 1; \
                break; \
            } \
        } \
        if (_unity_flag == 0) { \
            UNITY_ASSERT_PASSED \
        } \
    }

#endif
