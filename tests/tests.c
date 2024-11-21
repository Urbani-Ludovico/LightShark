
#include <stdio.h>
#include <assert.h>

#define BEGIN_ASSERT \
    unsigned int test_number = 1;

#define ASSERT(x) \
    printf("\033[0;35mTEST\033[0m %u", test_number); \
    assert(x); \
    printf(": \033[0;32mPASSED\033[0m"); \
    test_number++; \

int main(void) {
    BEGIN_ASSERT

    return 0;
}
