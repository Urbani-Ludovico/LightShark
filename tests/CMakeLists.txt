
project(LightSharkTests C)

add_executable(LightSharkTests
    tests/main.c

    tests/unity/unity.h
    tests/unity/example_tests.h
    tests/unity/example_tests.c

    tests/tests/start.h
    tests/tests/tree.h

    tests/tests/start.c
    tests/tests/tree.c
)

target_link_libraries(LightSharkTests PRIVATE LightShark)