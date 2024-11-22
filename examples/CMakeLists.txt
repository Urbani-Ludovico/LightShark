
project(LightSharkExamples C)

add_executable(LightSharkExamples
    examples/examples.c

    examples/create.h

    examples/create.c
)

target_link_libraries(LightSharkExamples PRIVATE LightShark)

target_compile_options(LightSharkExamples PRIVATE ${COMPILE_OPTIONS})