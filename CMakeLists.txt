cmake_minimum_required(VERSION 3.22)

project(tictactoe)

set(SRC
    src/main.cpp
    src/tictactoe.cpp)

set(HEADER
    src/tictactoe.h)

add_executable(tictactoe ${SRC} ${HEADER})
