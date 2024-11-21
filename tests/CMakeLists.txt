
project(LightSharkTests C)

add_executable(LightSharkTests
    tests/main.c

    tests/unity/unity.h
    tests/unity/example_tests.c
    tests/unity/example_tests.h

    tests/tests/start.c
)

target_link_libraries(LightSharkTests PRIVATE LightShark)