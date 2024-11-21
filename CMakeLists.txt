cmake_minimum_required(VERSION 3.30)

set(CMAKE_C_STANDARD 23)

include_directories(include)

#----------------------------------------
# Library
#----------------------------------------

project(LightShark C)

add_library(LightShark STATIC
    include/LightShark.h

    include/LSBoard.h
    include/LSEngine.h
    include/LSTree.h

    src/LSBoard.c
    src/LSEngine.c
    src/LSTree.c
)

#----------------------------------------
# Includes
#----------------------------------------

include(examples/CMakeLists.txt)
include(tests/CMakeLists.txt)