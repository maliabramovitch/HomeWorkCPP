cmake_minimum_required(VERSION 3.24)
project(03)

set(CMAKE_CXX_STANDARD 11)

add_executable(03 main.cpp Virus.cpp Virus.h Population.cpp Population.h World.cpp World.h)
