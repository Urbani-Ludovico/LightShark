
project(LightSharkTests C)

add_executable(LightSharkTests
    tests/tests.c
)

target_link_libraries(LightSharkTests PRIVATE LightShark)