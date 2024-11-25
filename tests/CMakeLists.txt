
project(LightSharkTests C)

add_executable(LightSharkTests
    tests/main.c

    tests/unity/unity.h
    tests/unity/example_tests.h
    tests/unity/example_tests.c

    tests/tests/start.h
    tests/tests/tree.h
    tests/tests/check.h

    tests/tests/start.c
    tests/tests/tree.c
    tests/tests/check.c
)

target_link_libraries(LightSharkTests PRIVATE LightShark)

target_compile_options(LightSharkTests PRIVATE ${COMPILE_OPTIONS})