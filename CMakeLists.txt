cmake_minimum_required(VERSION 3.30)

set(CMAKE_C_STANDARD 23)

include_directories(include)

if(MSVC)
    set(COMPILE_OPTIONS /W4 /WX)
else()
    set(COMPILE_OPTIONS -Wall -Wextra -Wpedantic -Werror)
endif()

#----------------------------------------
# Library
#----------------------------------------

project(LightShark C)

add_library(LightShark STATIC
    include/LightShark.h

    include/LSBoard.h
    include/LSEngine.h
    include/LSTree.h
    include/LSState.h

    src/LSBoard.c
    src/LSEngine.c
    src/LSTree.c
    src/LSState.c
)

target_compile_options(LightShark PRIVATE ${COMPILE_OPTIONS})

#----------------------------------------
# Includes
#----------------------------------------

include(examples/CMakeLists.txt)
include(tests/CMakeLists.txt)