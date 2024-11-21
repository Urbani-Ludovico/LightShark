cmake_minimum_required(VERSION 3.30)
project(LightShark C)

set(CMAKE_C_STANDARD 23)

include_directories(include)

add_library(LightShark STATIC
    include/LightShark.h

    include/Board.h
    include/Engine.h
    include/Tree.h

    src/Board.c
    src/Engine.c
    src/Tree.c
)
