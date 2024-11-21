cmake_minimum_required(VERSION 3.30)
project(LightShark C)

set(CMAKE_C_STANDARD 23)

include_directories(include)

add_library(LightShark STATIC
    include/LightShark.h

    include/LSBoard.h
    include/LSEngine.h
    include/LSTree.h

    src/LSBoard.c
    src/LSEngine.c
    src/LSTree.c
)
