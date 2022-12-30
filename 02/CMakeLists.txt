cmake_minimum_required(VERSION 3.23)
project(02)

set(CMAKE_CXX_STANDARD 11)

add_executable(02 main.cpp GameSquare.cpp GameSquare.h Player.cpp Player.h Board.cpp Board.h GameManager.cpp GameManager.h)
